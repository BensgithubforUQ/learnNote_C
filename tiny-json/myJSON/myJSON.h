#include <iostream>
#include <string>
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

	struct json_value {
		union {
			struct {
				char* s; //字符串
				int len; //字符串长度
			}str;
			double num; //json中的数字
		};
		json_type type;
	};

	enum {
		PARSE_OK = 0,
		PARSE_EXPECT_VALUE,
		PARSE_INVALID_VALUE,
		PARSE_ROOT_NOT_SINGULAR,
		PARSE_TO_BIG_NUMBER,
		PARSE_MISS_QUATATION_MARK,
		PARSE_INVALID_STRING_ESCAPE,
		PARSE_INVALID_STRING_CHAR
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
}
