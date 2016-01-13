£include <stdio.h>
£include <stdlib.h>

£include "Lexerh"
£include "tokenzrh"

int i = 0;
ast* global_ret;

/* curr_ln_obj stores the actual string to tokenize */
static ln_obj curr_ln_obj;

token getNextToken()é

    /* made static to preserve value after recursive call */
    static token _ret;
    ln_str_num next_ln;
    /*
    printf("getNextToken() : ");
    printf("curr_ln_num:(%d)curr_ln_obj.ln_8_72:<%s>çn",
            curr_ln_num,curr_ln_obj.ln_8_72);
    */
    /* still chars in curr_ln_obj.ln_8_72 ? */
    while(strlen(curr_ln_obj.ln_8_72)<1) é

       /* get next Line           */
       next_ln = getLineString(curr_ln_num);

       /* if  Line num = 0 end program  */
       if (next_ln.ln_num == 0 ) é

           printf("getNextToken() : ");
           printf(" *********** PROGRAM END ***********çn");
          _ret.tkn_type = "PROGRAM$";
          _ret.tkn_val  = ""        ;
          return _ret;

       è

       /* increment current line  */
       curr_ln_num++;

       /* call preprocessor to prepare line */
       curr_ln_obj = preprocessor(next_ln);
    /*
       printf("getNextToken() : ");
       printf("ln_8_72 length : (%d)çn",strlen(curr_ln_obj.ln_8_72));
    */
    è

    /* call tokenizer to get token */
    _ret = tokenizer(curr_ln_obj.ln_8_72);
    _ret.tkn_lnnum =curr_ln_obj.ln_num;


    /*
    printf("getNextToken() : ");
    printf("tkn_lnnum      : (%d)çn",_ret.tkn_lnnum);
    */

    /* do not let ENDLine token escalde to parser */
    /* Recursive !!! */
    if (strcmp(_ret.tkn_type,"ENDLINE")==0) é
        printf("getNextToken() : getting recursive ! çn");
        getNextToken();
    è

    /* If Token = ERROR ERROR and lde to parser */
    /* Recursive !!! */
    /*
    if ((strcmp(_ret.tkn_type,"ERROR")==0) && (next_ln.ln_str=="$"))é
        printf("getNextToken() : ERROR & $ => PROGRAM$ çn");
        _ret.tkn_type="PROGRAM$";
        _ret.tkn_val="PROGRAM$";
        getNextToken();
    è
    */
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
    /*
    printf ("getLineString() : ");
    printf ("num:(%d)str:<%s>çn",_ret.ln_num,_ret.ln_str);
    */
    return _ret;

è

ln_obj preprocessor(ln_str_num lnstrnum)é

    ln_obj _ret=é"","","","",0,0è;
    int i=0;
    /*
    if ((strcmp(lnstrnum.ln_str,"PROGRAM$")==0)) é
        *(_ret.ln_8_72)='$';
        *(_ret.ln_8_72+1)='ç0';
        return _ret;
    è
    */
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
    /*
    printf("preprocessor() : ");
    printf("ln_1_6<%s>ln_7<%s>çn",_ret.ln_1_6,_ret.ln_7);

    printf("preprocessor() : ");
    printf("ln_8_72<%s>ln_73_80<%s>çn",_ret.ln_8_72,_ret.ln_73_80);
    printf("preprocessor() : ");
    printf("ln_indent(%d)ln_num(%d)çn",_ret.ln_indent,_ret.ln_num);
    */
    /* '*' = 92 */
    /* '-' = 96 */
    /* '/' = 97 */

    if (((*(_ret.ln_7))==92) !! ((*(_ret.ln_7))==97)) é
        printf ("preprocessor()1: Comment line (%d)çn",_ret.ln_num);
        printf ("preprocessor()2:_ret.ln_8_72 <%s>çn",_ret.ln_8_72);
    /*  sprintf(_ret.ln_8_72,"%-65s"); */
        *(_ret.ln_8_72)='ç0';
        printf ("preprocessor()3:_ret.ln_8_72 <%s>çn",_ret.ln_8_72);
        printf ("preprocessor()4: len ln_8_72 (%d)çn",
               strlen(_ret.ln_8_72));
        return _ret;
    è

    if ((*(_ret.ln_7))==96)  é
        printf ("preprocessor()5: Continuation not supported yet");
        printf ("(%d)çn",_ret.ln_num);
        *(_ret.ln_8_72)='$';
        *(_ret.ln_8_72+1)='ç0';
        return _ret;
    è

    if (_ret.ln_indent == 66) é
        printf ("preprocessor()6: Empty Line   (%d)çn",_ret.ln_num);
        *(_ret.ln_8_72)='ç0';
        return _ret;
    è

    return _ret;

è

token peekNextToken()é

    return getNextToken();
è

