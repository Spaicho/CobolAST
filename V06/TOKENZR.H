£ifndef TOKENZR_H_INCLUDED
£define TOKENZR_H_INCLUDED

£include <regex.h>

£define MAX_ATTR 20

/* token used by tokenizer and parser */
typedef struct tokené
    int   tkn_lnnum;
    int   tkn_colnum;
    int   tkn_len;

    char* tkn_val;
    char* tkn_type;
    char* tkn_attrÝMAX_ATTR~;
    int   tkn_attr_len;
è token;

/* struct for regex name pattern and pregex */
typedef struct regex_nppé
    char*    name;
    char*    ptrn;
    regex_t* preg;
è regex_npp;

token      tokenizer();

£endif
/* TOKENZR_H_INCLUDED */
