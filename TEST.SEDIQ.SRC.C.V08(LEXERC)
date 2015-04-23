£include <stdio.h>
£include <stdlib.h>
£include "debugh"
£include "Lexerh"
£include "tokenzrh"
£include "grammarh"
£include "rexxcomh"

int i = 0;
_srcLine   *src_list;
_srcLine   *curr_src_line;

/* curr_ln_obj stores the actual string to tokenize */
static ln_obj curr_ln_obj;

token getNextToken()é

    /* made static to preserve value after recursive call */
    static token _ret;
    ln_str_num next_ln;

start:
//  debug_3("curr_ln_num(%d)curr_ln_obj.ln_8_72<%s>çn",
//          curr_ln_num,curr_ln_obj.ln_8_72);

    /* still chars in curr_ln_obj.ln_8_72 ? */
    while(strlen(curr_ln_obj.ln_8_72)<1) é

       /* get next Line           */
//     next_ln = getLineString(curr_ln_num);
       next_ln = getLineString();
    debug_1(" after getLineString curr_src_line(%d)çn",curr_src_line);

       /* if  Line num = 0 end program  */
       if (next_ln.ln_num == 0 ) é

           debug_1(" *********** PROGRAM END ***********çn");
          _ret.tkn_type = "PROGRAM$";
          _ret.tkn_val  = ""        ;
          return _ret;

       è

       /* increment current line  */
//     curr_ln_num++;

       /* call preprocessor to prepare line */
       curr_ln_obj = preprocessor(next_ln);
    debug_1(" after preprocessor curr_src_line (%d)çn",curr_src_line);

       debug_3("ln_8_72 length (%d)çn",strlen(curr_ln_obj.ln_8_72));

    è

    /* call tokenizer to get token */
    _ret = tokenizer(curr_ln_obj.ln_8_72);
    _ret.tkn_lnnum =curr_ln_obj.ln_num;

    debug_3("tkn_lnnum      (%d)çn",_ret.tkn_lnnum);


    /* do not let ENDLINE token escalde to parser */
    /* Recursive !!! */
    if (strcmp(_ret.tkn_type,"ENDLINE")==0) é
//      debug_2(" getting recursive ! çn");
        goto start;
//      getNextToken();
    è

    lookahead = _ret;

    //Traiter Copy
    if(copy_replacing())é
       ;
    è

 debug_1(" after copy rep curr_src_line (%d)(%d)(%s)çn",
                        curr_src_line,&curr_src_line, _ret.tkn_val);
    return _ret;

è

ln_str_num getLineString () é

    ln_str_num _ret;

    debug_1("curr_src_line (%d)çn",curr_src_line);
    debug_1("curr_src_line next (%d)çn",curr_src_line->next);
    debug_1("value         (%s)çn",curr_src_line->value);
    debug_1("num_all       (%d)çn",curr_src_line->num_all);
    debug_1("num_file      (%d)çn",curr_src_line->num_file);
    debug_1("file          (%s)çn",curr_src_line->file);
    if(§curr_src_line)é
       _ret.ln_num = 0;
    è
    else
    é

       /* else return line from rawcode and line number   */
       _ret.ln_str = curr_src_line->value;
       _ret.ln_num = curr_src_line->num_all;
       curr_src_line=curr_src_line->next;

    è
    debug_1("num(%d)str<%s>çn",_ret.ln_num,_ret.ln_str);
    debug_1("strlen(%d)    çn",strlen(_ret.ln_str));
    debug_1("AFTER !!! curr_src_line (%d)çn",curr_src_line);

    return _ret;

è

ln_obj preprocessor(ln_str_num lnstrnum)é

    ln_obj _ret=é"","","","",0,0è;
    int i=0;

    if (strlen(lnstrnum.ln_str)==80)é

       strncpy(_ret.ln_1_6,lnstrnum.ln_str,6);
       *(_ret.ln_1_6+6) = 'ç0';
       strncpy(_ret.ln_7,lnstrnum.ln_str+6,1);
       *(_ret.ln_7+1) = 'ç0';
       strncpy(_ret.ln_8_72,lnstrnum.ln_str+7,65);
       *(_ret.ln_8_72+65) = 'ç0';
       strncpy(_ret.ln_73_80,lnstrnum.ln_str+72,8);
       *(_ret.ln_73_80+8) = 'ç0';

       while (isspace(*(_ret.ln_8_72 + i))) i++;

       _ret.ln_indent= i+1;
       _ret.ln_num=lnstrnum.ln_num;


    è

    /* '*' = 92 */
    /* '-' = 96 */
    /* '/' = 97 */

    if (((*(_ret.ln_7))==92) !! ((*(_ret.ln_7))==97)) é
        debug_2(" Comment line (%d)çn",_ret.ln_num);
        debug_2(" _ret.ln_8_72 <%s>çn",_ret.ln_8_72);
    /*  sprintf(_ret.ln_8_72,"%-65s"); */
        *(_ret.ln_8_72)='ç0';
        debug_2(" _ret.ln_8_72 <%s>çn",_ret.ln_8_72);
        debug_2("  len ln_8_72 (%d)çn",strlen(_ret.ln_8_72));
        return _ret;
    è

    if ((*(_ret.ln_7))==96)  é
        printf(" Continuation not supported line (%d)çn",_ret.ln_num);
        *(_ret.ln_8_72)='$';
        *(_ret.ln_8_72+1)='ç0';
        exit(EXIT_FAILURE);
    è

    if (_ret.ln_indent == 66) é
        debug_2(" Empty Line   (%d)çn",_ret.ln_num);
        *(_ret.ln_8_72)='ç0';
        return _ret;
    è
    return _ret;
è

