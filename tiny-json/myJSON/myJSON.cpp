#include "myJSON.h"
#include <cassert>

namespace ben {

	#ifndef PARSE_STACK_INIT_SIZE
	#define PARSE_STACK_INIT_SIZE 256
	#endif

	typedef struct { //为了便于交换数据，存在这个结构体里面
		const char* json;
		char* stack;
		size_t size;
		size_t top;
	}context;


	//获取string首字母，如果是期望的就查看下一个
	void expect(context* c, char ch) { 
		do
		{
			assert(*c->json == ch);
			c->json++;
		} while (0);
	}

	bool isDigit029(char ch) {
		return (ch >= '0' && ch <= '9');
	}

	bool isDigit129(char ch) {
		return (ch >= '1' && ch <= '9');
	}



	void prase_init(json_value* v) {
		do {
			v->type = M_TEXT_NULL;
		} while (0);
	}

	void set_null(json_value* v) { //?
		json_free(v);
	}

	static void* context_push(context* c, size_t size) {
		void* ret;
		assert(size > 0);
		if (c->top + size >= c->size) {
			if (c->size == 0)
				c->size = PARSE_STACK_INIT_SIZE;
			while (c->top + size >= c->size)
				c->size += c->size >> 1;  /* c->size * 1.5 右移运算符 */ 
			c->stack = (char*)realloc(c->stack, c->size);
		}
		ret = c->stack + c->top;
		c->top += size;
		return ret;
	}

	void putc(context* c, char ch) {
		do {
			/*char* temp;
			temp = (char*)context_push(c, sizeof(char));
			*temp = ch;*/
			*(char*)context_push(c, sizeof(char)) = (ch);

		} while (0);
	}

//#define putc(c, ch) do { *(char*)context_push(c, sizeof(char)) = (ch); } while(0)

	static void *context_pop(context* c, size_t size) {//void返回类型
		assert(c->top >= size);
		return c->stack + (c->top -= size);
	}

	static void parse_whitespace(context* c) {
		const char* p = c->json;
		while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
			p++;
		c->json = p;
	}

	static int parse_literal(context* c, json_value* v, const char* literal, json_type type) {
		size_t i;
		expect(c, literal[0]);
		for (i = 0; literal[i + 1]; i++)
			if (c->json[i] != literal[i + 1])
				return PARSE_INVALID_VALUE;
		c->json += i;
		v->type = type;
		return PARSE_OK;
	}

	static int parse_number(context* c, json_value* v) {
		const char* p = c->json;
		//符号开头
		if (*p == '-') p++;
		//单个0
		if (*p == '0') {
			p++;
			printf("%s\n", p);
			if(( * p != '.') && ( * p != NULL)) return PARSE_ROOT_NOT_SINGULAR;
		}
		else {
			printf("%s\n", p);
			if (!isDigit129(*p)) return PARSE_INVALID_VALUE;
			p++;
			while (isDigit029(*p)) {
				p++;
			}
		}
		if (*p == '.') {
			p++;
			if (!isDigit029(*p)) return PARSE_INVALID_VALUE;
			p++;
			while (isDigit029(*p)) {
				p++;
			}
		}
		if (*p == 'e' || *p == 'E') {
			p++;
			if (*p == '+' || *p == '-') p++;
			if (!isDigit029(*p)) return PARSE_INVALID_VALUE;
			p++;
			while (isDigit029(*p)) {
				p++;
			}
		}
		errno = 0;
		v->num = strtod(c->json, NULL);
		if (errno == ERANGE && (v->num == HUGE_VAL || v->num == -HUGE_VAL)) return PARSE_TO_BIG_NUMBER;
		v->type = M_NUMBER;
		c->json = p;
		return PARSE_OK;
	}

	static int parse_string(context* c, json_value* v) {
		size_t head = c->top;
		size_t len;
		const char* p;
		expect(c, '\"');
		p = c->json;
		for (;;) {
			char ch = *p++;
			switch (ch) {
			case '\"':
				len = c->top - head;
				set_string(v, (const char*)context_pop(c, len), len);
				c->json = p;
				return PARSE_OK;
			case '\\':
				switch (*p++) {
				case '\"': putc(c, '\"'); break;
				case '\\': putc(c, '\\'); break;
				case '/':  putc(c, '/'); break;
				case 'b':  putc(c, '\b'); break;
				case 'f':  putc(c, '\f'); break;
				case 'n':  putc(c, '\n'); break;
				case 'r':  putc(c, '\r'); break;
				case 't':  putc(c, '\t'); break;
				default:
					c->top = head;
					return PARSE_INVALID_STRING_ESCAPE;
				}
				break;
			case '\0':
				c->top = head;
				return PARSE_MISS_QUATATION_MARK;
			default:
				if ((unsigned char)ch < 0x20) {
					c->top = head;
					return PARSE_INVALID_STRING_CHAR;
				}
				putc(c, ch);
			}
		}
	}


	static int parse_value(context* c, json_value* v) { 
		switch (*c->json) {
		case 't':  return parse_literal(c, v,"true",M_TEXT_TRUE);
		case 'f':  return parse_literal(c, v, "false", M_TEXT_FALSE);
		case 'n':  return parse_literal(c, v, "null", M_TEXT_NULL);
		case '\0': return PARSE_EXPECT_VALUE;
		case '"':  return parse_string(c, v);
		default:   return parse_number(c,v);
		}
	}

	int parse(json_value* v, const char* json) {
		context c;
		int ret;
		assert(v != NULL);
		c.json = json;
		c.stack = NULL;
		c.size = c.top = 0;
		prase_init(v);
		parse_whitespace(&c);
		if ((ret = parse_value(&c, v)) == PARSE_OK) {
			parse_whitespace(&c);
			if (*c.json != '\0') {
				v->type = M_TEXT_NULL;
				ret = PARSE_ROOT_NOT_SINGULAR;
			}
		}
		assert(c.top == 0);
		free(c.stack);
		return ret;
	}

	void json_free(json_value* v) {
		assert(v != NULL);
		if (v->type == M_STRING) {
			free(v->str.s);
		}
		v->type = M_TEXT_NULL;
	}


	json_type get_type(const json_value* v) {
		assert(v != NULL);
		return v->type;
	}

	int get_boolean(const json_value* v) {
		assert(v != NULL && (v->type == M_TEXT_TRUE || v->type == M_TEXT_FALSE));
		return v->type == M_TEXT_TRUE;
	}

	void set_boolean(json_value* v, int b) {
		json_free(v);
		v->type = b ? M_TEXT_TRUE : M_TEXT_FALSE;
	}

	double get_number(const json_value* v) {
		assert(v != NULL && v->type == M_NUMBER);
		return v->num;
	}
	
	void set_number(json_value* v, double n) {
		json_free(v);
		v->num = n;
		v->type = M_NUMBER;
	}

	const char* get_string(const json_value* v) {
		assert(v != NULL && v->type == M_STRING);
		return v->str.s;
	}


	size_t get_string_len(const json_value* v) {

		assert(v != NULL && v->type == M_STRING);
		return v->str.len;
	}
	void set_string(json_value* v, const char* s, size_t len) {
		printf("打印 %s \n", s);
		assert(v != NULL && (s!=NULL || len == 0));
		json_free(v);
		v->str.s = (char*)malloc(len + 1);
		memcpy(v->str.s, s, len); //复制
		v->str.s[len] = '\0';
		v->str.len = len;
		v->type =  M_STRING;
	}
}