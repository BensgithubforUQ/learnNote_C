#include "myJSON.h"
using namespace ben;


static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;
/* M_TEXT_NULL,
	 M_TEXT_FALSE,
	 M_TEXT_TRUE,
	 M_NUMBER,
	 M_STRING,
	 M_ARRAY,
	 M_OBJECT,*/

	 /*  PARSE_OK = 0,
		   PARSE_EXPECT_VALUE,
		   PARSE_INVALID_VALUE,
		   PARSE_ROOT_NOT_SINGULAR,
		   PARSE_TO_BIG_NUMBER,
		   PARSE_MISS_QUATATION_MARK,
		   PARSE_INVALID_STRING_ESCAPE,
		   PARSE_INVALID_STRING_CHAR*/

template <class T>
void EXPECT_EQ_BASE(bool equality, T expect, T actual, string format) {
	do {
		test_count++;
		if (equality)
			test_pass++;
		else {
			printf(".....................................\n");
			//fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);
			main_ret = 1;
		}
	} while (0);
}


void EXPECT_EQ_INT(int expect, int actual) {
	EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d");
}
void EXPECT_EQ_DOUBLE(int expect, int actual) {
	EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%.17g");
}

//#define EXPECT_EQ_STRING(expect, actual, alength) \
//    EXPECT_EQ_BASE(sizeof(expect) - 1 == alength && memcmp(expect, actual, alength) == 0, expect, actual, "%s")
void EXPECT_EQ_STRING(const char* expect, const char* actual, size_t alength) {
	string temp = expect;
	EXPECT_EQ_BASE(temp == actual, expect, actual, "%s");
	//EXPECT_EQ_BASE(temp.size() == alength && memcmp(expect,actual, alength) == 0, expect, actual, "%s");
}
void EXPECT_TRUE(int actual){
	EXPECT_EQ_BASE((actual) != 0, "true", "false", "%s");
}
void EXPECT_FALSE(int actual) {
	EXPECT_EQ_BASE((actual) == 0, "false", "true", "%s");
}

void EXPECT_EQ_SIZE_T(int expect, int actual) {
	EXPECT_EQ_BASE((expect) == (actual), actual, expect, "%d");
}

void TEST_ERROR(int error, const char* json) {
	do {
		json_value v;
		prase_init(&v);
		v.type = M_TEXT_FALSE;
		EXPECT_EQ_INT(error, parse(&v, json));
		EXPECT_EQ_INT(M_TEXT_NULL, get_type(&v));
		json_free(&v);
	} while (0);
}

static void test_parse_null() {
	json_value v;
	prase_init(&v);
	v.type = M_TEXT_FALSE;
	EXPECT_EQ_INT(PARSE_OK, parse(&v, "null"));
	EXPECT_EQ_INT(M_TEXT_NULL, get_type(&v));
	json_free(&v);
}

static void test_parse_true() {
	json_value v;
	prase_init(&v);
	v.type = M_TEXT_FALSE;
	EXPECT_EQ_INT(PARSE_OK, parse(&v, "true"));
	EXPECT_EQ_INT(M_TEXT_TRUE, get_type(&v));
	json_free(&v);
}

static void test_parse_false() {
	json_value v;
	prase_init(&v);
	v.type = M_TEXT_TRUE;
	EXPECT_EQ_INT(PARSE_OK, parse(&v, "false"));
	EXPECT_EQ_INT(M_TEXT_FALSE, get_type(&v));
	json_free(&v);
}

