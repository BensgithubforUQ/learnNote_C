#include "http_conn.h"

// 定义HTTP响应的一些状态信息
const char *ok_200_title = "OK";
const char *error_400_title = "Bad Request";
const char *error_400_form = "Your request has bad syntax or is inherently impossible to satisfy.\n";
const char *error_403_title = "Forbidden";
const char *error_403_form = "You do not have permission to get file from this server.\n";
const char *error_404_title = "Not Found";
const char *error_404_form = "The requested file was not found on this server.\n";
const char *error_500_title = "Internal Error";
const char *error_500_form = "There was an unusual problem serving the requested file.\n";

// 网站的根目录
const char *doc_root = "/home/ben/Linux/learnNote_C/web-server/easyImplement/resources";

//对文件描述符设置非阻塞
int setnonblocking(int fd)
{ //设置为非阻塞
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

//内核事件表注册新事件，开启EPOLLONESHOT，针对客户端连接的描述符，listenfd不用开启
void addfd(int epollfd, int fd, bool one_shot)
{
    epoll_event event;
    event.data.fd = fd;
    // #ifdef ET //边缘触发
    //     event.events = EPOLLIN | EPOLLET | EPOLLRDHUP;
    // #endif
    // #ifdef LT //条件触发
    //     event.events = EPOLLIN | EPOLLRDHUP;
    // #endif
    event.events = EPOLLIN | EPOLLRDHUP;
    if (one_shot)
    {
        // 防止同一个通信被不同的线程处理，listen就不开,其他套接字开
        event.events |= EPOLLONESHOT;
    }
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event); //注册
    // 设置文件描述符非阻塞
    setnonblocking(fd);
}

// 从epoll中移除监听的文件描述符
void removefd(int epollfd, int fd)
{
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, 0);
    close(fd);
}

