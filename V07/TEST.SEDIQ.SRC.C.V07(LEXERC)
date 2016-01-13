£include <stdio.h>
£include <stdlib.h>

£include "Lexerh"
£include "tokenzrh"

int i = 0;

/* curr_ln_obj stores the actual string to tokenize */
static ln_obj curr_ln_obj;

token getNextToken()é

    /* made static to preserve value after recursive call */
    static token _ret;
    ln_str_num next_ln;

    debug_3("curr_ln_num(%d)curr_ln_obj.ln_8_72<%s>çn",
            curr_ln_num,curr_ln_obj.ln_8_72);

    /* still chars in curr_ln_obj.ln_8_72 ? */
    while(strlen(curr_ln_obj.ln_8_72)<1) é

       /* get next Line           */
       next_ln = getLineString(curr_ln_num);

       /* if  Line num = 0 end program  */
       if (next_ln.ln_num == 0 ) é

           debug_1(" *********** PROGRAM END ***********çn");
          _ret.tkn_type = "PROGRAM$";
          _ret.tkn_val  = ""        ;
          return _ret;

       è

       /* increment current line  */
       curr_ln_num++;

       /* call preprocessor to prepare line */
       curr_ln_obj = preprocessor(next_ln);

       debug_3("ln_8_72 length (%d)çn",strlen(curr_ln_obj.ln_8_72));

    è

    /* call tokenizer to get token */
    _ret = tokenizer(curr_ln_obj.ln_8_72);
    _ret.tkn_lnnum =curr_ln_obj.ln_num;

    debug_3("tkn_lnnum      (%d)çn",_ret.tkn_lnnum);


    /* do not let ENDLine token escalde to parser */
    /* Recursive !!! */
    if (strcmp(_ret.tkn_type,"ENDLINE")==0) é
        debug_2(" getting recursive ! çn");
        getNextToken();
    è

    //Traiter Copy
    if(copy_replacing())é
       ;
    è

    return _ret;

è

ln_str_num getLineString (int linenum) é

    ln_str_num _ret;

    /* if current line num > num of last line return $ */
    if(linenum > lnumlast)é

     /*_ret.ln_str = "PROGRAM$"; */
       _ret.ln_num = 0;
    è
    else
    é
       if(linenum < 1)é

     /*   _ret.ln_str = "^";  */
          _ret.ln_num = 0;

       è
       else
       é
           /* else return line from rawcode and line number   */
           _ret.ln_str = rawcodeÝlinenum-1~;
           _ret.ln_num = linenum;
       è

    è
    debug_3("num(%d)str<%s>çn",_ret.ln_num,_ret.ln_str);

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

//
//   PREPROCESSING OF COPY
//

ast*
copy_replacing()é

    debug_9("Trying to match rule : %s çn",__func__);

    ast* ret=NULL;
    ast* copy_ret=NULL;
    ast* lib_ret=NULL;
    int  bool_rplc=0;


    if(match_val("COPY"))é
        ;
    è
    else return NULL;

    // text-name
    if(copy_ret=id_name())é
        ;

    // or literal
    è else if(equal_attr("ALPHANUMERIC"))é

        copy_ret=litr();

    è else return NULL;

    // optional qualifier
    if (equal_val("OF") !! equal_val("IN"))é
       consume();

       // text-name
       if(lib_ret=id_name())é
           ;

       // or literal
       è else if(equal_attr("ALPHANUMERIC"))é

           lib_ret=litr();

       è else return NULL;

    è

    // optional suppress
    if (equal_val("SUPPRESS"))é
       consume();
    è

    /* optional */
    if (equal_val("REPLACING"))é

       if(intlz_rplc())é
           bool_rplc =1;
       è
       else return NULL;

    è

    ret = make_initialize(bool_rplc,0,sub_ret);

    debug_2("Rule recognized: %s çn",__func__);

    return ret;
è

int
intlz_rplc ()
é
    debug_2("Trying to match rule : intlz_rplc çn");

    if(match_val("REPLACING"))é
        ;
    è
    else return 0;

    if(intlz_rplc_oprnds())é
        ;
    è
    else return 0;

    debug_2("Rule recognized: intlz_rplc çn");

    return 1;
è

int
intlz_rplc_oprnds()
é
    debug_2("Trying to match rule : intlz_rplc_oprnds çn");

    int ret = 0;

    while((equal_val("ALPHABETIC"))   !!
          (equal_val("ALPHANUMERIC")) !!
          (equal_val("NUMERIC")))    é

       if(intlz_rplc_oprnd())é
           ;
       è
       else return 0;
       ret = 1;
    è

    if (ret == 1)   debug_2("Rule recognized: intlz_rplc_oprnds çn");
    return ret;
è

int
intlz_rplc_oprnd()é

    debug_2("Trying to match rule : intlz_rplc_oprnd çn");

    if(chartype())é
        ;
    è
    else return 0;

    if(match_val("BY"))é
        ;
    è
    else return 0;

    if (id_litr())é
        ;
    è
    else return 0;

    debug_2("Rule recognized: intlz_rplc_oprnd çn");
    return 1;
è

int
chartype()
é
    debug_2("Trying to match rule : chartype çn");

    if(match_val("ALPHABETIC"))é
        ;
    è
    else if (match_val("ALPHANUMERIC"))é
        ;
    è
    else if (match_val("NUMERIC"))é
        ;
    è
    else return 0;

    debug_2("Rule recognized: chartype çn");
    return 1;
è