void TEST_NUMBER(double expect, const char* json) {
	do {
		json_value v;
		prase_init(&v);
		EXPECT_EQ_INT(PARSE_OK, parse(&v, json));
		EXPECT_EQ_INT(M_NUMBER, get_type(&v));
		EXPECT_EQ_DOUBLE(expect, get_number(&v));
		json_free(&v);
	} while (0);
}
static void test_parse_number() {
	TEST_NUMBER(0.0, "0");
	TEST_NUMBER(0.0, "-0");
	TEST_NUMBER(0.0, "-0.0");
	TEST_NUMBER(1.0, "1");
	TEST_NUMBER(-1.0, "-1");
	TEST_NUMBER(1.5, "1.5");
	TEST_NUMBER(-1.5, "-1.5");
	TEST_NUMBER(3.1416, "3.1416");
	TEST_NUMBER(1E10, "1E10");
	TEST_NUMBER(1e10, "1e10");
	TEST_NUMBER(1E+10, "1E+10");
	TEST_NUMBER(1E-10, "1E-10");
	TEST_NUMBER(-1E10, "-1E10");
	TEST_NUMBER(-1e10, "-1e10");
	TEST_NUMBER(-1E+10, "-1E+10");
	TEST_NUMBER(-1E-10, "-1E-10");
	TEST_NUMBER(1.234E+10, "1.234E+10");
	TEST_NUMBER(1.234E-10, "1.234E-10");
	TEST_NUMBER(0.0, "1e-10000"); /* must underflow */

	TEST_NUMBER(1.0000000000000002, "1.0000000000000002"); /* the smallest number > 1 */
	TEST_NUMBER(4.9406564584124654e-324, "4.9406564584124654e-324"); /* minimum denormal */
	TEST_NUMBER(-4.9406564584124654e-324, "-4.9406564584124654e-324");
	TEST_NUMBER(2.2250738585072009e-308, "2.2250738585072009e-308");  /* Max subnormal double */
	TEST_NUMBER(-2.2250738585072009e-308, "-2.2250738585072009e-308");
	TEST_NUMBER(2.2250738585072014e-308, "2.2250738585072014e-308");  /* Min normal positive double */
	TEST_NUMBER(-2.2250738585072014e-308, "-2.2250738585072014e-308");
	TEST_NUMBER(1.7976931348623157e+308, "1.7976931348623157e+308");  /* Max double */
	TEST_NUMBER(-1.7976931348623157e+308, "-1.7976931348623157e+308");
}


void TEST_STRING(const char * expect, const char* json) {
	do {
		json_value v;
		prase_init(&v);
		EXPECT_EQ_INT(PARSE_OK, parse(&v, json));
		EXPECT_EQ_INT(M_STRING, get_type(&v)); 
		EXPECT_EQ_STRING(expect, get_string(&v), get_string_len(&v));
		json_free(&v);
	} while (0);
}

//#define TEST_STRING(expect, json)\
//    do {\
//        json_value v;\
//        prase_init(&v);\
//        EXPECT_EQ_INT(PARSE_OK, parse(&v, json));\
//        EXPECT_EQ_INT(M_STRING, get_type(&v));\
//        EXPECT_EQ_STRING(expect, get_string(&v), get_string_len(&v));\
//        json_free(&v);\
//    } while(0)

static void test_parse_string() {
	TEST_STRING("", "\"\"");
	TEST_STRING("Hello", "\"Hello\"");
	TEST_STRING("Hello\nWorld", "\"Hello\\nWorld\"");
	TEST_STRING("\" \\ / \b \f \n \r \t", "\"\\\" \\\\ \\/ \\b \\f \\n \\r \\t\"");
	TEST_STRING("Hello\0World", "\"Hello\\u0000World\"");
	TEST_STRING("\x24", "\"\\u0024\"");         /* Dollar sign U+0024 */
	TEST_STRING("\xC2\xA2", "\"\\u00A2\"");     /* Cents sign U+00A2 */
	TEST_STRING("\xE2\x82\xAC", "\"\\u20AC\""); /* Euro sign U+20AC */
	TEST_STRING("\xF0\x9D\x84\x9E", "\"\\uD834\\uDD1E\"");  /* G clef sign U+1D11E */
	TEST_STRING("\xF0\x9D\x84\x9E", "\"\\ud834\\udd1e\"");  /* G clef sign U+1D11E */
}