// 修改文件描述符，重置socket上的EPOLLONESHOT事件，以确保下一次可读时，EPOLLIN事件能被触发
void modfd(int epollfd, int fd, int ev)
{
    epoll_event event;
    event.data.fd = fd;
    // #ifdef ET //边缘触发
    //     event.events = ev | EPOLLET | EPOLLONESHOT | EPOLLRDHUP;
    // #endif
    // #ifdef LT //条件触发
    //     event.events = ev | EPOLLONESHOT | EPOLLRDHUP;
    // #endif
    event.events = ev | EPOLLONESHOT | EPOLLRDHUP;
    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 所有的客户数
int http_conn::m_user_count = 0;
// 所有socket上的事件都被注册到同一个epoll内核事件中，所以设置成静态的
int http_conn::m_epollfd = -1;

// 关闭连接
void http_conn::close_conn()
{
    if (m_sockfd != -1)
    {
        removefd(m_epollfd, m_sockfd);
        m_sockfd = -1;
        m_user_count--; // 关闭一个连接，将客户总数量-1
    }
}

// 初始化连接,外部调用初始化套接字地址
void http_conn::init(int sockfd, const sockaddr_in &addr)
{
    m_sockfd = sockfd;
    m_address = addr;

    // 端口复用
    int reuse = 1;
    setsockopt(m_sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    addfd(m_epollfd, sockfd, true);
    m_user_count++;
    init();
}

void http_conn::init()
{

    bytes_to_send = 0;
    bytes_have_send = 0;

    m_check_state = CHECK_STATE_REQUESTLINE; // 初始状态为检查请求行
    m_linger = false;                        // 默认不保持链接  Connection : keep-alive保持连接

    m_method = GET; // 默认请求方式为GET
    m_url = 0;
    m_version = 0;
    m_content_length = 0;
    m_host = 0;
    m_start_line = 0;
    m_checked_idx = 0;
    m_read_idx = 0;
    m_write_idx = 0;

    bzero(m_read_buf, READ_BUFFER_SIZE);
    bzero(m_write_buf, READ_BUFFER_SIZE);
    bzero(m_real_file, FILENAME_LEN);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 循环读取客户数据，直到无数据可读或者对方关闭连接 - 一次性读完
bool http_conn::read()
{
    if (m_read_idx >= READ_BUFFER_SIZE)
    {
        return false;
    }
    int bytes_read = 0;
    while (true)
    {
        // 从m_read_buf + m_read_idx索引出开始保存数据，大小是READ_BUFFER_SIZE - m_read_idx
        bytes_read = recv(m_sockfd, m_read_buf + m_read_idx,
                          READ_BUFFER_SIZE - m_read_idx, 0);
        if (bytes_read == -1)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                // 没有数据
                break;
            }
            return false;
        }
        else if (bytes_read == 0)
        { // 对方关闭连接
            return false;
        }
        m_read_idx += bytes_read;
    }
    return true;
}

// 解析一行，判断依据\r\n
// 从状态机，用于分析出一行内容
// 返回值为行的读取状态，有LINE_OK,LINE_BAD,LINE_OPEN
http_conn::LINE_STATUS http_conn::parse_line()
{
    char temp;
    for (; m_checked_idx < m_read_idx; ++m_checked_idx)
    {
        temp = m_read_buf[m_checked_idx];
        if (temp == '\r')
        {
            if ((m_checked_idx + 1) == m_read_idx) // buf读完了，但是没有\n，证明还有数据没读完
            {
                return LINE_OPEN;
            }
            else if (m_read_buf[m_checked_idx + 1] == '\n') //下一个就是\n,置换为行结束符，返回读完了一行
            {
                m_read_buf[m_checked_idx++] = '\0';
                m_read_buf[m_checked_idx++] = '\0';
                return LINE_OK;
            }
            return LINE_BAD;
        }
        else if (temp == '\n')
        {
            if ((m_checked_idx > 1) && (m_read_buf[m_checked_idx - 1] == '\r')) //读到\n，就要判断去前一个是不是\r
            {
                m_read_buf[m_checked_idx - 1] = '\0';
                m_read_buf[m_checked_idx++] = '\0';
                return LINE_OK;
            }
            return LINE_BAD; //如果不是那就语法错误
        }
    }
    return LINE_OPEN;
}

// 解析HTTP请求行，获得请求方法，目标URL,以及HTTP版本号
http_conn::HTTP_CODE http_conn::parse_request_line(char *text)
{
    // GET /index.html HTTP/1.1
    //在HTTP报文中，请求行用来说明请求类型,要访问的资源以及所使用的HTTP版本，其中各个部分之间通过\t或空格分隔。
    m_url = strpbrk(text, " \t"); //请求行中最先含有空格和\t任一字符的位置并返回
    if (!m_url)
    {
        return BAD_REQUEST; //如果没有空格或\t，则报文格式有误
    }
    // GET\0/index.html HTTP/1.1
    *m_url++ = '\0'; //将该位置改为\0，用于将前面数据取出
    char *method = text;
    if (strcasecmp(method, "GET") == 0)
    { // 忽略大小写比较
        m_method = GET;
    }
    else if (strcasecmp(method, "POST") == 0)
    {
        m_method = POST;
        cgi = 1;
    }
    else
    {
        return BAD_REQUEST;
    }

    // /index.html HTTP/1.1
    // 检索字符串 str1 中第一个不在字符串 str2 中出现的字符下标。
    m_version = strpbrk(m_url, " \t");
    if (!m_version)
    {
        return BAD_REQUEST;
    }
    *m_version++ = '\0';
    if (strcasecmp(m_version, "HTTP/1.1") != 0) //仅支持HTTP/1.1
    {
        return BAD_REQUEST;
    }
    /**
     * http://192.168.110.129:10000/index.html
     */
    if (strncasecmp(m_url, "http://", 7) == 0) //对请求资源前7个字符进行判断
    {
        m_url += 7;
        // 在参数 str 所指向的字符串中搜索第一次出现字符 c（一个无符号字符）的位置。
        m_url = strchr(m_url, '/');
    }
    if (strncasecmp(m_url, "https://", 8) == 0) //对请求资源前8个字符进行判断
    {
        m_url += 8;
        // 在参数 str 所指向的字符串中搜索第一次出现字符 c（一个无符号字符）的位置。
        m_url = strchr(m_url, '/');
    }
    //一般的不会带有上述两种符号，直接是单独的/或/后面带访问资源
    if (!m_url || m_url[0] != '/')
    {
        return BAD_REQUEST;
    }

    // if(strlen(m_url)==1) //这个是欢迎页，就是后面不跟/？？？
    //     strcat(m_url,"judge.html");

    m_check_state = CHECK_STATE_HEADER; //请求行处理完毕，将主状态机转移处理请求头
    return NO_REQUEST;
}

// 解析HTTP请求的一个头部信息
http_conn::HTTP_CODE http_conn::parse_headers(char *text)
{
    // 遇到空行，表示头部字段解析完毕
    if (text[0] == '\0')
    {
        // 如果HTTP请求有消息体，则还需要读取m_content_length字节的消息体，
        // 状态机转移到CHECK_STATE_CONTENT状态
        if (m_content_length != 0)
        {
            m_check_state = CHECK_STATE_CONTENT;
            return NO_REQUEST;
        }
        // 否则说明我们已经得到了一个完整的HTTP请求
        return GET_REQUEST;
    }
    else if (strncasecmp(text, "Connection:", 11) == 0) //解析请求头部连接字段
    {
        // 处理Connection 头部字段  Connection: keep-alive
        text += 11;
        text += strspn(text, " \t");             //跳过空格和\t字符
        if (strcasecmp(text, "keep-alive") == 0) //如果是长连接，则将linger标志设置为true
        {
            m_linger = true;
        }
    }
    else if (strncasecmp(text, "Content-Length:", 15) == 0) //解析请求头部内容长度字段
    {
        // 处理Content-Length头部字段
        text += 15;
        text += strspn(text, " \t");
        m_content_length = atol(text);
    }
    else if (strncasecmp(text, "Host:", 5) == 0) //解析请求头部HOST字段
    {
        // 处理Host头部字段
        text += 5;
        text += strspn(text, " \t");
        m_host = text;
    }
    else
    {
        printf("oop! unknow header %s\n", text);
    }
    return NO_REQUEST;
}

// 用于保存post请求消息体，为后面的登录和注册做准备
// GET和POST请求报文的区别之一是有无消息体部分
http_conn::HTTP_CODE http_conn::parse_content(char *text)
{
    if (m_read_idx >= (m_content_length + m_checked_idx))
    {
        text[m_content_length] = '\0';
        // POST请求中最后为输入的用户名和密码
        m_string = text;
        return GET_REQUEST;
    }
    return NO_REQUEST;
}

// 主状态机，解析请求
http_conn::HTTP_CODE http_conn::process_read()
{
    LINE_STATUS line_status = LINE_OK; //初始化从状态机状态、HTTP请求解析结果
    HTTP_CODE ret = NO_REQUEST;
    char *text = 0;
    // parse_line为从状态机的具体实现
    while (((m_check_state == CHECK_STATE_CONTENT) && (line_status == LINE_OK)) || ((line_status = parse_line()) == LINE_OK))
    {
        // m_start_line是行在buffer中的起始位置，将该位置后面的数据赋给text
        //此时从状态机已提前将一行的末尾字符\r\n变为\0\0，所以text可以直接取出完整的行进行解析
        text = get_line(); //定义在类里面了

        // m_start_line是每一个数据行在m_read_buf中的起始位置
        // m_checked_idx表示从状态机在m_read_buf中读取的位置
        m_start_line = m_checked_idx;
        printf("got 1 http line: %s\n", text);

        //主状态机的三种状态转移逻辑
        switch (m_check_state)
        {
        case CHECK_STATE_REQUESTLINE: //当前正在分析请求行
        {
            ret = parse_request_line(text);
            if (ret == BAD_REQUEST)
            {
                return BAD_REQUEST;
            }
            break;
        }
        case CHECK_STATE_HEADER: //当前正在分析请求头
        {
            ret = parse_headers(text);
            if (ret == BAD_REQUEST)
            {
                return BAD_REQUEST;
            }
            else if (ret == GET_REQUEST) //完整解析GET请求后，跳转到报文响应函数
            {
                return do_request();
            }
            break;
        }
        case CHECK_STATE_CONTENT: //解析消息体
        {
            ret = parse_content(text); //完整解析POST请求后，跳转到报文响应函数
            if (ret == GET_REQUEST)
            {
                return do_request();
            }
            line_status = LINE_OPEN; //解析完消息体即完成报文解析，避免再次进入循环，更新line_status
            break;
        }
        default:
        {
            return INTERNAL_ERROR;
        }
        }
    }
    return NO_REQUEST;
}

// 浏览器端发出HTTP请求报文，服务器端接收该报文并调用process_read对其进行解析，
// 根据解析结果HTTP_CODE，进入相应的逻辑和模块。
// 其中，服务器子线程完成报文的解析与响应；
// 主线程监测读写事件，调用read_once和http_conn::write完成数据的读取与发送。

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// process_read函数的返回值是对请求的文件分析后的结果，一部分是语法错误导致的BAD_REQUEST，
// 一部分是do_request的返回结果.该函数将网站根目录和url文件拼接，然后通过stat判断该文件属性。
// 另外，为了提高访问速度，通过mmap进行映射，将普通文件映射到内存逻辑地址。

// 为了更好的理解请求资源的访问流程，这里对各种各页面跳转机制进行简要介绍。
// 其中，浏览器网址栏中的字符，即url，可以将其抽象成ip:port/xxx，xxx通过html文件的action属性进行设置。

// m_url为请求报文中解析出的请求资源，以/开头，也就是/xxx，项目中解析后的m_url有8种情况。

// 当得到一个完整、正确的HTTP请求时，我们就分析目标文件的属性，
// 如果目标文件存在、对所有用户可读，且不是目录，则使用mmap将其
// 映射到内存地址m_file_address处，并告诉调用者获取文件成功
http_conn::HTTP_CODE http_conn::do_request()
{
    strcpy(m_real_file, doc_root); //将初始化的m_real_file赋值为网站根目录doc_root
    int len = strlen(doc_root);

    //找到m_url中/的位置
    const char *p = strchr(m_url, '/');

    //实现登录和注册校验
    if (cgi == 1 && (*(p + 1) == 2 || *(p + 1) == 3))
    { //还未实现！！！！！！！！！！
      //根据标志判断是登录检测还是注册检测
      //同步线程登录校验
      // CGI多进程登录校验
    }

    //如果请求资源为/0，表示跳转注册界面
    if (*(p + 1) == '0')
    {
        char *m_url_real = (char *)malloc(sizeof(char) * 200);
        strcpy(m_url_real, "/register.html");
        //将网站目录和/register.html进行拼接，更新到m_real_file中
        strncpy(m_real_file + len, m_url_real, strlen(m_url_real));
        // char *strncpy(char *dest, const char *src, int n)
        // 表示把src所指向的字符串中以src地址开始的前n个字节复制到dest所指的数组中，并返回被复制后的dest
        free(m_url_real);
    }
    //如果请求资源为/1，表示跳转注册界面
    else if (*(p + 1) == '1')
    {
        char *m_url_real = (char *)malloc(sizeof(char) * 200);
        strcpy(m_url_real, "/log.html");
        //将网站目录和/log.html进行拼接，更新到m_real_file中
        strncpy(m_real_file + len, m_url_real, strlen(m_url_real));
        // char *strncpy(char *dest, const char *src, int n)
        // 表示把src所指向的字符串中以src地址开始的前n个字节复制到dest所指的数组中，并返回被复制后的dest
        free(m_url_real);
    }
    else
    {
        //如果以上均不符合，即不是登录和注册，直接将url与网站目录拼接
        //这里的情况是welcome界面，请求服务器上的一个图片
        strncpy(m_real_file + len, m_url, FILENAME_LEN - len - 1);
        // strncpy(m_real_file + len, m_url, FILENAME_LEN - len - 1);
    }

    //通过stat获取请求资源文件信息，成功则将信息更新到m_file_stat结构体
    // 获取m_real_file文件的相关的状态信息，-1失败，0成功
    if (stat(m_real_file, &m_file_stat) < 0)
    {
        return NO_RESOURCE;
    }

    //判断文件的权限，是否可读，不可读则返回FORBIDDEN_REQUEST状态
    if (!(m_file_stat.st_mode & S_IROTH))
    {
        return FORBIDDEN_REQUEST;
    }

    //判断文件类型，如果是目录，则返回BAD_REQUEST，表示请求报文有误
    if (S_ISDIR(m_file_stat.st_mode))
    {
        return BAD_REQUEST;
    }

    //以只读方式获取文件描述符，通过mmap将该文件映射到内存中
    int fd = open(m_real_file, O_RDONLY);
    // 创建内存映射
    m_file_address = (char *)mmap(0, m_file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    // void* mmap(void* start,size_t length,int prot,int flags,int fd,off_t offset);
    //  start：映射区的开始地址，设置为0时表示由系统决定映射区的起始地址
    //      length：映射区的长度
    //  prot：期望的内存保护标志，不能与文件的打开模式冲突
    //      PROT_READ 表示页内容可以被读取
    //  flags：指定映射对象的类型，映射选项和映射页是否可以共享
    //      MAP_PRIVATE 建立一个写入时拷贝的私有映射，内存区域的写入不会影响到原文件
    //  fd：有效的文件描述符，一般是由open()函数返回
    //  off_toffset：被映射对象内容的起点
    close(fd);           //避免文件描述符的浪费和占用
    return FILE_REQUEST; //表示请求文件存在，且可以访问
}

// 对内存映射区执行munmap操作
void http_conn::unmap()
{
    if (m_file_address)
    {
        munmap(m_file_address, m_file_stat.st_size);
        // int munmap(void* start,size_t length); 用于将一个文件或其他对象映射到内存，提高文件的访问速度。
        // start：映射区的开始地址，设置为0时表示由系统决定映射区的起始地址
        // length：映射区的长度
        m_file_address = 0;
    }
}

// 写HTTP响应
// 服务器子线程调用process_write完成响应报文，随后注册epollout事件。
// 服务器主线程检测写事件，并调用http_conn::write函数将响应报文发送给浏览器端。
bool http_conn::write()
{
    int temp = 0;

    if (bytes_to_send == 0)
    {
        // 将要发送的字节为0，这一次响应结束。
        modfd(m_epollfd, m_sockfd, EPOLLIN);
        init();
        return true;
    }

    while (1)
    {
        //将响应报文的状态行、消息头、空行和响应正文发送给浏览器端
        // writev函数用于在一次函数调用中写多个非连续缓冲区，有时也将这该函数称为聚集写。
        // filedes表示文件描述符
        // iov为前述io向量机制结构体iovec
        // iovcnt为结构体的个数
        temp = writev(m_sockfd, m_iv, m_iv_count);
        if (temp <= -1)
        {
            // 如果TCP写缓冲没有空间，则等待下一轮EPOLLOUT事件，虽然在此期间，
            // 服务器无法立即接收到同一客户的下一个请求，但可以保证连接的完整性。
            if (errno == EAGAIN)
            {
                modfd(m_epollfd, m_sockfd, EPOLLOUT);
                return true;
            }
            unmap();
            return false;
        }
        //正常发送，temp为发送的字节数
        bytes_have_send += temp; //更新已发送字节
        bytes_to_send -= temp; //偏移文件iovec的指针

        if (bytes_have_send >= m_iv[0].iov_len)
        {
            m_iv[0].iov_len = 0;
            m_iv[1].iov_base = m_file_address + (bytes_have_send - m_write_idx);
            m_iv[1].iov_len = bytes_to_send;
        }
        else
        {
            m_iv[0].iov_base = m_write_buf + bytes_have_send;
            m_iv[0].iov_len = m_iv[0].iov_len - temp;
        }

        if (bytes_to_send <= 0)
        {
            // 没有数据要发送了
            unmap();
            modfd(m_epollfd, m_sockfd, EPOLLIN);

            if (m_linger)
            {
                init();
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}

// 往写缓冲中写入待发送的数据,更新m_write_idx指针和缓冲区m_write_buf中的内容。
bool http_conn::add_response(const char *format, ...)
{
    if (m_write_idx >= WRITE_BUFFER_SIZE) //如果写入内容超出m_write_buf大小则报错
    {
        return false;
    }
    va_list arg_list;           //定义可变参数列表
    va_start(arg_list, format); //将变量arg_list初始化为传入参数
    //将数据format从可变参数列表写入缓冲区写，返回写入数据的长度
    int len = vsnprintf(m_write_buf + m_write_idx, WRITE_BUFFER_SIZE - 1 - m_write_idx, format, arg_list);
    //如果写入的数据长度超过缓冲区剩余空间，则报错
    if (len >= (WRITE_BUFFER_SIZE - 1 - m_write_idx))
    {
        return false;
    }
    m_write_idx += len; //更新m_write_idx位置
    va_end(arg_list);   //清空可变参列表
    return true;
}

bool http_conn::add_status_line(int status, const char *title) //添加状态行
{
    return add_response("%s %d %s\r\n", "HTTP/1.1", status, title);
}

bool http_conn::add_headers(int content_len) //添加消息报头，具体的添加文本长度、连接状态和空行
{
    add_content_length(content_len);
    add_content_type();
    add_linger();
    add_blank_line();
}

bool http_conn::add_content_length(int content_len) //添加Content-Length，表示响应报文的长度
{
    return add_response("Content-Length: %d\r\n", content_len);
}

bool http_conn::add_linger() //添加连接状态，通知浏览器端是保持连接还是关闭
{
    return add_response("Connection: %s\r\n", (m_linger == true) ? "keep-alive" : "close");
}

bool http_conn::add_blank_line() //添加空行
{
    return add_response("%s", "\r\n");
}

bool http_conn::add_content(const char *content) //添加文本content
{
    return add_response("%s", content);
}

bool http_conn::add_content_type() //添加文本类型，这里是html
{
    return add_response("Content-Type:%s\r\n", "text/html");
}

// 响应报文分为两种，
// 一种是请求文件的存在，通过io向量机制iovec，声明两个iovec，
// 第一个指向m_write_buf，第二个指向mmap的地址m_file_address；一种是请求出错，这时候只申请一个iovec，指向m_write_buf。
//      iovec是一个结构体，里面有两个元素，指针成员iov_base指向一个缓冲区，这个缓冲区是存放的是writev将要发送的数据。
//      成员iov_len表示实际写入的长度
// 根据服务器处理HTTP请求的结果，决定返回给客户端的内容
bool http_conn::process_write(HTTP_CODE ret)
{
    switch (ret)
    {
    case INTERNAL_ERROR:                       //内部错误，500
        add_status_line(500, error_500_title); //状态行
        add_headers(strlen(error_500_form));   //消息报头
        if (!add_content(error_500_form))
        {
            return false;
        }
        break;
    case BAD_REQUEST: //报文语法有误，404
        add_status_line(400, error_400_title);
        add_headers(strlen(error_400_form));
        if (!add_content(error_400_form))
        {
            return false;
        }
        break;
    case NO_RESOURCE:
        add_status_line(404, error_404_title);
        add_headers(strlen(error_404_form));
        if (!add_content(error_404_form))
        {
            return false;
        }
        break;
    case FORBIDDEN_REQUEST: //资源没有访问权限，403
        add_status_line(403, error_403_title);
        add_headers(strlen(error_403_form));
        if (!add_content(error_403_form))
        {
            return false;
        }
        break;
    case FILE_REQUEST: //文件存在，200
        add_status_line(200, ok_200_title);
        //如果请求的资源存在
        if (m_file_stat.st_size != 0)
        {
            add_headers(m_file_stat.st_size);
            //第一个iovec指针指向响应报文缓冲区，长度指向m_write_idx
            m_iv[0].iov_base = m_write_buf;
            m_iv[0].iov_len = m_write_idx;
            //第二个iovec指针指向mmap返回的文件指针，长度指向文件大小
            m_iv[1].iov_base = m_file_address;
            m_iv[1].iov_len = m_file_stat.st_size;
            m_iv_count = 2;
            //发送的全部数据为响应报文头部信息和文件大小
            bytes_to_send = m_write_idx + m_file_stat.st_size;
            return true;
        }
        else
        {
            //如果请求的资源大小为0，则返回空白html文件
            const char* ok_string="<html><body></body></html>";
            add_headers(strlen(ok_string));
            if(!add_content(ok_string))
                return false;
        }

    default:
        return false;
    }
    //除FILE_REQUEST状态外，其余状态只申请一个iovec，指向响应报文缓冲区
    m_iv[0].iov_base = m_write_buf;
    m_iv[0].iov_len = m_write_idx;
    m_iv_count = 1;
    bytes_to_send = m_write_idx;
    return true;
}

// 由线程池中的工作线程调用，这是处理HTTP请求的入口函数
void http_conn::process()
{
    // 解析HTTP请求
    HTTP_CODE read_ret = process_read();
    if (read_ret == NO_REQUEST) // NO_REQUEST，表示请求不完整，需要继续接收请求数据
    {
        modfd(m_epollfd, m_sockfd, EPOLLIN); //注册并监听读事件
        return;
    }

    //调用process_write完成报文响应
    bool write_ret = process_write(read_ret);
    if (!write_ret)
    {
        close_conn();
    }
    modfd(m_epollfd, m_sockfd, EPOLLOUT); //注册并监听写事件
}