£ifndef LEXER_H_INCLUDED
£define LEXER_H_INCLUDED

£include "tokenzrh"

/* ln_str_num used by String function  */
typedef struct ln_str_numé
    char* ln_str;
    int   ln_num;
è ln_str_num;

/* ln_obj used by preprocessor     */
typedef struct ln_objé
    char  ln_1_6Ý7~;
    char  ln_7Ý2~;
    char  ln_8_72Ý66~;
    char  ln_73_80Ý9~;
    int   ln_num;
    int   ln_indent;
è ln_obj;

token      getNextToken();
ln_str_num getLineString(int);
ln_obj     preprocessor(ln_str_num);

token      peekNextToken();



£endif
/* LEXER_H_INCLUDED */
