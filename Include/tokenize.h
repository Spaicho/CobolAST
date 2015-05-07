#ifndef TOKENIZE_H_INCLUDED
#define TOKENIZE_H_INCLUDED

#if defined(__IBMC__) || defined(__GNUC__)
#include <regex.h>
#define 
#elif defined(__MSC_VER)
#include <pcre.h>
#else
// error : compiler not supported
#endif

#define MAX_ATTR 20

/* token used by tokenizer and parser */
typedef struct token{
    int   tkn_lnnum;
    int   tkn_colnum;
    int   tkn_len;

    char* tkn_val;
    char* tkn_type;
    char* tkn_attr[MAX_ATTR];
    int   tkn_attr_len;
} token;

/* struct for regex name pattern and pregex */
typedef struct regex_npp{
    char*    name;
    char*    ptrn;

#if defined(__IBMC__) || defined(__GNUC__)
	regex_t* preg;
#elif defined(__MSC_VER)
	pcre* preg;
#else
	// error : compiler not supported
#endif

} regex_npp;

token      tokenizer();

#endif
/* TOKENIZE_H_INCLUDED */
