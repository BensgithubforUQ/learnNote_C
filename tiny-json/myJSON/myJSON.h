#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace ben{
	typedef enum {
		M_TEXT_NULL,
		M_TEXT_FALSE,
		M_TEXT_TRUE,
		M_NUMBER,
		M_STRING,
		M_ARRAY,
		M_OBJECT,
	}json_type;

	typedef struct json_value json_value;
	typedef struct json_object json_object;
	class json_value {
	public:
		union {
			struct {
				char* s; //字符串
				int len; //字符串长度
			}str;
			double num; //json中的数字
		};
		json_type type;
		json_value* arr;
		int size;
		
		//object的数组
		json_object* object;
		size_t o_size;
	};

	struct json_object {
		char* k;
		size_t k_len;
		json_value v;
	};

	enum {
		PARSE_OK = 0,
		PARSE_EXPECT_VALUE,
		PARSE_INVALID_VALUE,
		PARSE_ROOT_NOT_SINGULAR,
		PARSE_TO_BIG_NUMBER,
		PARSE_MISS_QUATATION_MARK,
		PARSE_INVALID_STRING_ESCAPE, //对其他不合法的字符
		PARSE_INVALID_STRING_CHAR, 
		PARSE_INVALID_UNICODE_SURROGATE, //有高代理项而欠缺低代理项，或是低代理项不在合法码点范围
		PARSE_INVALID_UNICODE_HEX, //如果 "\\u" 后不是 4 位十六进位数字
		PARSE_MISS_COMMA_OR_SQUARE_BRACKET, //缺少]或者, 其实也是格式不对
		PARSE_MISS_KEY, //缺少键
		PARSE_MISS_COLON, //缺少冒号
		PARSE_MISS_COMMA_OR_CURLY_BRACKET //缺少逗号
	};

	void prase_init(json_value* v);

	int parse(json_value* v, const char* json);

	void json_free(json_value* v);
	json_type get_type(const json_value* v);
	
	void set_null(json_value* v);

	int get_boolean(const json_value* v);
	void set_boolean(json_value* v, int b);

	double get_number(const json_value* v);
	void set_number(json_value* v, double n);


	const char* get_string(const json_value* v);
	size_t get_string_len(const json_value* v);
	void set_string(json_value* v, const char* s, size_t len);

	const char* parse_hex4(const char *p, unsigned* u);

	size_t get_array_size(const json_value* v);
	json_value* get_array_element(const json_value* v, size_t index);


	size_t get_object_size(const json_value* v);
	const char* get_object_key(const json_value* v, size_t index);
	size_t get_object_key_length(const json_value* v, size_t index);
	json_value* get_object_value(const json_value* v, size_t index);

}
