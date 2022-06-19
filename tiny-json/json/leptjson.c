#include "leptjson.h"
#include <assert.h>  /* assert() */
#include <errno.h>   /* errno, ERANGE */
#include <math.h>    /* HUGE_VAL */
#include <stdlib.h>  /* NULL, strtod() */ 

#define EXPECT(c, ch)             \
    do                            \
    {                             \
        assert(*c->json == (ch)); \
        c->json++;                \
    } while (0)

// 断言（assertion）是 C 语言中常用的防御式编程方式，减少编程错误。
// 最常用的是在函数开始的地方，检测所有参数。有时候也可以在调用函数后，检查上下文是否正确。

#define ISDIGIT(ch)         ((ch) >= '0' && (ch) <= '9')
#define ISDIGIT1TO9(ch)     ((ch) >= '1' && (ch) <= '9')


//为了减少解析函数之间传递多个参数，数据都放进一个 lept_context 结构体：
typedef struct{
    const char *json;
}lept_context;//减少解析函数传递参数

//SON 文本由 3 部分组成，首先是空白（whitespace），接着是一个值，最后是空白。
//
//所谓空白，是由零或多个空格符（space U + 0020）、制表符（tab U + 0009）\t、换行符（LF U + 000A）\n、
//回车符（CR U + 000D）\r所组成。

//解析white space
static void lept_parse_whitespace(lept_context *c)
{
    const char *p = c->json; //指针
    while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n')
    {
        p++;//往后挪
    }
    c->json = p;//挪完的位置开始
}

//们现时的值只可以是 null、false 或 true，它们分别有对应的字面值（literal）。

static int lept_parse_literal(lept_context *c, lept_value *v,const char * literal,lept_type type){
    EXPECT(c, literal[0]); //判断首字母
    size_t i;
    for(i = 0; literal[i+1];i++){
        if(c->json[i]!= literal[i+1])
            return LEPT_PARSE_INVALID_VALUE;
    }
    c->json += i;
    v->type = type;
    return LEPT_PARSE_OK;
}


//number 是以十进制表示，它主要由 4 部分顺序组成：负号、整数、小数、指数。只有整数是必需部分。
//注意和直觉可能不同的是，正号是不合法的。
//
//整数部分如果是 0 开始，只能是单个 0；而由 1 - 9 开始的话，可以加任意数量的数字（0 - 9）。
//也就是说，0123 不是一个合法的 JSON 数字。
//
//小数部分比较直观，就是小数点后是一或多个数字（0 - 9）。
//
//JSON 可使用科学记数法，指数部分由大写 E 或小写 e 开始，然后可有正负号，之后是一或多个数字（0 - 9）。

static int lept_parse_number(lept_context *c,lept_value*v){
    const char * p = c->json;
    if(*p == '-') p++;
    if(*p == '0') p++;
    else{
        if (!ISDIGIT1TO9(*p)) return LEPT_PARSE_INVALID_VALUE;//不符合标准
        for (p++; ISDIGIT(*p); p++);
    }
    if(*p == '.'){
        p++;
        if (!ISDIGIT(*p)) return LEPT_PARSE_INVALID_VALUE;//不符合标准
        for (p++; ISDIGIT(*p); p++);
    }
    if (*p == 'e' || *p == 'E') {
        p++;
        if (*p == '+' || *p == '-') p++;
        if (!ISDIGIT(*p)) return LEPT_PARSE_INVALID_VALUE;//不符合标准
        for (p++; ISDIGIT(*p); p++);
    }
    errno = 0;

    v->num = strtod(c->json,NULL); //strtod（将字符串转换成浮点数）
    //在校验成功以后，我们不再使用 end 指针去检测 strtod() 的正确性，第二个参数可传入 NULL。
    //str -- 要转换为双精度浮点数的字符串。
    //endptr -- 对类型为 char* 的对象的引用，其值由函数设置为 str 中数值后的下一个字符。
    if (errno == ERANGE && (v->num == HUGE_VAL || v->num == -HUGE_VAL))
        return LEPT_PARSE_NUMBER_TOO_BIG;
    c->json = p;
    v->type = LEPT_NUMBER;
    return LEPT_PARSE_OK;

}

static int lept_parse_value(lept_context* c, lept_value* v) {
    switch (*c->json) {
        case 't':  return lept_parse_literal(c, v,"true",LEPT_TRUE);
        case 'f':  return lept_parse_literal(c, v,"false",LEPT_FALSE);
        case 'n':  return lept_parse_literal(c, v,"null",LEPT_NULL);
        default:   return lept_parse_number(c,v);
        case '\0': return LEPT_PARSE_EXPECT_VALUE;
    }
}
//解析 JSON：
int lept_parse(lept_value* v, const char* json) {
    lept_context c;
    int ret;
    assert(v != NULL);
    c.json = json;
    v->type = LEPT_NULL;
    lept_parse_whitespace(&c);
    if ((ret = lept_parse_value(&c, v)) == LEPT_PARSE_OK) {
        lept_parse_whitespace(&c);
        if (*c.json != '\0'){
            v->type = LEPT_NULL; //?
            ret = LEPT_PARSE_ROOT_NOT_SINGULAR;
        }
    }
    return ret;
}

lept_type lept_get_type(const lept_value* v) {
    assert(v != NULL);
    return v->type;
}

double lept_get_number(const lept_value *v){
    //使用者应确保类型(是number类型的数据)正确，才调用此 API。
    assert(v != NULL && v->type == LEPT_NUMBER); //我们继续使用断言来保证。
    return v->num;
}