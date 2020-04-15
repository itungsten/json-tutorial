#include "fbkjson.h"
#include <assert.h>
#include <stdlib.h>

#define EXPECT(c,ch)\
    do{\
        assert(*(c->json)==(ch));\
        ++c->json;\
    }while(0)

typedef struct{
    const char * json;
}fbk_context;
//this kind of class user needn't to know
static void fbk_parse_whitespace(fbk_context* c){
    const char *p=c->json;
    while(*p==' '|| *p == '\t'|| *p=='\n'|| *p=='r'){
        ++p;
    }
    c->json=p;
}
static int fbk_parse_null(fbk_context* c,fbk_value *v){
    EXPECT(c,'n');
    //note that this macro function has side effect
    if(c->json[0]!='u' || c->json[1]!='l' || c->json[2]!='l'){
        return FBK_PARSE_INVALID_VALUE;
    }
    c->json+=3;
    v->type=FBK_NULL;
    return FBK_PARSE_OK;
}
static int fbk_parse_false(fbk_context* c,fbk_value *v){
    EXPECT(c,'f');
    //note that this macro function has side effect
    if(c->json[0]!='a' || c->json[1]!='l' || c->json[2]!='s'|| c->json[3]!='e'){
        return FBK_PARSE_INVALID_VALUE;
    }
    c->json+=4;
    v->type=FBK_FALSE;
    return FBK_PARSE_OK;
}
static int fbk_parse_true(fbk_context* c,fbk_value *v){
    EXPECT(c,'t');
    //note that this macro function has side effect
    if(c->json[0]!='r' || c->json[1]!='u' || c->json[2]!='e'){
        return FBK_PARSE_INVALID_VALUE;
    }
    c->json+=3;
    v->type=FBK_TRUE;
    return FBK_PARSE_OK;
}
static int fbk_parse_value(fbk_context* c,fbk_value * v){
    switch(*c->json){
        case 'n':
            return fbk_parse_null(c,v);
        case '\0':
            return FBK_PARSE_EXPECT_VALUE;
        case 't':
            return fbk_parse_true(c,v);
        case 'f':
            return fbk_parse_false(c,v);
        default:
            return FBK_PARSE_INVALID_VALUE;
    }
}
                
int fbk_parse(fbk_value* v,const char* json){
    fbk_context c;
    assert(v!=NULL);
    c.json=json;
    v->type=FBK_NULL;
    fbk_parse_whitespace(&c);
    return fbk_parse_value(&c,v);
    //fbk_parse use fbk_parse_whitespace and fbk_parse_value
}
fbk_type fbk_get_type(const fbk_value* v){
    assert(v!=NULL);
    return v->type;
}
