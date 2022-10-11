#include "QtWidgetsApplication1.h"
#include "MyOwnButton.h"


QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QMainWindow(parent)
{
    //两种新建button的方法
    QPushButton* _btn_01 = new QPushButton;
    _btn_01->setText(" first button test... ");
    _btn_01->adjustSize();
    _btn_01->setParent(this);
    

    QPushButton* _btn_02 = new QPushButton("second button", this);
    
    //套件位移
    _btn_01->move(0, 100);
    _btn_02->move(100, 0);
    ui.setupUi(this);

    //设置窗口大小
    resize(600, 600);

    //设置窗口的标题
    setWindowTitle(" first window's title...");

    //设置不可拉伸的窗口
    setFixedSize(600, 600);

    //创建一个MyOwnButton类型的对象
    MyOwnButton *_myBtn01 = new MyOwnButton(0);
    _myBtn01->setText("my own button");
    _myBtn01->move(150, 100);
    _myBtn01->adjustSize();
    _myBtn01->setParent(this);

    /*
    有反应的按钮 - 信号槽
    参数1：信号发送者
    参数2：发送的信号（函数的地址）
    参数3：接受信号的对象
    参数4：处理信号的槽函数（函数的地址）
    */
    connect(_myBtn01, &QPushButton::clicked, this, &QWidget::close);

}

QtWidgetsApplication1::~QtWidgetsApplication1()
{}