static void test_parse_array() {
	size_t i, j;
	json_value v;

	prase_init(&v);
	EXPECT_EQ_INT(PARSE_OK, parse(&v, "[ ]"));
	EXPECT_EQ_INT(M_ARRAY, get_type(&v));
	EXPECT_EQ_SIZE_T(0, get_array_size(&v));
	json_free(&v);

	prase_init(&v);
	EXPECT_EQ_INT(PARSE_OK, parse(&v, "[ null , false , true , 123 , \"abc\" ]"));
	EXPECT_EQ_INT(M_ARRAY, get_type(&v));
	EXPECT_EQ_SIZE_T(5, get_array_size(&v));
	EXPECT_EQ_INT(M_TEXT_NULL, get_type(get_array_element(&v, 0)));
	EXPECT_EQ_INT(M_TEXT_FALSE, get_type(get_array_element(&v, 1)));
	EXPECT_EQ_INT(M_TEXT_TRUE, get_type(get_array_element(&v, 2)));
	EXPECT_EQ_INT(M_NUMBER, get_type(get_array_element(&v, 3)));
	EXPECT_EQ_INT(M_STRING, get_type(get_array_element(&v, 4)));
	EXPECT_EQ_DOUBLE(123.0, get_number(get_array_element(&v, 3)));
	EXPECT_EQ_STRING("abc", get_string(get_array_element(&v, 4)), get_string_len(get_array_element(&v, 4)));
	json_free(&v);

	prase_init(&v);
	EXPECT_EQ_INT(PARSE_OK, parse(&v, "[ [ ] , [ 0 ] , [ 0 , 1 ] , [ 0 , 1 , 2 ] ]"));
	cout << endl;
	for (int i = 0; i < 4; i++) {
		printf("%d\n", v.type);
	}
	EXPECT_EQ_INT(M_ARRAY, get_type(&v));
	cout << "size是:" << get_array_size(&v) << endl;
	EXPECT_EQ_SIZE_T(5, get_array_size(&v));
	for (i = 0; i < 4; i++) {
		json_value* a = get_array_element(&v, i);
		EXPECT_EQ_INT(M_ARRAY, get_type(a));
		EXPECT_EQ_SIZE_T(i, get_array_size(a));
		for (j = 0; j < i; j++) {
			json_value* e = get_array_element(a, j);
			EXPECT_EQ_INT(M_NUMBER, get_type(e));
			EXPECT_EQ_DOUBLE((double)j, get_number(e));
		}
	}
	json_free(&v);
}

static void test_parse_expect_value() {
	TEST_ERROR(PARSE_EXPECT_VALUE, "");
	TEST_ERROR(PARSE_EXPECT_VALUE, " ");
}

static void test_parse_invalid_value() {
	TEST_ERROR(PARSE_INVALID_VALUE, "nul");
	TEST_ERROR(PARSE_INVALID_VALUE, "?");

	/* invalid number */
	cout << endl;
	TEST_ERROR(PARSE_INVALID_VALUE, "+0");
	TEST_ERROR(PARSE_INVALID_VALUE, "+1");
	TEST_ERROR(PARSE_INVALID_VALUE, ".123"); /* at least one digit before '.' */
	TEST_ERROR(PARSE_INVALID_VALUE, "1.");   /* at least one digit after '.' */
	TEST_ERROR(PARSE_INVALID_VALUE, "INF");
	TEST_ERROR(PARSE_INVALID_VALUE, "inf");
	TEST_ERROR(PARSE_INVALID_VALUE, "NAN");
	TEST_ERROR(PARSE_INVALID_VALUE, "nan");
}

static void test_parse_root_not_singular() {
	TEST_ERROR(PARSE_ROOT_NOT_SINGULAR, "null x");

	/* invalid number */
	TEST_ERROR(PARSE_ROOT_NOT_SINGULAR, "0123"); /* after zero should be '.' or nothing */
	TEST_ERROR(PARSE_ROOT_NOT_SINGULAR, "0x0");
	TEST_ERROR(PARSE_ROOT_NOT_SINGULAR, "0x123");
}

static void test_parse_number_too_big() {
	TEST_ERROR(PARSE_TO_BIG_NUMBER, "1e309");
	TEST_ERROR(PARSE_TO_BIG_NUMBER, "-1e309");
}

static void test_parse_missing_quotation_mark() {
	TEST_ERROR(PARSE_MISS_QUATATION_MARK, "\"");
	TEST_ERROR(PARSE_MISS_QUATATION_MARK, "\"abc");
}

static void test_parse_invalid_string_escape() {
	TEST_ERROR(PARSE_INVALID_STRING_ESCAPE, "\"\\v\"");
	TEST_ERROR(PARSE_INVALID_STRING_ESCAPE, "\"\\'\"");
	TEST_ERROR(PARSE_INVALID_STRING_ESCAPE, "\"\\0\"");
	TEST_ERROR(PARSE_INVALID_STRING_ESCAPE, "\"\\x12\"");
}

static void test_parse_invalid_string_char() {
	TEST_ERROR(PARSE_INVALID_STRING_CHAR, "\"\x01\"");
	TEST_ERROR(PARSE_INVALID_STRING_CHAR, "\"\x1F\"");
}

