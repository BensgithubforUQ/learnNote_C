#ifndef LEPTJSON_H_
#define LEPTJSON_H_

//JSON 中有 6 种数据类型，如果把 true 和 false 当作两个类型就是 7 种，为此声明一个枚举类型（enumeration type）：
typedef enum { LEPT_NULL, LEPT_FALSE, LEPT_TRUE, LEPT_NUMBER, LEPT_STRING, LEPT_ARRAY, LEPT_OBJECT } lept_type;
//null, false, true, float, "", [] , {};

typedef struct
{
    /* 我们声明 JSON 的数据结构。JSON 是一个树形结构，
    我们最终需要实现一个树的数据结构，每个节点使用 lept_value 结构体表示，
    我们会称它为一个 JSON 值（JSON value）。  */
    lept_type type;
    double num; //LEPT_NUMBER

}lept_value;//json的树形数据结构


// 若一个 JSON 只含有空白，传回 LEPT_PARSE_EXPECT_VALUE。
// 若一个值之后，在空白之后还有其他字符，传回 LEPT_PARSE_ROOT_NOT_SINGULAR。
// 若值不是那三种字面值，传回 LEPT_PARSE_INVALID_VALUE。
enum {
    LEPT_PARSE_OK = 0,
    LEPT_PARSE_EXPECT_VALUE,
    LEPT_PARSE_INVALID_VALUE,
    LEPT_PARSE_ROOT_NOT_SINGULAR
};

//解析 JSON：
int lept_parse(lept_value *v,const char* json);
//访问结果的函数，就是获取其类型：
lept_type lept_get_type(const lept_value* v);
double lept_get_number(const lept_value *v);
#endif