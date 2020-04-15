#ifndef FBKJSON_H__
#define FBKJSON_H__

typedef enum{ FBK_NULL, FBK_FALSE, FBK_TRUE, FBK_NUMBER, FBK_STRING, FBK_ARRAY, FBK_OBJECT }
fbk_type;

typedef struct{
    fbk_type type;
}fbk_value;

enum{
    FBK_PARSE_OK,
    FBK_PARSE_EXPECT_VALUE,
    FBK_PARSE_INVALID_VALUE,
    FBK_PARSE_ROOT_NOT_SINGULAR,
};

int fbk_parse(fbk_value* v,const char * json);
fbk_type fbk_get_type(const fbk_value* v);

#endif 