static void test_parse_invalid_unicode_hex() {
	TEST_ERROR(PARSE_INVALID_UNICODE_HEX, "\"\\u\"");
	TEST_ERROR(PARSE_INVALID_UNICODE_HEX, "\"\\u0\"");
	TEST_ERROR(PARSE_INVALID_UNICODE_HEX, "\"\\u01\"");
	TEST_ERROR(PARSE_INVALID_UNICODE_HEX, "\"\\u012\"");
	TEST_ERROR(PARSE_INVALID_UNICODE_HEX, "\"\\u/000\"");
	TEST_ERROR(PARSE_INVALID_UNICODE_HEX, "\"\\uG000\"");
	TEST_ERROR(PARSE_INVALID_UNICODE_HEX, "\"\\u0/00\"");
	TEST_ERROR(PARSE_INVALID_UNICODE_HEX, "\"\\u0G00\"");
	TEST_ERROR(PARSE_INVALID_UNICODE_HEX, "\"\\u00/0\"");
	TEST_ERROR(PARSE_INVALID_UNICODE_HEX, "\"\\u00G0\"");
	TEST_ERROR(PARSE_INVALID_UNICODE_HEX, "\"\\u000/\"");
	TEST_ERROR(PARSE_INVALID_UNICODE_HEX, "\"\\u000G\"");
	TEST_ERROR(PARSE_INVALID_UNICODE_HEX, "\"\\u 123\"");
}

static void test_parse_invalid_unicode_surrogate() {
	TEST_ERROR(PARSE_INVALID_UNICODE_SURROGATE, "\"\\uD800\"");
	TEST_ERROR(PARSE_INVALID_UNICODE_SURROGATE, "\"\\uDBFF\"");
	TEST_ERROR(PARSE_INVALID_UNICODE_SURROGATE, "\"\\uD800\\\\\"");
	TEST_ERROR(PARSE_INVALID_UNICODE_SURROGATE, "\"\\uD800\\uDBFF\"");
	TEST_ERROR(PARSE_INVALID_UNICODE_SURROGATE, "\"\\uD800\\uE000\"");
}

static void test_access_null() {
	json_value v;
	prase_init(&v);
	set_string(&v, "a", 1);
	set_null(&v);
	EXPECT_EQ_INT(M_TEXT_NULL, get_type(&v));
	json_free(&v);
}

static void test_access_boolean() {
	json_value v;
	prase_init(&v);
	set_string(&v, "a", 1);
	set_boolean(&v, 1);
	EXPECT_TRUE(get_boolean(&v));
	set_boolean(&v, 0);
	EXPECT_FALSE(get_boolean(&v));
	json_free(&v);
}

static void test_access_number() {
	json_value v;
	prase_init(&v);
	set_string(&v, "a", 1);
	set_number(&v, 1234.5);
	EXPECT_EQ_DOUBLE(1234.5, get_number(&v));
	json_free(&v);
}

static void test_access_string() {
	json_value v;
	prase_init(&v);
	set_string(&v, "", 0);
	EXPECT_EQ_STRING("", get_string(&v), get_string_len(&v));
	set_string(&v, "Hello", 5);
	EXPECT_EQ_STRING("Hello", get_string(&v), get_string_len(&v));
	json_free(&v);
}

static void test_parse_miss_comma_or_square_bracket() {
	TEST_ERROR(PARSE_MISS_COMMA_OR_SQUARE_BRACKET, "[1");
	TEST_ERROR(PARSE_MISS_COMMA_OR_SQUARE_BRACKET, "[1}");
	TEST_ERROR(PARSE_MISS_COMMA_OR_SQUARE_BRACKET, "[1 2");
	TEST_ERROR(PARSE_MISS_COMMA_OR_SQUARE_BRACKET, "[[]");
}

static void test_parse() {
	test_parse_null();
	test_parse_true();
	test_parse_false();
	test_parse_number();
	test_parse_string();
	test_parse_expect_value();
	test_parse_invalid_value();
	test_parse_root_not_singular();
	test_parse_number_too_big();
	test_parse_array();
	test_parse_missing_quotation_mark();
	test_parse_invalid_string_escape();
	test_parse_invalid_string_char();
	test_parse_invalid_unicode_hex();
	test_parse_invalid_unicode_surrogate();
	test_parse_miss_comma_or_square_bracket();
	/*test_access_null();
	test_access_boolean();
	test_access_number();
	test_access_string();*/
}

int main() {
	test_parse();
	printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
	printf("\"\"");
	cout << endl;
	const char* ch = "\""; //\"是一个字符
	char x = *ch;
	cout << x << endl;
	return main_ret;
}
