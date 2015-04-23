£include <stdio.h>
£define __XPG4 // itoa, strccase
£define __UU
£define __OE_8
£include <stdlib.h>
£include <stddef.h>
£include <assert.h>
£include "debugh"
£include "Grammarh"
£include "Lexerh"
£include "asth"

£define MAX_FP_ARR   12
£define COUNT_OF( arr) (sizeof(arr)/sizeof(0›arr~))

context _context=È"","","","","",""Ë;
context save;
ast* build_literal(int);

                     /****************************/

ast*
get_sentence()
È
    ast* ret=NULL;

    if (ret=sntce())È
      ;
    Ë
    else return NULL;

 /* if(ßequal_type("PROGRAM$"))È
       printf("unexpected token (%s)Án",get_token_val());
       return NULL;
    Ë */

    return ret;
Ë

ast*
get_data()
È
    ast* ret=NULL;
    ast* sub_ret=NULL;

    if(ret=data_fields())È
      ;
    Ë
    else return NULL;

 /* if(ßequal_type("PROGRAM$"))È
       printf("unexpected token (%s)Án",get_token_val());
       return NULL;
    Ë */

    return ret;
Ë

/*---------------------------------  Balayeur for DATA      ---------*/

int
balayeur_pgm()È

    // commencer le parcours de pgm ‡ partir du dÈbut
    setCurrLnStrart();
    // get first token
    consume();

    debug_3("token value (%s) token type (%s) Án",get_token_val()
             ,get_token_type());

    // lire jusqua trouver DATA
    while((ßequal_val("DATA")) && (ßequal_type("PROGRAM$"))
                               && (ßequal_type("ERROR")))È
       consume();
    Ë

    if(equal_val("DATA"))È
       return 1;
    Ë else È
       return 0;
    Ë

Ë

/*---------------------------------  file storage        ---------*/
ast*
data_division()È

    ast* ret=NULL;
    ast* file_ret=NULL;
    ast* ws_ret=NULL;
    ast* link_ret=NULL;


    debug_2("Trying to match rule : %s Án",__func__);

    if (match_val("DATA"))È
       ;
    Ë
    else return 0;

    if (match_val("DIVISION"))È
       ;
    Ë
    else return 0;

    if (match_val("."))È
       ;
    Ë
    else return 0;

    if (file_ret=file_section())È
       ;
    Ë

    if (ws_ret=working_storage_section())È
       ;
    Ë

    if (link_ret=linkage_section())È
       ;
    Ë

    if (ßequal_val("PROCEDURE"))È
       printf("expected procedure but found (%s)type(%s)l(%d)c(%d)Án",
              get_token_val(),get_token_type(),get_token_line(),
              get_token_col());
       exit(EXIT_FAILURE);
    Ë

    ret=make_data_div(file_ret,ws_ret,link_ret);

    return ret;

Ë
/*---------------------------------  file storage        ---------*/
ast*
file_section()È


    ast* ret=NULL;

    debug_2("Trying to match rule : %s Án",__func__);

    if(match_val("FILE"))È
       ;
    Ë
    else return 0;

    if(match_val("SECTION"))È
       ;
    Ë
    else return 0;

    if(match_val("."))È
       ;
    Ë
    else return 0;

    // lire jusqua sortir de la file section
    while( ßequal_val("WORKING-STORAGE")
       &&  ßequal_val("LINKAGE")
       &&  ßequal_val("PROCEDURE")
       &&  ßequal_type("PROGRAM$")
       &&  ßequal_type("ERROR"))È
       consume();
    Ë

    if (equal_type("PROGRAM$") !! equal_type("ERROR"))È
       printf("expected working-storage, linkage or procedure Án");
       exit(EXIT_FAILURE);
    Ë

    ret = make_field(NULL, NULL, UNKNOWN_FIELD_NAME, UNKNOWN_FIELD_LVL,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     NULL, NULL, NULL, NULL, NULL, NULL,
                     NULL, NULL, NULL, NULL, NULL, NULL,
                     UNKNOWN_SECTION);

    debug_2("Rule recognized: %s Án",__func__);

    return ret;
Ë

/*---------------------------------  working storage        ---------*/
ast*
working_storage_section()È

    ast* ret= NULL;

    debug_2("Trying to match rule : %s Án",__func__);

    if(match_val("WORKING-STORAGE"))È
       ;
    Ë
    else return ret;

    if(match_val("SECTION"))È
       ;
    Ë
    else return ret;

    if(match_val("."))È
       ;
    Ë
    else return ret;

    /* 1-49, 66, 77 et 88 */
    while  (equal_attr("LEVEL NUMBER"))È

           if(ret=data_fields())È
              ;
           Ë
           else return ret;
    Ë

    if (equal_type("PROGRAM$") !! equal_type("ERROR"))È
       printf("expected linkage or procedure Án");
       exit(EXIT_FAILURE);
    Ë

    debug_2("Rule recognized: %s Án",__func__);

    return ret;
Ë

/*---------------------------------  linkage                ---------*/
ast*
linkage_section()È


    ast* ret=NULL;
    debug_2("Trying to match rule : %s Án",__func__);

    if(match_val("LINKAGE"))È
       ;
    Ë
    else return ret;

    if(match_val("SECTION"))È
       ;
    Ë
    else return ret;

    if(match_val("."))È
       ;
    Ë
    else return ret;

    /* 1-49, 66, 77 et 88 */
    while  (equal_attr("LEVEL NUMBER"))È

           if(ret=data_fields())È
              ;
           Ë
           else return ret;
    Ë

    if (equal_type("PROGRAM$") !! equal_type("ERROR"))È
       printf("expected  procedure Án");
       exit(EXIT_FAILURE);
    Ë


    debug_2("Rule recognized: %s Án",__func__);

    return ret;
Ë

/*---------------------------------  Sentence and Statement ---------*/

ast*
sntce()
È
    ast* ret=NULL;
    ast* stmnt_ret=NULL;

    int nb_statement =  0;
    ast* list_statement = NULL;

    debug_2("Trying to match rule : sntce Án");

    while((equal_val("MOVE"))         !!
          (equal_val("DISPLAY"))      !!
          (equal_val("INITIALIZE")))È

      if(stmnt_ret=stmnt())È

         nb_statement++;
         list_statement = append_list(list_statement,stmnt_ret);

    /*  (ret->node.sentence.nb_statement)++; */
    /* bug tres bizzare: list_statement->next nest pas null mai egale
       au list_statement, le patch est provisoire eet peux causer
       perte de noeud si append de plusieur noeud a la fois */
    /*  ret->node.sentence.list_statement=append_list
                        (ret->node.sentence.list_statement,stmnt_ret);
    */
      Ë
      else return NULL;

    Ë



    /* optional */
    if (equal_val("."))
        consume();

    if (list_statement) È
       ret = make_sentence(nb_statement,list_statement);
       debug_2("Rule recognized: sntce Án");
       return ret;
    Ë
    else return NULL;

Ë

ast*
stmnt()È
    debug_2("Trying to match rule : stmnt Án");

    ast* ret=NULL;

    if (equal_val("MOVE"))È

       if (ret=move())È
           ;
       Ë
       else return NULL;

    Ë
    else if (equal_val("INITIALIZE"))È

       if (ret=intlz())È
           ;
       Ë
       else return NULL;
    Ë
    else if(equal_val("DISPLAY"))È

       if (ret=dsply())È
           ;
       Ë
       else return NULL;
    Ë
    else return NULL;


    debug_2("Rule recognized: stmnt Án.");

    return ret;
Ë

/*--------------------  move, display and initialize Statement ------*/

ast*
move()
È
    debug_2("Trying to match rule : move Án");
/*
    if (move_2()) È
        ;
    Ë
    else if (move_1())È
        ;
    Ë
    else return 0;
*/
    ast* ret=NULL;


    if(match_val("MOVE"))È
        ;
    Ë
    else return 0;

    if (ret=move_oprnd())È
        ;
    Ë
    else return 0;

    debug_2("Rule recognized: move Án");
    return ret;
Ë

ast*
dsply()
È
    debug_2("Trying to match rule : dsply Án");

    ast* ret=NULL;
    ast* sub_ret=NULL;

/*  BUILD AST : DISPLAY_STM */
    ret = make_display(0,0,"",0,NULL);


    if(match_val("DISPLAY"))È
        ;
    Ë
    else return NULL;

    if(sub_ret=ids_litrs())È

        ret->node.display_stm.list_operand=
        append_list(ret->node.display_stm.list_operand,sub_ret);
        /* attention un append peut ajouter plus qu'un seul operand */
        (ret->node.display_stm.nb_operand)++;
    Ë
    else return NULL;

    /* optional */
    if (equal_val("UPON"))È
       if(dsply_upon())È
           ret->node.display_stm.bool_upon =1;
       Ë
       else return NULL;
    Ë

    /* optional */
    if ((equal_val("WITH"))!!(equal_val("NO")))È
       if(dsply_noadv())È
           ret->node.display_stm.bool_no_adv =1;
       Ë
       else return NULL;
    Ë

    debug_2("Rule recognized: dsply Án");

    return ret;
Ë

ast*
intlz()
È
    debug_2("Trying to match rule : intlz Án");

    ast* ret=NULL;
    ast* sub_ret=NULL;
    int  bool_rplc=0;


    if(match_val("INITIALIZE"))È
        ;
    Ë
    else return NULL;

    if(sub_ret=ids())È
        ;
    Ë
    else return NULL;

    /* optional */
    if (equal_val("REPLACING"))È

       if(intlz_rplc())È
           bool_rplc =1;
       Ë
       else return NULL;

    Ë

    ret = make_initialize(bool_rplc,0,sub_ret);

    debug_2("Rule recognized: intlz Án");

    return ret;
Ë

/*------------------ initialize body --------------------------------*/

int
intlz_rplc ()
È
    debug_2("Trying to match rule : intlz_rplc Án");

    if(match_val("REPLACING"))È
        ;
    Ë
    else return 0;

    if(intlz_rplc_oprnds())È
        ;
    Ë
    else return 0;

    debug_2("Rule recognized: intlz_rplc Án");

    return 1;
Ë

int
intlz_rplc_oprnds()
È
    debug_2("Trying to match rule : intlz_rplc_oprnds Án");

    int ret = 0;

    while((equal_val("ALPHABETIC"))   !!
          (equal_val("ALPHANUMERIC")) !!
          (equal_val("NUMERIC")))    È

       if(intlz_rplc_oprnd())È
           ;
       Ë
       else return 0;
       ret = 1;
    Ë

    if (ret == 1)   debug_2("Rule recognized: intlz_rplc_oprnds Án");
    return ret;
Ë

int
intlz_rplc_oprnd()È

    debug_2("Trying to match rule : intlz_rplc_oprnd Án");

    if(chartype())È
        ;
    Ë
    else return 0;

    if(match_val("BY"))È
        ;
    Ë
    else return 0;

    if (id_litr())È
        ;
    Ë
    else return 0;

    debug_2("Rule recognized: intlz_rplc_oprnd Án");
    return 1;
Ë

int
chartype()
È
    debug_2("Trying to match rule : chartype Án");

    if(match_val("ALPHABETIC"))È
        ;
    Ë
    else if (match_val("ALPHANUMERIC"))È
        ;
    Ë
    else if (match_val("NUMERIC"))È
        ;
    Ë
    else return 0;

    debug_2("Rule recognized: chartype Án");
    return 1;
Ë

/*-------------------------- move body ------------------------------*/
/*
int move_1()È

    debug_2("Trying to match rule : move_1 Án");

    if(match("MOVE"))È
        ;
    Ë
    else return  0;

    if(id_litr())È
        ;
    Ë
    else return  0;

    if(match("TO"))È
        ;
    Ë
    else return  0;

    if(ids())È
        ;
    Ë
    else return  0;

    debug_2("Rule recognized: move_1 Án");
    return 1;

Ë
*/
/* backtracking ? */
/*
int move_2()
È
    debug_2("Trying to match rule : move_2 Án");

    if(match("MOVE"))È
        ;
    Ë
    else return  0;

    if(corspnd())È
        ;
    Ë
    else return  0;

    debug_2("Rule recognized: move_2 Án");

    return 1;
Ë
*/
ast*
move_oprnd()È

    debug_2("Trying to match rule : move_oprnd Án");

    ast* ret=NULL;
    ast* sub_ret=NULL;
    ast* g_oprnd=NULL;
    ast* r_oprnd=NULL;
    int  bool_corresp = 0;


    if((equal_val("CORR")) !!
       (equal_val("CORRESPONDING"))) È
       if(sub_ret=corspnd())È
          bool_corresp = 1;
       Ë
       else return NULL;

       if(g_oprnd=id())È
          ;
       Ë
       else return NULL;

       if(match_val("TO"))È
          ;
       Ë
       else return NULL;

       if(r_oprnd=id())È
          ;
       Ë
       else return NULL;

    Ë
    else È

       if(g_oprnd=id_litr())È
          ;
       Ë
       else return NULL;

       if(match_val("TO"))È
          ;
       Ë
       else return NULL;

       if(r_oprnd=ids())È
          ;
       Ë
       else return NULL;
    Ë

    debug_3("g_oprnd (%s) r_oprnd (%s) Án",tagValues›g_oprnd->tag~,
                                          tagValues›r_oprnd->tag~);
    ret=make_move(bool_corresp,0,g_oprnd,r_oprnd);


    /*
    if(id_litr())È
        if(match("TO"))È
            if(ids())È
                ;
            Ë
            else return  0;
        Ë
        else return  0;
    Ë
    else È
        if(corspnd())È
            if(id())È
                if(match("TO"))È
                    if(id())È
                        ;
                    Ë
                    else return  0;
                Ë
                else return  0;
            Ë
            else return  0;
        Ë
        else return  0;
    Ë
    */
    debug_2("Rule recognized: move_oprnd Án");
    return ret;

Ë

ast*
corspnd()
È
    debug_2("Trying to match rule : corspnd Án");

    if(match_val("CORRESPONDING"))È
        ;
    Ë
    else if (match_val("CORR"))È
        ;
    Ë
    else return  NULL;

    ast* ret = make_ast();

    debug_2("Rule recognized : corspnd Án");
    return ret;
Ë

/*--------------------------- display body --------------------------*/

int
dsply_upon()
È
    debug_2("Trying to match rule : dsply_upon Án");

    if(match_val("UPON"))È
        ;
    Ë
    else return  0;

    if(dsply_upon_oprnd())È
        ;
    Ë
    else return  0;

    debug_2("Rule recognized : dsply_upon Án");

    return 1;
Ë

int
dsply_noadv()
È
    debug_2("Trying to match rule : dsply_noadv Án");

    /* optional */
    if (match_val("WITH"))È
        ;
    Ë

    if (match_val("NO"))È
        ;
    Ë
    else return  0;

    if (match_val("ADVANCING"))È
        ;
    Ë
    else return  0;

    debug_2("Rule recognized : dsply_noadv Án");

    return 1;
Ë

int
dsply_upon_oprnd()
È
    debug_2("Trying to match rule : dsply_upon_oprnd Án");

    if(mnemo_or_envir())È
        ;
    Ë
    else return  0;

    debug_2("Rule recognized : dsply_upon_oprnd Án");
    return 1;
Ë

int
mnemo_or_envir()
È
    debug_2("Trying to match rule : mnemo_or_envir Án");

    if(id_name())È
        ;
    Ë
    else return  0;

    debug_2("Rule recognized : mnemo_or_envir Án");
    return 1;
Ë


/*----------------------  Identifiers and Literals ------------------*/

ast*
ids_litrs()
È
    debug_2("Trying to match rule : ids_litrs Án");

    ast* ret    =NULL;
    ast* sub_ret=NULL;

    while(sub_ret=id_litr())È

        ret=append_list(ret,sub_ret);
        ;
    Ë

    if (ret)     debug_2("Rule recognized: ids_litrs (%d) Án",ret);

    return ret;
Ë

ast*
id_litr() È

    debug_2("Trying to match rule : id_litr Án");

    ast* ret=NULL;

    if(equal_type("IDENTIFIER") !! equal_attr("SPECIAL REGISTER"))È

       if (ret=id())È
           ;
       Ë
       else return NULL;

    Ë

    else È

       if (ret=litr())È
           ;
       Ë
       else return NULL;

    Ë

    debug_2("Rule recognized: id_litr Án");
    return ret;
Ë

ast*
ids() È

    debug_2("Trying to match rule : ids Án");

    ast* ret     =NULL;
    ast* sub_ret =NULL;

    while(equal_type("IDENTIFIER") !! equal_attr("SPECIAL REGISTER"))È
       if(sub_ret=id())È

          ret = append_list(ret,sub_ret);

       Ë
       else return NULL;
    Ë

    if (ret)     debug_2("Rule recognized: ids Án");
    return ret;
Ë

/*-----------------------  Identifier and Literal -------------------*/

ast*
litr() È

    debug_2("Trying to match rule : litr Án");

    ast* ret=NULL;


    /* figurative constants */
    if (equal_attr("FIGURATIVE CONST"))È

        if (ret=figurative_constants())È
           ;
        Ë
        else return NULL;
    Ë
    else

    /* nonnumeric and numeric literals  */
    if (equal_type("LITERAL"))È

    /*  BUILD AST : LITERAL */
        ret=build_literal(0);
        consume();
    Ë
    else return  NULL;

    debug_2("Rule recognized: litr Án");
/*  printf("ret tag (%s)(%d) Án",tagValues›ret->tag~,ret->tag);
*/  return ret;
Ë

ast*
figurative_constants() È

    ast* ret=NULL;
    ast* figurative_ret=NULL;

    int bool_all=0;

    debug_2("Trying to match rule : figurative_constants Án");

    if(equal_val("ALL"))È

       bool_all = 1;
       consume();

    Ë
       /* QUOTED  est prÈsent ici dans le cas ou ALL est consommÈ */
    if (equal_attr("QUOTED")       !!
        equal_val ("ZERO")         !!
        equal_val ("ZEROS")        !!
        equal_val ("ZEROES")       !!
        equal_val ("SPACE")        !!
        equal_val ("SPACES")       !!
        equal_val ("HIGH-VALUE")   !!
        equal_val ("HIGH-VALUES")  !!
        equal_val ("LOW-VALUE")    !!
        equal_val ("LOW-VALUES")   !!
        equal_val ("QUOTE")        !!
        equal_val ("QUOTES"))È

       /*  BUILD AST : LITERAL */
       figurative_ret = build_literal(bool_all);
       ret=append_list(ret,figurative_ret);

       consume();

    Ë
    else return NULL;

    debug_2("Rule recognized: figurative_constants Án");
    return ret;
Ë

ast*
id() È

    debug_2("Trying to match rule : id Án");

    ast* ret=NULL;
    ast* sub_ret=NULL;

    ast* name_ret=NULL;
    ast* qualif_ret=NULL;
    ast* subscr_ret=NULL;
    ast* refmod_ret=NULL;

    if (equal_attr("SPECIAL REGISTER"))È
       if (sub_ret=special_register())È
          ret=append_list(ret,sub_ret);
       Ë
    Ë
    else È

       if (sub_ret=id_name())È
           name_ret=append_list(name_ret,sub_ret);
           ;
       Ë
       else return NULL;

       /* optional */
       if (equal_val("OF"))È
          if (sub_ret=id_qualif())È
              qualif_ret=append_list(qualif_ret,sub_ret);
              ;
          Ë
          else return  NULL;
       Ë

       /* optional subscript and refmodifier */
       if (equal_val("("))È

           /* une fois rentrÈ, ca devient obligatoire */
           if (sub_ret=id_subs_refm())È
            debug_3("id_subs_refm ret->tag (%s) ret->next (%d) Án",
            tagValues›sub_ret->tag~,sub_ret->next);

           /* separer les noeuds subs de refm */
              if(sub_ret->tag==IDENT_SUBSCRIPT)È
                 subscr_ret = sub_ret;
                 if (sub_ret->next->tag==IDENT_REFMOD)È
                    refmod_ret = sub_ret->next;
                    subscr_ret->next = NULL;
                 Ë
              Ë
              else È
                 if(sub_ret->tag==IDENT_REFMOD)È
                    refmod_ret = sub_ret;
                    if(sub_ret->next) È
                       debug_3("refmod has a next !Án");
                       exit(EXIT_FAILURE);
                    Ë
                 Ë
              Ë
           Ë
           else return  NULL;
       Ë



       ret=make_identifier(0,0,0,name_ret,qualif_ret,subscr_ret,
                                                     refmod_ret);
    Ë

    debug_2("Rule recognized: id Án");
    return ret;
Ë


ast*
special_register() È

    debug_2("Trying to match rule : special_register Án");

    ast* ret    =NULL;
    ast* sub_ret=NULL;

    int bool_length=0;
    int bool_address=0;

    /* gestion de special register avec OF */
    if ((equal_val("LENGTH")) !! (equal_val("ADDRESS")))È

       if(equal_val("LENGTH"))  bool_length  =1;
       if(equal_val("ADDRESS")) bool_address =1;

       consume();

       if(match_val("OF"))È
          ;
       Ë
       else return NULL;

       if (sub_ret=id())È

           ret=append_list(ret,sub_ret);
           ret->node.identifier.bool_length =bool_length;
           ret->node.identifier.bool_address=bool_address;

       Ë
       else return NULL;

    Ë
    else

       if(equal_attr("SPECIAL REGISTER"))È
          ret=make_identifier(bool_length,bool_address,1,
              make_ident_name(get_token_len(),get_token_val()),
                                              NULL,NULL,NULL);
          consume();
       Ë
       else return NULL;


    debug_2("Rule recognized: special_register Án");
    return ret;
Ë

ast*
id_name_qualif()
È
    ast* ret    =NULL;
    ast* sub_ret=NULL;
    ast* name_ret=NULL;
    ast* qualif_ret=NULL;

/*  ret = make_ident_name_qualif(NULL,NULL); */


    if (name_ret=id_name())È
/*      ret->node.ident_name_qualif.name=sub_ret; */
    Ë
    else return NULL;

    /* optional */
    if (equal_val("OF"))È
       if (qualif_ret=id_qualif())È
/*        ret->node.ident_name_qualif.qualif=sub_ret; */
          ;
       Ë
       else return NULL;
    Ë

    ret=make_identifier(0,0,0,name_ret,qualif_ret,NULL,NULL);

    return ret;

Ë

ast*
id_names()
È
    ast* ret    =NULL;
    ast* sub_ret=NULL;

    debug_2("Trying to match rule : id_names Án");

    while(equal_type("IDENTIFIER"))È

        if (sub_ret=id_name())È

           ret=append_list(ret,sub_ret);
        Ë
        else return NULL;

    Ë

    if(ret) debug_2("Rule recognized: id_names Án");

    return ret;
Ë

ast*
id_name()
È
    debug_2("Trying to match rule : id_name Án");

    ast* ret    =NULL;
    ast* sub_ret=NULL;

    if (equal_type("IDENTIFIER"))È
        ret=make_ident_name(get_token_len(),get_token_val());
        consume();
    Ë
    else return NULL;

    debug_2("Rule recognized: id_name Án");
    return ret;
Ë

ast*
id_qualif()
È
    debug_2("Trying to match rule : id_qualif Án");

    ast* ret    =NULL;
    ast* sub_ret=NULL;
    ret=make_ident_qualif(NULL);

    while (equal_val("OF"))È
       if(sub_ret=id_qualif_oprnd())È
           ret->node.ident_qualif.list_qualif=
               append_list(ret->node.ident_qualif.list_qualif,sub_ret);
       Ë
       else return NULL;

    Ë

    if (ret)     debug_2("Rule recognized: id_qualif Án");
    return ret;

Ë

ast*
id_qualif_oprnd ()È

    ast* ret    =NULL;
    ast* sub_ret=NULL;

    debug_2("Trying to match rule : id_qualif_oprnd Án");

    if (match_val("OF"))È
        ;
    Ë
    else return NULL;

    if(sub_ret=id_name())È
        ret=append_list(ret,sub_ret);
    Ë
    else return NULL;

    debug_2("Rule recognized: id_qualif_oprnd Án");
    return ret;
Ë
/* continue implementing ast here ... */
ast*
id_subs_refm()È

    ast* ret    =NULL;
    ast* sub_ret=NULL;
    ast* oprnd1 =NULL;

    debug_2("Trying to match rule : id_subs_refm Án");

    if (match_val("("))È
        ;
    Ë
    else return NULL;
    /* concatener oprnd 1 avec le reste de subs et refm */
    if(oprnd1=id_oprnd_1_subs_refm())È
        ;
    Ë
    else return NULL;

    if(sub_ret=id_subs_refm_rest())È
        ;
    Ë
    else return NULL;

    debug_3("expecting IDENT_SUBSCRIPT OR REFMOD (%s)Án",
               tagValues›sub_ret->tag~);
    if(sub_ret->tag==IDENT_SUBSCRIPT)È

       ast* head = sub_ret->node.ident_subscript.list_subscript;
       oprnd1->next = head;
       sub_ret->node.ident_subscript.list_subscript = oprnd1;
    Ë
    else if (sub_ret->tag==IDENT_REFMOD)È

       sub_ret->node.ident_refmod.charleft = oprnd1;

    Ë
    else È

       printf("expected IDENT_SUBSCRIPT OR REFMOD but found (%s)Án",
               tagValues›sub_ret->tag~);
       exit(EXIT_FAILURE);
    Ë

    ret=sub_ret;

    /* patch pour enlever length vide */

    if (ret->tag==IDENT_REFMOD)È
       if(ret->node.ident_refmod.length->node.arith_exp.left == NULL)
         ret->node.ident_refmod.length=NULL;
    Ë

    debug_3("id_subs_refm ret->tag (%s) ret->next (%d) Án",
            tagValues›ret->tag~,ret->next);

    debug_2("Rule recognized : id_subs_refm Án");
    return ret;

Ë

ast*
id_oprnd_1_subs_refm()È


    ast* ret    =NULL;
    ast* sub_ret=NULL;

    debug_2("Trying to match rule : id_oprnd_1_subs_refm Án");

    if (sub_ret=arith_expr())È
        ret=append_list(ret,sub_ret);
    Ë
    else return NULL;

    debug_2("Rule recognized : id_oprnd_1_subs_refm Án");
    return ret;

Ë

ast*
id_subs_refm_rest()È

    debug_2("Trying to match rule : id_subs_refm_rest Án");

    ast* ret    =NULL;
    ast* sub_ret=NULL;

    ast* refmod_ret=NULL;
    ast* subscript_ret=NULL;

    if (equal_val(":"))È
        if (sub_ret=id_refm_rest())È
           /* null pour charleft a remplacer par oprnd 1 */
           refmod_ret=make_ident_refmod(NULL,sub_ret);
           ret=append_list(ret,refmod_ret);
           ;
        Ë
        else return NULL;
    Ë
    else if (sub_ret=id_subs_rest())È
             /* 1er subscript absent/coquille: remplacer par oprnd 1 */
             subscript_ret=make_ident_subscript(sub_ret);
             ret=append_list(ret,subscript_ret);

             if (equal_val("("))È
                if (sub_ret=id_refmodif())È
                    /* refmod ast est cree par id_refmodif */
                    ret=append_list(ret,sub_ret);
                    ;
                Ë
                else return  NULL;
             Ë

    Ë

    else return  NULL;

    /* ret = soit refmod sans charleft, soit subscripts avec premier
             subscript coquille si seul ou absent si plusieurs
             puis refmod ou non mais complet (car subscript avant) */

    debug_2("Rule recognized : id_subs_refm_rest Án");
    return  ret;

Ë

ast*
id_refm_rest()
È
    debug_2("Trying to match rule : id_refm_rest Án");

    ast* ret    =NULL;
    ast* sub_ret=NULL;


    if (match_val(":"))È
        ;
    Ë
    else return  NULL;
    /* length peut etre une arith_exp vide */
    if(sub_ret=refmodif_length())È
        /* arith_exp */
        ret=append_list(ret,sub_ret);
    Ë
    else return  NULL;

    if (match_val(")"))È
        ;
    Ë
    else return  NULL;

    debug_2("Rule recognized : id_refm_rest Án");
    return  ret;

Ë

ast*
id_subs_rest()
È
    debug_2("Trying to match rule : id_subs_rest Án");

    ast* ret    =NULL;
    ast* sub_ret=NULL;

    if (match_val(")"))È
        /* creation d'une coquille AST pour le premier subscript */
        ret=make_arith_exp("","","",NULL,NULL);
        ;
    Ë
    else
    È
        if(sub_ret=subscripts())È

            ret=append_list(ret,sub_ret);

            if (match_val(")"))È
                ;
            Ë
            else return  NULL;
        Ë
        else return  NULL;
    Ë

    debug_2("Rule recognized : id_subs_rest Án");
    return  ret;

Ë

ast*
id_subscript()
È
    debug_2("Trying to match rule : id_subscript Án");

    ast* ret    =NULL;
    ast* sub_ret=NULL;


    if (match_val("("))È
        ;
    Ë
    else return  NULL;

    if(sub_ret=subscripts())È
        ret=append_list(ret,sub_ret);
    Ë
    else return  NULL;

    if (match_val(")"))È
        ;
    Ë
    else return  NULL;

    debug_2("Rule recognized: id_subscript Án");
    return ret;
Ë

ast*
id_refmodif()
È
    debug_2("Trying to match rule : id_refmodif Án");

    ast* ret    =NULL;
    ast* sub_ret=NULL;


    if (match_val("("))È
        ;
    Ë
    else return  NULL;

    if(sub_ret=refmodif())È
        ret=append_list(ret,sub_ret);
    Ë
    else return  NULL;

    if (match_val(")"))È
        ;
    Ë
    else return  NULL;

    debug_2("Rule recognized: id_refmodif Án");
    return ret;
Ë


/*---------------------------  Identifier body ----------------------*/

ast*
subscripts()
È
    debug_2("Trying to match rule : subscripts Án");


    ast* ret    =NULL;
    ast* sub_ret=NULL;

    while(sub_ret=subscript())È
        ret=append_list(ret,sub_ret);
    Ë

    if (ret)     debug_2("Rule recognized: subscripts Án");
    return ret;
Ë

ast*
subscript()
È
    debug_2("Trying to match rule : subscript Án");

    ast* ret    =NULL;
    ast* sub_ret=NULL;

    if (sub_ret=arith_expr2())È
        ret=append_list(ret,sub_ret);
    Ë
    else return  NULL;

    debug_2("Rule recognized: subscript Án");
    return ret;
Ë

ast*
refmodif()
È

    ast* ret    =NULL;
    ast* charleftpos_ret=NULL;
    ast* refmodif_length_ret=NULL;

    debug_2("Trying to match rule : refmodif Án");

    if(charleftpos_ret=charleftpos())È
        ;
    Ë
    else return  NULL;

    if(match_val(":"))È
        ;
    Ë
    else return  NULL;

    /* it's optional !! */
    if(refmodif_length_ret=refmodif_length())È
        ;
    Ë
    else return  NULL;

    ret=make_ident_refmod(charleftpos_ret,refmodif_length_ret);

    debug_2("Rule recognized: refmodif Án");
    return ret;
Ë

ast*
charleftpos()
È

    ast* ret    =NULL;
    ast* sub_ret=NULL;

    debug_2("Trying to match rule : charleftpos Án");

    if (sub_ret=arith_expr())È
        ret=append_list(ret,sub_ret);
    Ë
    else return  NULL;

    debug_2("Rule recognized: charleftpos Án");
    return ret;
Ë

ast*
refmodif_length()
È
    debug_2("Trying to match rule : refmodif_length Án");

    /*optional */

    ast* ret    =NULL;


    if(ßequal_val(")"))È
       if (ret=arith_expr())È
           ;
       Ë
       else return NULL;
    Ë
    else È
       ret=make_arith_exp("","","",NULL,NULL);

    Ë
    debug_2("Rule recognized: refmodif_length Án");
    return ret;
Ë


/*-------------------------  Arithmetic expression ------------------*/
/*
int arith_expr_old()
È
    debug_2("Trying to match rule : arith_expr_old Án");

    if(arith_expr_oprnd())È
        ;
    Ë
    else return  0;

       optional
    if(arith_expr_oprtn())È
        if(arith_expr())È
            ;
        Ë
        else return  0;
    Ë

    debug_2("Rule recognized: arith_expr_old Án");
    return 1;
Ë
*/
ast*
arith_expr()
È
    debug_2("Trying to match rule : arith_expr Án");

    ast* ret    =NULL;
    ast* sub_ret=NULL;

    ast* left   =NULL;
    ast* right  =NULL;
    char oper›3~="";

    if(left=times_div())È
        /* attention aux variables string */
        ret=make_arith_exp("","","",left,NULL);
        ;
    Ë
    else return  NULL;

    while((equal_val("+")) !! (equal_val("-")))È

       strcpy(oper,get_token_val());
       strcpy(ret->node.arith_exp.oper,oper);
       strcpy(oper,"");
       consume();

       if(right=times_div())È
          ret->node.arith_exp.right = right;
       Ë
       else return NULL;

       ret=make_arith_exp("","","",ret,NULL);
    Ë

    debug_2("Rule recognized: arith_expr Án");
    return ret;
Ë

ast*
times_div()
È
    debug_2("Trying to match rule : times_div Án");

    ast* ret    =NULL;
    ast* sub_ret=NULL;

    ast* left   =NULL;
    ast* right  =NULL;
    char oper›3~="";


    if(left=power())È
        /* attention aux variables string */
        ret=make_arith_exp("","","",left,NULL);
        ;
    Ë
    else return  NULL;

    while((equal_val("*")) !! (equal_val("/")))È

       strcpy(oper,get_token_val());
       strcpy(ret->node.arith_exp.oper,oper);
       strcpy(oper,"");
       consume();

       if(right=power())È
          ret->node.arith_exp.right = right;
       Ë
       else return NULL;

       ret=make_arith_exp("","","",ret,NULL);

    Ë

    debug_2("Rule recognized: times_div Án");
    return ret;
Ë

ast*
power()
È
    debug_2("Trying to match rule : power Án");

    ast* ret    =NULL;
    ast* sub_ret=NULL;

    ast* left   =NULL;
    ast* right  =NULL;
    char oper›3~="";
    char sign›3~="";

    if ((equal_val("+")))È

       strcpy(sign,get_token_val());
       consume();
    Ë
    else if((equal_val("-")))È

       strcpy(sign,get_token_val());
       consume();
    Ë

    if(left=basis())È
        /* attention aux variables string */
        ret=make_arith_exp("","",sign,left,NULL);
        strcpy(sign,"");
    Ë
    else return  NULL;

    while((equal_val("**")))È

       strcpy(oper,get_token_val());
       strcpy(ret->node.arith_exp.oper,oper);
       strcpy(oper,"");

       consume();

       if(right=basis())È
          ret->node.arith_exp.right = right;
       Ë
       else return NULL;

       ret=make_arith_exp("","","",ret,NULL);

    Ë

    /* ret est unaire (left seulement) */

    debug_2("Rule recognized: power Án");
    return ret;
Ë

ast*
basis()
È
    debug_2("Trying to match rule : basis Án");


    ast* ret    =NULL;
    ast* sub_ret=NULL;

    if ((equal_type("IDENTIFIER"))!!(equal_attr("SPECIAL REGISTER")))È

       if (sub_ret=id())È
          ret=append_list(ret,sub_ret);
       Ë
       else return NULL;
    Ë
    else if((equal_val("(")))È

            /* bug de caca ! ne pas oublier de consommer le ( */
            consume();

            if (sub_ret=arith_expr())È
               ret=append_list(ret,sub_ret);
            Ë
            else return NULL;

            if (match_val(")"))È
               ;
            Ë
            else return NULL;
         Ë
            /* ZERO/ZEROS/ZEROS inclut */
    else if (equal_attr("NUMERIC"))È

            if(equal_type("LITERAL"))È

               if (sub_ret=litr())È
                  ret=append_list(ret,sub_ret);
               Ë
               else return NULL;
            Ë
            else /* KEYWORD (ZERO/ZEROS/ZEROS) */
            È
               sub_ret=build_literal(0);
               consume();
            Ë

         Ë

    else return NULL;

    debug_2("Rule recognized: basis Án");
    return ret;
Ë

ast*
arith_expr2()
È
    debug_2("Trying to match rule : arith_expr2 Án");

    ast*  ret    =NULL;
    ast*  sub_ret=NULL;

    ast*  left   =NULL;
    ast*  right  =NULL;
    char* oper   =NULL;

    if((equal_attr("INTEGER"))&&(equal_attr("UNSIGNED")))È

        left=build_literal(0);
        consume();

    Ë
    else if(sub_ret=id_name_qualif())È
            /* id_name_qualif retourn dÈsormais un identifier */
            left=make_identifier(0,0,0,
                 sub_ret->node.ident_name_qualif.name,
                 sub_ret->node.ident_name_qualif.qualif,NULL,NULL);


            /* optional */
            if((equal_val("+"))!!(equal_val("-"))) È

               strcpy(oper,get_token_val());
               strcpy(ret->node.arith_exp.oper,oper);
               strcpy(oper,"");
               consume();

               if((equal_attr("INTEGER"))&&(equal_attr("UNSIGNED")))È

                  right=build_literal(0);
                  consume();

               Ë
               else return  NULL;
            Ë

         Ë
    else return NULL;

    ret = make_arith_exp("",oper,"",left,right);

    debug_2("Rule recognized: arith_expr2 Án");
    return ret;
Ë
/*
int arith_expr2_old()
È
    debug_2("Trying to match rule : arith_expr2_old Án");

    if(arith_expr_oprnd())È
        ;
    Ë
    else return  0;

       optional
    if(arith_expr_oprtn())È
        if(arith_expr_oprnd())È
            ;
        Ë
        else return  0;
    Ë

    debug_2("Rule recognized: arith_expr2_old Án");
    return 1;
Ë

int arith_expr_oprnd()
È
    debug_2("Trying to match rule : arith_expr_oprnd Án");

    if (match("INTEGER"))È
        ;
    Ë
    else if (id_name_qualif())È
        ;
    Ë
    else return  0;

    debug_2("Rule recognized: arith_expr_oprnd Án");
    return 1;
Ë

int arith_expr_oprtn()
È
    debug_2("Trying to match rule : arith_expr_oprtn Án");

    if (match("+"))È
        ;
    Ë
    else if (match("-"))È
        ;
    Ë
    else if (match("*"))È
        ;
    Ë
    else return  0;

    debug_2("Rule recognized: arith_expr_oprtn Án");
    return 1;
Ë
*/
/*---------------------- Data declaration    ------------------------*/
ast*
data_fields()È

    debug_2("Trying to match rule : data_fields Án");

    ast* ret=NULL;
    ast* driver=NULL;
    ast* sub_ret=NULL;
    int i;

    static ast* lvl_arr ›89~;

    while(sub_ret=data_field()) È

       debug_2("lvl_arr(%d)=(%d)AVÁn",FLD_LVL(sub_ret)
                                     ,lvl_arr›FLD_LVL(sub_ret)~);

       debug_2("sub_ret(%d)name(%s)lvl(%d)Án",sub_ret,FLD_NAME(sub_ret),
                                                 FLD_LVL(sub_ret));
       if(driver) È
          debug_2("driver(%d)lvl(%d)Án",driver,FLD_LVL(driver));
       Ë

       if(ßret) È
          if(FLD_LVL(sub_ret)==1 !! FLD_LVL(sub_ret)==77)È
             ret=append_list(ret,sub_ret);
             driver=ret;
          Ë else È
             printf("Section must begin with data level 01 or 77Án");
       printf("expected procedure but found (%s)type(%s)l(%d)c(%d)Án",
              get_token_val(),get_token_type(),get_token_line(),
              get_token_col());
             exit(EXIT_FAILURE);
          Ë
       Ë else È
          // gerer field lu lvl 77
          if       (FLD_LVL(sub_ret)==77)È
             debug_2("(%d-%s) == 77 Lonely field Án",
                      FLD_LVL(sub_ret),FLD_NAME(sub_ret));
             if(FLD_LVL(driver)==77)È
                append_list(driver,sub_ret) ; // sister
                // Erasing ...
                for(i=1;i<89;i++) È
                    debug_3(" Erasing lvl arr (%d) Án",i);
                    lvl_arr›i~=NULL;
                Ë

             Ë else if (lvl_arr›1~) È
                append_list(lvl_arr›1~,sub_ret) ; // sister
                for(i=1;i<89;i++) È
                    debug_3(" Erasing lvl arr (%d) Án",i);
                    lvl_arr›i~=NULL;
                Ë

             Ë else È
                printf("Section must begin with data level 01 or 77Án");
       printf("expected procedure but found (%s)type(%s)l(%d)c(%d)Án",
              get_token_val(),get_token_type(),get_token_line(),
              get_token_col());
                exit(EXIT_FAILURE);
             Ë
             driver=sub_ret;

          // gerer field existant lvl 77
          Ë else if(FLD_LVL(driver) == 77)È
             if(FLD_LVL(sub_ret)==1 !! FLD_LVL(sub_ret)==77)È
                debug_2("(%d-%s) New start after 77Án",
                         FLD_LVL(sub_ret),FLD_NAME(sub_ret));
                append_list(driver,sub_ret) ; // sister
                driver=sub_ret;
                for(i=1;i<89;i++) È
                    debug_3(" Erasing lvl arr (%d) Án",i);
                    lvl_arr›i~=NULL;
                Ë
             Ë else È
                printf("Level 77 must be followed by level 01 or 77Án");
                exit(EXIT_FAILURE);
             Ë

          Ë else if(FLD_LVL(driver) == FLD_LVL(sub_ret))È
             FLD_PARENT   (sub_ret) =  FLD_PARENT   (driver);
             FLD_NB_PARENT(sub_ret) =  FLD_NB_PARENT(driver);
             FLD_NB_BCHON (sub_ret) =  FLD_NB_BCHON (driver);
             debug_2("(%d-%s) == (%d-%s) Append to sisterÁn",
                      FLD_LVL(driver) ,FLD_NAME(driver),
                      FLD_LVL(sub_ret),FLD_NAME(sub_ret));
             append_list(driver,sub_ret) ; // sister
             driver=sub_ret;

          Ë else if(FLD_LVL(driver) < FLD_LVL(sub_ret))È
             FLD_PARENT   (sub_ret) =  driver;
             FLD_NB_PARENT(sub_ret) =  FLD_NB_PARENT(driver)+1;
             FLD_NB_BCHON (sub_ret) =  FLD_NB_BCHON (driver);
         //  FLD_CHILD    (driver ) =  sub_ret; // children
             debug_2("(%d-%s) <  (%d-%s) Append to child Án",
                      FLD_LVL(driver) ,FLD_NAME(driver),
                      FLD_LVL(sub_ret),FLD_NAME(sub_ret));

             append_child(driver,sub_ret) ;
             driver=sub_ret;

          Ë else if(FLD_LVL(driver) > FLD_LVL(sub_ret))È

             debug_2("(%d-%s) >  (%d-%s) ",
                      FLD_LVL(driver) ,FLD_NAME(driver),
                      FLD_LVL(sub_ret),FLD_NAME(sub_ret));

             /* parcourir array pour trouver lvl <= lvl du sub_ret */
             for(i=FLD_LVL(sub_ret);i>0;i--) È
                 debug_3("loop lvl array (%d) ",i);
                 if(lvl_arr›i~) È
                    /* nouveau driver est celui trouve */
                    driver=lvl_arr›i~;
                    debug_2(" lvl found(%d-%s)",
                    FLD_LVL(driver) ,FLD_NAME(driver));

                    /* si meme lvl non trouve */
                    if(FLD_LVL(sub_ret)>i) È
                       // append to child
                       // ca rend sub_ret frere des child de driver
                       // du coup deux lvl different peuvent etre freres
                       FLD_PARENT (sub_ret) = driver;
                       FLD_NB_PARENT(sub_ret) = FLD_NB_PARENT(driver)+1;
                       FLD_NB_BCHON (sub_ret) = FLD_NB_BCHON (driver);
                       append_child(driver,sub_ret) ;
                       debug_2("append to child Án");

                    Ë else È /*  i = lvl de sub_ret  */
                       /* append to sister */
                       FLD_PARENT   (sub_ret) = FLD_PARENT   (driver);
                       FLD_NB_PARENT(sub_ret) = FLD_NB_PARENT(driver);
                       FLD_NB_BCHON (sub_ret) = FLD_NB_BCHON (driver);
                       append_list(driver,sub_ret) ;
                       debug_2("append to sister Án");

                    Ë
                    // un field superior trouve quitter
                    break;
                 Ë else È
                    debug_3("not foundÁn");
                 Ë
             Ë

             if(i==0) È

                 printf("field parent not found Án");
                 exit(EXIT_FAILURE);
             Ë

             driver=sub_ret;

             debug_2(" driver lvl > subret lvl Án");
             debug_2(" driver (%d) Án",driver);
             debug_2(" dr-nxt (%d) Án",driver->next);
             debug_2(" subret (%d) Án",sub_ret);
             debug_2(" su-nxt (%d) Án",sub_ret->next);
         //  append_list(driver,sub_ret) ; /* sister */
             debug_2(" driver (%d) Án",driver);
             debug_2(" dr-nxt (%d) Án",driver->next);

             debug_3(" i (%d) Án",i);
             for(++i;i<60;i++) È
                 debug_3(" Erasing lvl arr (%d) Án",i);
                 lvl_arr›i~=NULL;
             Ë

          Ë
       Ë

       debug_3("lvl_arr(%d)= (%d)AP",FLD_LVL(sub_ret),
                lvl_arr›FLD_LVL(sub_ret)~);
       lvl_arr›FLD_LVL(sub_ret)~ = sub_ret;
       debug_3("--> (%d)Án ",sub_ret);

      if (ret) debug_3("(%d-%s) next (%d) child (%s) Án",
             FLD_LVL(ret) ,FLD_NAME(ret),
             ret->next, FLD_NAME(FLD_CHILD(ret)));

    Ë

    if(ret) debug_2("Rule recognized: data_fields Án");


    return ret;

Ë

ast*
data_field()È

    debug_2("Trying to match rule : data_field Án");

    ast* ret=NULL;
    ast* name_ret=NULL;
    ast* sub_ret=NULL;

    field_name field_name;
    field_lvl  field_lvl;
    int  lvl=0;
    char** ptr=NULL;

    if  (equal_attr("LEVEL NUMBER")&&
        ßequal_val ("66")          &&
        ßequal_val ("88")          )È

         if (get_token_val()=="77") È
            field_lvl=LVL_77;
         Ë else È
            field_lvl=LVL_49;
         Ë
         lvl=strtol(get_token_val(),ptr,10);
         consume();

        if (equal_type("IDENTIFIER"))È

           if (name_ret=id_name())È
              ;
           Ë
           else return NULL;
        Ë
        else if (equal_val("FILLER"))È

                name_ret=make_ident_name(get_token_len(),
                                         get_token_val());
                field_name=FILLER;
                consume();
             Ë
             else È
                name_ret=make_ident_name(0,"");
                field_name=SPACE;
             Ë

        if (ret=data_desc())È
           ;
        Ë
        else return NULL;

        if (match_val("."))È
           ;
        Ë
        else return NULL;

    Ë
    else if (equal_attr("LEVEL NUMBER")&&
             equal_val ("66")          )È

             field_lvl =LVL_66;
             lvl=strtol(get_token_val(),ptr,10);
             consume();

        if (name_ret=id_name())È
           ;
        Ë
        else return NULL;

        if (ret=renames_cl())È
           ;
        Ë
        else return NULL;

        if (match_val("."))È
           ;
        Ë
        else return NULL;

    Ë
    else if (equal_attr("LEVEL NUMBER")&&
             equal_val ("88")          )È

             field_lvl =LVL_88;
             lvl=strtol(get_token_val(),ptr,10);
             consume();

        if (name_ret=cond_name())È
           ;
        Ë
        else return NULL;

        if (ret=cond_val_cl())È
           ;
        Ë
        else return NULL;

        if (match_val("."))È
           ;
        Ë
        else return NULL;

    Ë
    else return NULL;

    ret=update_field_init(ret,name_ret,field_name,field_lvl,lvl);


    debug_2("Rule recognized: data_field Án");
    return ret;

Ë
/*---------------------- Declaration  body   ------------------------*/

ast*
cond_name()
È
    debug_2("Trying to match rule : cond_name Án");

    ast* ret=NULL;
    ast* sub_ret=NULL;
    /*
    if (match_type("IDENTIFIER"))È
        ;
    Ë
    else return NULL;
    */

    if(ret=id_name())È

    Ë
    else return NULL;

    debug_2("Rule recognized: cond_name Án");
    return ret;
Ë

/*------*/

ast*
data_desc()
È
    debug_2("Trying to match rule : data_desc Án");

    ast* ret=NULL;
    ast* sub_ret=NULL;
    ast* redefines_ret=NULL;


    /* Not all clauses are compatible with each other */
    /* Semantic for further analysis and elimination */


    /* add permutation */
    /* Union for all the clause to permute */
    /* an array of function pointer        */
    /* a while loop                        */
    /* if a clause is found                */
    /* take it off from the array          */

    /* Known bug : normalement global peut venir avant redefines */
    /* Mais pour nous redefines doit obligatoirement etre en premier */

    if (equal_val("REDEFINES"))È

       if (redefines_ret=data_redefines_cl())È
          ;
       Ë
       else return NULL;
    Ë

    /* Array of clauses to permute      */
    fp_t_nod *clauses;
    clauses = alim_clauses();
    /* print_clauses(clauses); */

    fp_t_nod *iterator= clauses;

    debug_3("Permutation loop start ... Án list head (%d)Án",iterator);

    ret = make_field(NULL, NULL, UNKNOWN_FIELD_NAME, UNKNOWN_FIELD_LVL,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     NULL, NULL, NULL, NULL, NULL, NULL,
                     redefines_ret, NULL, NULL, NULL, NULL, NULL,
                     UNKNOWN_SECTION);
    while (iterator ß= NULL)È

         debug_3("Permutation loop .iterator (%d)Án",iterator);
       /* Known bug : 'IS' is accepted before each clause !! */
       /* if should be for external et gloabal only          */
       /* A deleguer a l'analyse semantique                  */
       if (equal_val("IS"))È

          consume();

       Ë

       /* if lookahead match    */
       if (tkn_in_array(iterator->val.cond_1))È
          /* invoquer la function pointer */
          if (sub_ret=iterator->val.fp())È
             debug_2("Function pointer (%d) invoked after cond Án",
                                                iterator->val.id);
             update_field(ret,sub_ret,iterator->val.tag);
          Ë
          else return NULL;

          /* Reduire la ligne de la liste chainÈe */
          clauses = delete_clauses(clauses,iterator);
          /* Repointer vers la tete de la chaine */
          iterator = clauses;
       Ë
       else
       È
          /* pointer vers le noeud suivant */
          iterator = iterator->next;

       Ë
    Ë

    /* Not implemented clause : Like */
    /* Not implemented clause : Typedef */

    /* Not implemented clause : Type    */

    debug_2("Rule recognized: data_desc Án");
    return ret;
Ë

/*--------------------- Data declaration functions ------------------*/

ast*
data_redefines_cl()È

    debug_2("Trying to match rule : data_redefines_cl Án");

    ast* ret=NULL;

    if (match_val("REDEFINES"))È
       ;
    Ë
    else return NULL;

    if (ret=id_name())È
       ;
    Ë
    else return NULL;

    debug_2("Rule recognized: data_redefines_cl Án");
    return ret;
Ë

/*------*/

ast*
data_external_cl()È

    debug_2("Trying to match rule : data_external_cl Án");

    ast* ret=NULL;
    ast* sub_ret=NULL;

    if (match_val("EXTERNAL"))È
       ret=make_ast();
    Ë
    else return NULL;


    debug_2("Rule recognized: data_external_cl Án");
    return ret;
Ë

/*------*/

ast*
data_blankzero_cl()È

    debug_2("Trying to match rule : data_blankzero_cl Án");

    ast* ret=NULL;


    if (match_val("BLANK"))È
       ;
    Ë
    else return NULL;

    if (equal_val("WHEN"))È

       consume();

    Ë

    if (match_val("ZERO"))È
       ;
    Ë
    else return NULL;

    ret=make_ast();

    debug_2("Rule recognized: data_blankzero_cl Án");
    return ret;
Ë

/*------*/

ast*
data_global_cl()È

    debug_2("Trying to match rule : data_global_cl Án");

    ast* ret=NULL;

    if (match_val("GLOBAL"))È
       ;
    Ë
    else return NULL;

    ret=make_ast();

    debug_2("Rule recognized: data_global_cl Án");
    return ret;
Ë

/*------*/

ast*
data_just_cl()È

    debug_2("Trying to match rule : data_just_cl Án");

    ast* ret=NULL;
    ast* sub_ret=NULL;


    if ((equal_val("JUST"))!!(equal_val("JUSTIFIED")))È

       consume();

    Ë else return NULL; /* ajoutÈ au cours de ast */

    if ((equal_val("RIGHT")))È

       consume();

    Ë

    ret = make_ast();

    debug_2("Rule recognized: data_just_cl Án");
    return ret;
Ë

/*------*/

ast*
data_occurs_cl()È

    debug_2("Trying to match rule : data_occurs_cl Án");

    ast* ret       =NULL;
    ast* sub_ret   =NULL;

    int  times     =0;
    char** ptr     =NULL;
    int  to_times  =0;
    ast* depend_on =NULL;
    ast* keys      =NULL;
    ast* indexes   =NULL;


    if (match_val("OCCURS"))È
       ;
    Ë
    else return NULL;

    if ((equal_attr("INTEGER"))!!(equal_attr("UNSIGNED")))È

       times = strtol(get_token_val(),ptr,10);
       consume();
    Ë
    else return NULL;

    /* Format 2 */
    if ((equal_val("TO")))È

        consume();

        if ((equal_attr("INTEGER"))!!(equal_attr("UNSIGNED")))È

           to_times = strtol(get_token_val(),ptr,10);
           consume();
        Ë
        else return NULL;

        if ((equal_val("TIMES")))È

           consume();
        Ë

        if (match_val("DEPENDING"))È
           ;
        Ë
        else return NULL;

        if ((equal_val("ON")))È

           consume();
        Ë

        if (depend_on=id_name())È
           ;
        Ë
        else return NULL;

        /* Key-indexed-by phrase */

        if ((equal_val("ASCENDING")) !!
            (equal_val("DESCENDING")) )È

            if (keys=data_index_key_cls())È
               ;
            Ë
            else return NULL;
        Ë

        if ((equal_val("INDEX")))È

            if (indexes=data_index_by_cl())È
               ;
            Ë
            else return NULL;
        Ë

    Ë

    /* Format 1 */

    else È

        if ((equal_val("TIMES")))È

           consume();
        Ë

        /* Key-indexed-by phrase */

        if ((equal_val("ASCENDING")) !!
            (equal_val("DESCENDING")) )È

            if (keys=data_index_key_cls())È
               ;
            Ë
            else return NULL;
        Ë

        if ((equal_val("INDEX")))È

            if (indexes=data_index_by_cl())È
               ;
            Ë
            else return NULL;
        Ë

    Ë

    ret=make_occurs(times,to_times,depend_on,keys,indexes);

    debug_2("Rule recognized: data_occurs_cl Án");
    return ret;
Ë

ast* data_index_key_cls()È

    debug_2("Trying to match rule : data_index_key_cls Án");

    ast* ret=NULL;
    ast* sub_ret=NULL;
    int  bool_asc =0;
    int  bool_des =0;

    while ((equal_val("ASCENDING")) !!
           (equal_val("DESCENDING")))È

        if (equal_val("ASCENDING"))  bool_asc = 1;
        else                         bool_des = 1;

        if (sub_ret=data_index_key_cl())È /* names */
           ret=append_list(ret,
                           make_occurs_key(bool_asc,bool_des,sub_ret));
           bool_asc =0;
           bool_des =0;
        Ë
        else return NULL;

    Ë

    if(ret) debug_2("Rule recognized: data_index_key_cls Án");

    return ret; /* occurs_key */
Ë

ast*
data_index_key_cl()È

    debug_2("Trying to match rule : data_index_key_cl Án");

    ast* ret=NULL;

    if ((equal_val("ASCENDING")) !!
        (equal_val("DESCENDING")) )È

       consume();

       if ((equal_val("KEY")))È

          consume();
       Ë

       if ((equal_val("IS")))È

          consume();
       Ë

       if (ret=id_names())È
          ;
       Ë
       else return NULL;

    Ë
    else return NULL;

    debug_2("Rule recognized: data_index_key_cl Án");
    return ret;
Ë

ast*
data_index_by_cl()È

    debug_2("Trying to match rule : data_index_by_cl Án");

    ast* ret=NULL;

    if (match_val("INDEX"))È
       ;
    Ë
    else return NULL;

    if ((equal_val("BY")))È

       consume();
    Ë

    if (ret=id_names())È
       ;
    Ë
    else return NULL;


    debug_2("Rule recognized: data_index_by_cl Án");
    return ret;
Ë

/*------*/

ast*
data_pic_cl()È

    debug_2("Trying to match rule : data_pic_cl Án");

    ast* ret=NULL;
    ast* sub_ret=NULL;


    if(equal_val("PIC")!!equal_val("PICTURE"))È
       save = set_context("data_pic_chars");
       consume();
       ;
    Ë
    else return NULL;

    if (ret=data_pic_str())È
       ;
    Ë
    else return NULL;

    /* restore_context(save);*/


    if (equal_val("SIZE"))È /* ?? */
       if (sub_ret=data_pic_size_local())È
          ;
       Ë
       else return NULL;
    Ë


    /* consommer Space qui vient apres la fin de pic str  (??) */
    if (equal_type("SPACE"))È

       consume();
    Ë


    debug_2("Rule recognized: data_pic_cl Án");
    return ret;
Ë


ast*
data_pic_str()È

    debug_2("Trying to match rule : data_pic_str Án");

    ast* ret=NULL;
    ast* sub_ret=NULL;

    if (equal_val("IS"))È

       consume();
    Ë

    /* Lexer/Parser Hack */
    /* pour ne pas accepter espace apres repeat : */
    /* PIC 9(9) V                                 */
    /* on consomme le premier espace apres pic et IS */
    /* et puis enlever les espaces de token picchar  */

    /* Space */

    if (equal_type("SPACE"))È
       consume();
    Ë
    else return NULL;

    // bug : on ajoute une boucle de consommation space
    //         08 I-EMTITRE-FININFO REDEFINES I-EMTITRE-NSIGFT   PIC
    //   9(7).
    while (equal_type("SPACE"))È
       consume();
    Ë

    /* Currency */
    if (equal_val("$"))È
       sub_ret=make_pic_cmpnt(PIC_CURRENCY,0,"",get_token_val());
       ret=append_list(ret,sub_ret);
       consume();

    Ë

    while (equal_type("PICCHARS"))È

   /*  set_context("data_pic_chars");
   */
       /* PicChars */
       if (sub_ret=data_pic_chars())È
          ret=append_list(ret,sub_ret);
       Ë
       else return NULL;

   /*  restore_context(save);
   */
       /* Repeat */
       if (equal_val("("))È

          if (sub_ret=data_pic_repeat())È
             ret=append_list(ret,sub_ret);
          Ë
          else return NULL;

       Ë
    Ë


    debug_2("Rule recognized: data_pic_str Án");
    return ret;
Ë

/****/

ast*
data_pic_chars()È

    debug_2("Trying to match rule : data_pic_chars Án");

    ast* ret=NULL;
    ast* sub_ret=NULL;
    char chars›120~;


    if (equal_type("PICCHARS"))È
       /* si dernier char de picchar est un point alors */
       /* exiger un point avant la fin de la ligne */
       strcpy(chars,get_token_val());
       consume();
    Ë
    else
    È
       return NULL;
    Ë

    ret=make_pic_cmpnt(PIC_CHARS,0,chars,"");
    strcpy(chars,"");

    debug_2("Rule recognized: data_pic_chars Án");

    return ret;
Ë

ast*
data_pic_repeat()È

    debug_2("Trying to match rule : data_pic_repeat Án");

    ast* ret=NULL;
    ast* sub_ret=NULL;
    int  repeat=0;
    char** ptr=NULL;


    if (match_val("("))È
       ;
    Ë
    else return NULL;

    if ((equal_attr("UNSIGNED"))&&(equal_attr("INTEGER")))È
       repeat=strtol(get_token_val(),ptr,10);
       consume();
    Ë
    else return NULL;

    if (equal_val(")"))È
       set_context("data_pic_chars");
       consume();
    Ë
    else return NULL;

    /* picchar hack */
    if (ßequal_type("PICCHARS"))È
       erase_context();
       if(equal_type("SPACE"))È
          consume();
       Ë
    Ë

    ret=make_pic_cmpnt(PIC_REPEAT,repeat,"","");

    debug_2("Rule recognized: data_pic_repeat Án");
    return ret;
Ë


ast*
data_pic_size_local()È

    debug_2("Trying to match rule : data_pic_size_local Án");

    ast* ret=NULL;
    ast* sub_ret=NULL;


    if (match_val("SIZE"))È
       ;
    Ë
    else return NULL;

    if (equal_val("IS"))È

       consume();

    Ë

    if (match_attr("INTEGER"))È
       ;
    Ë
    else return NULL;

    if (match_val("LOCALE"))È
       ;
    Ë
    else return NULL;

    if (equal_val("IS"))È

       consume();

       if (mnemo_or_envir())È
          ;
       Ë
       else return NULL;
    Ë

    else È
       if (equal_type("IDENTIFIER"))È
          if (mnemo_or_envir())È
             ;
          Ë
          else return NULL;
       Ë
    Ë
    /* clause size and local n'est pas exmploitÈ */
    ret=make_ast();

    debug_2("Rule recognized: data_pic_size_local Án");
    return ret;
Ë

/*------*/

ast*
data_sign_cl()È

    debug_2("Trying to match rule : data_sign_cl Án");

    ast* ret=NULL;
    int  bool_leading=0;
    int  bool_trailing=0;
    int  bool_separate=0;
    int  bool_character=0;

    if (equal_val("SIGN"))È
       consume();

       if (equal_val("IS"))È

          consume();
       Ë
    Ë

    if (equal_val("LEADING"))È
       bool_leading=1;
       consume();

    Ë
    else if(equal_val("TRAILING"))È
             bool_trailing=1;
             consume();
         Ë

    else return NULL;

    if (equal_val("SEPARATE"))È
       bool_separate=1;
       consume();

       if (equal_val("CHARACTER"))È
          bool_character=1;
          consume();
       Ë
    Ë

    ret=make_field_sign(bool_leading,bool_trailing,bool_separate,
                                                   bool_character);
    debug_2("Rule recognized: data_sign_cl Án");
    return ret;
Ë

/*------*/

ast*
data_value_cl()È

    debug_2("Trying to match rule : data_value_cl Án");

    ast* ret=NULL;
    ast* sub_ret=NULL;


    if (match_val("VALUE"))È
       ;
    Ë
    else return NULL;

    if (equal_val("IS"))È

       consume();

    Ë

    if (sub_ret=litr())È
       ;
    Ë
    else return NULL;

    ret=make_field_value(sub_ret,NULL);

    debug_2("Rule recognized: data_value_cl Án");
    return ret;
Ë

/*------*/

ast*
data_sync_cl()È

    debug_2("Trying to match rule : data_sync_cl Án");

    ast* ret=NULL;
    int  bool_right=0;
    int  bool_left=0;

    if ((equal_val("SYNC"))) È

       consume();

    Ë
    else if (equal_val("SYNCHRONIZED"))È

       consume();
    Ë
    else return NULL;

    if ((equal_val("LEFT"))) È
       bool_left=1;
       consume();
    Ë
    else if (equal_val("RIGHT")) È
       bool_right=1;
       consume();

    Ë

    ret=make_field_sync(bool_right,bool_left);

    debug_2("Rule recognized: data_sync_cl Án");
    return ret;
Ë

/*------*/

ast*
data_usage_cl()È

    debug_2("Trying to match rule : data_usage_cl Án");

    ast* ret=NULL;
    usage_t usage;

    if (equal_val("USAGE"))È

       consume();

       if (equal_val("IS"))È

          consume();

       Ë

    Ë

    if (equal_val("BINARY"))È
        usage=BINARY;
        consume();


    Ë else if (equal_val("COMPUTATIONAL"))È
        usage=COMPUTATIONAL;
        consume();

    Ë else if (equal_val("COMP"))È
        usage=COMP;
        consume();

    Ë else if (equal_val("COMPUTATIONAL-1"))È
        usage=COMPUTATIONAL_1;
        consume();

    Ë else if (equal_val("COMP-1"))È
        usage=COMP_1;
        consume();

    Ë else if (equal_val("COMPUTATIONAL-2"))È
        usage=COMPUTATIONAL_2;
        consume();

    Ë else if (equal_val("COMP-2"))È
        usage=COMP_2;
        consume();

    Ë else if (equal_val("COMPUTATIONAL-3"))È
        usage=COMPUTATIONAL_3;
        consume();

    Ë else if (equal_val("COMP-3"))È
        usage=COMP_3;
        consume();

    Ë else if (equal_val("COMPUTATIONAL-4"))È
        usage=COMPUTATIONAL_4;
        consume();

    Ë else if (equal_val("COMP-4"))È
        usage=COMP_4;
        consume();

    Ë else if (equal_val("DISPLAY"))È
        usage=DISPLAY;
        consume();

    Ë else if (equal_val("DISPLAY-1"))È
        usage=DISPLAY_1;
        consume();

    Ë else if (equal_val("INDEX"))È
        usage=INDEX;
        consume();

    Ë else if (equal_val("PACKED-DECIMAL"))È
        usage=PACKED_DECIMAL;
        consume();

    Ë else if (equal_val("POINTER"))È
        usage=POINTER;
        consume();

    Ë else if (equal_val("PROCEDURE-POINTER"))È
        usage=PROCEDURE_POINTER;
        consume();

    Ë else return NULL;

    ret=make_usage(usage);

    debug_2("Rule recognized: data_usage_cl Án");
    return ret;
Ë
/*---------------------- renames and conditional function -----------*/

ast*
renames_cl()
È
    debug_2("Trying to match rule : renames_cl Án");

    ast* ret=NULL;
    ast* renames_ret=NULL;
    ast* id_qualif_ret=NULL;
    ast* thru_id_qualif_ret=NULL;

    if (match_val("RENAMES"))È
        ;
    Ë
    else return NULL;

    if (id_qualif_ret=id_name_qualif())È
        ;
    Ë
    else return NULL;

    if ((equal_val("THROUGH")) !!
        (equal_val("THRU")) )È

       consume();

       if (thru_id_qualif_ret=id_name_qualif())È
           ;
       Ë
       else return NULL;

    Ë

    renames_ret=make_renames(id_qualif_ret,thru_id_qualif_ret);
    ret=make_field(NULL, NULL, UNKNOWN_FIELD_NAME, UNKNOWN_FIELD_LVL,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   NULL, NULL, NULL, NULL, NULL, NULL,
                   NULL, renames_ret , NULL,NULL, NULL, NULL,
                   UNKNOWN_SECTION);
    debug_2("Rule recognized: renames_cl Án");
    return ret;
Ë

ast*
cond_val_cl()
È
    debug_2("Trying to match rule : cond_val_cl Án");

    ast* ret=NULL;
    ast* field_value_ret=NULL;
    ast* sub_ret=NULL;
    ast* value_ret=NULL;
    ast* thru_value_ret=NULL;

    if      (match_val("VALUE"))È
         if (match_val("IS"))È
            ;
         Ë
    Ë
    else if (match_val("VALUES"))È
         if (match_val("ARE"))È
            ;
         Ë
    Ë
    else return NULL;

    while (value_ret=litr())È

       if ((equal_val("THROUGH")) !!
           (equal_val("THRU")) )È

           consume();

          if (thru_value_ret=litr())È
              ;
          Ë
          else return NULL;
       Ë
       sub_ret=make_field_value(value_ret,thru_value_ret);
   /*  value_ret=NULL;
       thru_value_ret=NULL; */
       field_value_ret=append_list(field_value_ret,sub_ret);
    Ë

    ret=make_field(NULL, NULL, UNKNOWN_FIELD_NAME, UNKNOWN_FIELD_LVL,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   NULL, NULL, field_value_ret, NULL, NULL, NULL,
                   NULL, NULL, NULL,NULL, NULL, NULL,UNKNOWN_SECTION);


    debug_2("Rule recognized: cond_val_cl Án");
    return ret;
Ë

//
//   PREPROCESSING OF COPY
//

ast*
copy_replacing()È

    debug_9("Trying to match rule : %s Án",__func__);

    ast* ret=NULL;
    ast* copy_ret=NULL;
    ast* lib_ret=NULL;
    int  bool_rplc=0;


    if(match_val("COPY"))È
        ;
    Ë
    else return NULL;

    // text-name
    if(copy_ret=id_name())È
        ;

    // or literal
    Ë else if(equal_attr("ALPHANUMERIC"))È

        copy_ret=litr();

    Ë else return NULL;

    // optional qualifier
    if (equal_val("OF") !! equal_val("IN"))È
       consume();

       // text-name
       if(lib_ret=id_name())È
           ;

       // or literal
       Ë else if(equal_attr("ALPHANUMERIC"))È

           lib_ret=litr();

       Ë else return NULL;

    Ë

    // optional suppress
    if (equal_val("SUPPRESS"))È
       consume();
    Ë

    /*
    if (equal_val("REPLACING"))È

       if(intlz_rplc())È
           bool_rplc =1;
       Ë
       else return NULL;

    Ë

    ret = make_initialize(bool_rplc,0,sub_ret);
    */
    debug_2("Rule recognized: %s Án",__func__);

    return ret;
Ë


/*---------------------- Context function    ------------------------*/

int
affich_context()È

   debug_2("context.division : <%s>Án", _context.division);
   debug_2("context.section  : <%s>Án", _context.section );
   debug_2("context.sentence : <%s>Án", _context.sentence);
   debug_2("context.clause   : <%s>Án", _context.clause  );
   debug_2("context.keyword  : <%s>Án", _context.keyword );
   debug_2("context.other    : <%s>Án", _context.other   );

   return 1;
Ë

context
set_context(char* clause)È

    context save;

    if(strcmp("data_pic_chars",clause)==0)È

       save = _context;
       _context.division ="DATA";
       _context.section  ="";
       _context.clause   ="data_pic_chars";
       _context.keyword  ="PIC";
       _context.other    ="";

    Ë

    affich_context();

    return  save;

Ë

int
restore_context(context save)È

    _context = save;

    affich_context();

    return  1;

Ë

/*---------------------- Functions for permutation -----------------*/
fp_t_nod*
alim_clauses()È

    /*printf("alim_clauses : Start Án"); */

    fp_t clauses_arr›MAX_FP_ARR~;
    fp_t_nod* head;

    int i=0;

    fp_t_nod* node;
    node  = malloc (sizeof (fp_t_nod));

    clauses_arr›i~.cond_1.len =0;
    clauses_arr›i~.cond_2.len =0;
    clauses_arr›i~.cond_1.arr›0~ = "";
    clauses_arr›i~.cond_2.arr›0~ = "";

    clauses_arr›i~.id = 1;
    clauses_arr›i~.tag= CL_EXTERNAL;
    clauses_arr›i~.fp = data_external_cl;
    clauses_arr›i~.cond_1.arr›0~ = "EXTERNAL";
  /*printf("alim_clauses : alimentation of cond_1 Án");
  */clauses_arr›i~.cond_1.len++;
  /*printf("alim_clauses : Succesful insertion of clause  1 Án");
  *//**/
    node->val      = clauses_arr›i~;
    node->next     = malloc (sizeof (fp_t_nod));
    head           = node;
    node           = node->next;
    /**/
    i++;

    clauses_arr›i~.cond_1.len =0;
    clauses_arr›i~.cond_2.len =0;
    clauses_arr›i~.cond_1.arr›0~ = "";
    clauses_arr›i~.cond_2.arr›0~ = "";

    clauses_arr›i~.id = 2;
    clauses_arr›i~.tag= CL_BLANK_WHEN_ZERO;
    clauses_arr›i~.fp = data_blankzero_cl;
    clauses_arr›i~.cond_1.arr›0~ = "BLANK";
  /*printf("alim_clauses : alimentation of cond_1 Án");
  */clauses_arr›i~.cond_1.len++;
  /*printf("alim_clauses : Succesful insertion of clause  2 Án");
  *//**/
    node->val      = clauses_arr›i~;
    node->next     = malloc (sizeof (fp_t_nod));
    node           = node->next;
    /**/
    i++;

    clauses_arr›i~.cond_1.len =0;
    clauses_arr›i~.cond_2.len =0;
    clauses_arr›i~.cond_1.arr›0~ = "";
    clauses_arr›i~.cond_2.arr›0~ = "";

    clauses_arr›i~.id = 3;
    clauses_arr›i~.tag= CL_GLOBAL;
    clauses_arr›i~.fp = data_global_cl;
    clauses_arr›i~.cond_1.arr›0~ = "GLOBAL";
  /*printf("alim_clauses : alimentation of cond_1 Án");
  */clauses_arr›i~.cond_1.len++;
  /*printf("alim_clauses : Succesful insertion of clause  3 Án");
    /**/
    node->val      = clauses_arr›i~;
    node->next     = malloc (sizeof (fp_t_nod));
    node           = node->next;
    /**/
    i++;

    clauses_arr›i~.cond_1.len =0;
    clauses_arr›i~.cond_2.len =0;
    clauses_arr›i~.cond_1.arr›0~ = "";
    clauses_arr›i~.cond_2.arr›0~ = "";

    clauses_arr›i~.id = 4;
    clauses_arr›i~.tag= CL_JUSTIFIED;
    clauses_arr›i~.fp = data_just_cl;
    clauses_arr›i~.cond_1.arr›0~ = "JUST";
    clauses_arr›i~.cond_1.len++;
    clauses_arr›i~.cond_1.arr›1~ = "JUSTIFIED";
    clauses_arr›i~.cond_1.len++;
  /*printf("alim_clauses : alimentation of cond_1 Án");
    printf("alim_clauses : Succesful insertion of clause  4 Án");
  *//**/
    node->val      = clauses_arr›i~;
    node->next     = malloc (sizeof (fp_t_nod));
    node           = node->next;
    /**/
    i++;

    clauses_arr›i~.cond_1.len =0;
    clauses_arr›i~.cond_2.len =0;
    clauses_arr›i~.cond_1.arr›0~ = "";
    clauses_arr›i~.cond_2.arr›0~ = "";

    clauses_arr›i~.id = 5;
    clauses_arr›i~.tag= CL_OCCURS;
    clauses_arr›i~.fp = data_occurs_cl;
    clauses_arr›i~.cond_1.arr›0~ = "OCCURS";
  /*printf("alim_clauses : alimentation of cond_1 Án");
  */clauses_arr›i~.cond_1.len++;
  /*printf("alim_clauses : Succesful insertion of clause  5 Án");
  *//**/
    node->val      = clauses_arr›i~;
    node->next     = malloc (sizeof (fp_t_nod));
    node           = node->next;
    /**/
    i++;


    clauses_arr›i~.cond_1.len =0;
    clauses_arr›i~.cond_2.len =0;
    clauses_arr›i~.cond_1.arr›0~ = "";
    clauses_arr›i~.cond_2.arr›0~ = "";

    clauses_arr›i~.id = 6;
    clauses_arr›i~.tag= CL_PICTURE;
    clauses_arr›i~.fp = data_pic_cl;
    clauses_arr›i~.cond_1.arr›0~ = "PIC";
    clauses_arr›i~.cond_1.len++;
    clauses_arr›i~.cond_1.arr›1~ = "PICTURE";
    clauses_arr›i~.cond_1.len++;
  /*printf("alim_clauses : alimentation of cond_1 Án");
    printf("alim_clauses : Succesful insertion of clause  6 Án");
  *//**/
    node->val      = clauses_arr›i~;
    node->next     = malloc (sizeof (fp_t_nod));
    node           = node->next;
    /**/
    i++;

    clauses_arr›i~.cond_1.len =0;
    clauses_arr›i~.cond_2.len =0;
    clauses_arr›i~.cond_1.arr›0~ = "";
    clauses_arr›i~.cond_2.arr›0~ = "";

    clauses_arr›i~.id = 7;
    clauses_arr›i~.tag= CL_SIGN;
    clauses_arr›i~.fp = data_sign_cl;
    clauses_arr›i~.cond_1.arr›0~ = "SIGN";
    clauses_arr›i~.cond_1.len++;
    clauses_arr›i~.cond_1.arr›1~ = "LEADING";
    clauses_arr›i~.cond_1.len++;
    clauses_arr›i~.cond_1.arr›2~ = "TRAILING";
    clauses_arr›i~.cond_1.len++;
  /*printf("alim_clauses : alimentation of cond_1 Án");
    printf("alim_clauses : Succesful insertion of clause  7 Án");
  *//**/
    node->val      = clauses_arr›i~;
    node->next     = malloc (sizeof (fp_t_nod));
    node           = node->next;
    /**/
    i++;

    clauses_arr›i~.cond_1.len =0;
    clauses_arr›i~.cond_2.len =0;
    clauses_arr›i~.cond_1.arr›0~ = "";
    clauses_arr›i~.cond_2.arr›0~ = "";

    clauses_arr›i~.id = 8;
    clauses_arr›i~.tag= CL_VALUE;
    clauses_arr›i~.fp = data_value_cl;
    clauses_arr›i~.cond_1.arr›0~ = "VALUE";
    clauses_arr›i~.cond_1.len++;
  /*printf("alim_clauses : alimentation of cond_1 Án");
    printf("alim_clauses : Succesful insertion of clause  8 Án");
  *//**/
    node->val      = clauses_arr›i~;
    node->next     = malloc (sizeof (fp_t_nod));
    node           = node->next;
    /**/
    i++;

    clauses_arr›i~.cond_1.len =0;
    clauses_arr›i~.cond_2.len =0;
    clauses_arr›i~.cond_1.arr›0~ = "";
    clauses_arr›i~.cond_2.arr›0~ = "";

    clauses_arr›i~.id = 9;
    clauses_arr›i~.tag= CL_SYNCHRONIZED;
    clauses_arr›i~.fp = data_sync_cl;
    clauses_arr›i~.cond_1.arr›0~ = "SYNC";
    clauses_arr›i~.cond_1.len++;
    clauses_arr›i~.cond_1.arr›1~ = "SYNCHRONIZED";
    clauses_arr›i~.cond_1.len++;
  /*printf("alim_clauses : alimentation of cond_1 Án");
    printf("alim_clauses : Succesful insertion of clause  9 Án");
  *//**/
    node->val      = clauses_arr›i~;
    node->next     = malloc (sizeof (fp_t_nod));
    node           = node->next;
    /**/
    i++;

    clauses_arr›i~.cond_1.len =0;
    clauses_arr›i~.cond_2.len =0;
    clauses_arr›i~.cond_1.arr›0~ = "";
    clauses_arr›i~.cond_2.arr›0~ = "";

    clauses_arr›i~.id = 10;
    clauses_arr›i~.tag= CL_USAGE;
    clauses_arr›i~.fp = data_usage_cl;
    clauses_arr›i~.cond_1.arr›0~  = "USAGE";
    clauses_arr›i~.cond_1.len++;
    clauses_arr›i~.cond_1.arr›1~  = "BINARY";
    clauses_arr›i~.cond_1.len++;
    clauses_arr›i~.cond_1.arr›2~  = "COMPUTATIONAL";
    clauses_arr›i~.cond_1.len++;
    clauses_arr›i~.cond_1.arr›3~  = "COMP";;
    clauses_arr›i~.cond_1.len++;
    clauses_arr›i~.cond_1.arr›4~  = "COMPUTATIONAL-1";
    clauses_arr›i~.cond_1.len++;
    clauses_arr›i~.cond_1.arr›5~  = "COMP-1";
    clauses_arr›i~.cond_1.len++;
    clauses_arr›i~.cond_1.arr›6~  = "COMPUTATIONAL-2";
    clauses_arr›i~.cond_1.len++;
    clauses_arr›i~.cond_1.arr›7~  = "COMP-2";
    clauses_arr›i~.cond_1.len++;
    clauses_arr›i~.cond_1.arr›8~  = "COMPUTATIONAL-3";
    clauses_arr›i~.cond_1.len++;
    clauses_arr›i~.cond_1.arr›9~  = "COMP-3";
    clauses_arr›i~.cond_1.len++;
    clauses_arr›i~.cond_1.arr›10~ = "COMPUTATIONAL-4";
    clauses_arr›i~.cond_1.len++;
    clauses_arr›i~.cond_1.arr›11~ = "COMP-4";
    clauses_arr›i~.cond_1.len++;
    clauses_arr›i~.cond_1.arr›12~ = "DISPLAY";
    clauses_arr›i~.cond_1.len++;
    clauses_arr›i~.cond_1.arr›13~ = "DISPLAY-1";
    clauses_arr›i~.cond_1.len++;
    clauses_arr›i~.cond_1.arr›14~ = "INDEX";;
    clauses_arr›i~.cond_1.len++;
    clauses_arr›i~.cond_1.arr›15~ = "PACKED-DECIMAL";
    clauses_arr›i~.cond_1.len++;
    clauses_arr›i~.cond_1.arr›16~ = "POINTER";
    clauses_arr›i~.cond_1.len++;
    clauses_arr›i~.cond_1.arr›17~ = "PROCEDURE-POINTER";
    clauses_arr›i~.cond_1.len++;
  /*printf("alim_clauses : alimentation of cond_1 Án");
    printf("alim_clauses : Succesful insertion of clause 10 Án");
  *//**/
    node->val      = clauses_arr›i~;
    node->next     = NULL;
    /**/
    i++;

    /*--------------------------------------------------*/
    /*                                                  */
    /*--------------------------------------------------*/
    /*
    printf("Start for linked list building from array ...(%d)Án",i);

    fp_t_nod* temp;

    fp_t_nod* node = malloc (sizeof (fp_t_nod));
    node->val      = clauses_arr›0~;
    clauses = node;

    temp = clauses->next;

    for(j=1;j<i;j++)È

       printf("iteration (%d) Án",j+1);
       if (temp == NULL) È
          temp = malloc (sizeof (fp_t_nod));
          printf("malloc done Án");
       Ë

       temp->val  = clauses_arr›j~;
       temp->next = NULL;

       clause_print(temp->val,"temp->val");


       clause_nod_print(temp,"temp->val");
       temp = temp->next;

       printf("Creation done Án");

    Ë
    */
    return head;

Ë
/*
int alim_clause_arr(fp_t_arr clauses)È

    printf("alim_clause_arr : Start Án");

    int i=0;
    int j=0;

    if (clause_arr == NULL) È
       clause_arr = malloc(MAX_FUNCTIONS*sizeof(fp_t));
       printf("alim_clause_arr : allocation of MAX_FUNCTIONS size Án");
       for(i=0;i<MAX_FUNCTIONS;i++)È
          (clause_arr+i)->cond_1 = malloc(MAX_COND*sizeof(char*));
          (clause_arr+i)->cond_2 = malloc(MAX_COND*sizeof(char*));
       Ë
    Ë
    printf("alim_clause_arr : allocation of MAX_COND size Án");
    printf("sizeof(clause_arr) malloc : (%d) Án",sizeof(*clause_arr));

    i = 0;
    j = 0;

    (clause_arr+i)->id = 1;
    (clause_arr+i)->fp = data_external_cl;
    *(((clause_arr+i)->cond_1)+j) = "IS"; j++;
    printf("alim_clause_arr : alimentation of cond_1 Án");
    realloc((clause_arr+i)->cond_1,j*sizeof(char*)); j=0;
    printf("alim_clause_arr : allocation of j size for cond_1 Án");
    *(((clause_arr+i)->cond_2)+j) = "EXTERNAL"; j++;
    printf("alim_clause_arr : alimentation of cond_2 Án");
    realloc((clause_arr+i)->cond_2,j*sizeof(char*)); j=0;
    printf("alim_clause_arr : allocation of j size for cond_2 Án");
    i++;
    printf("alim_clause_arr : Succesful insertion of clause  1 Án");

    (clause_arr+i)->id = 2;
    (clause_arr+i)->fp = data_external_cl;
    *(((clause_arr+i)->cond_1)+j) = "BLANK"; j=0;
    realloc((clause_arr+i)->cond_1,j*sizeof(char*)); j=0;
    realloc((clause_arr+i)->cond_2,j*sizeof(char*)); j=0;
    i++;
    printf("alim_clause_arr : Succesful insertion of clause  2 Án");

    (clause_arr+i)->id = 3;
    (clause_arr+i)->fp = data_global_cl;
    *(((clause_arr+i)->cond_1)+j) = "IS"; j++;
    realloc((clause_arr+i)->cond_1,j*sizeof(char*)); j=0;
    *(((clause_arr+i)->cond_2)+j) = "GLOBAL"; j++;
    realloc((clause_arr+i)->cond_2,j*sizeof(char*)); j=0;
    i++;
    printf("alim_clause_arr : Succesful insertion of clause  3 Án");

    (clause_arr+i)->id = 4;
    (clause_arr+i)->fp = data_just_cl;
    *(((clause_arr+i)->cond_1)+j) = "JUST"; j++;
    *(((clause_arr+i)->cond_1)+j) = "JUSTIFIED"; j++;
    realloc((clause_arr+i)->cond_1,j*sizeof(char*)); j=0;
    *(((clause_arr+i)->cond_2)+j) = "GLOBAL"; j++;
    realloc((clause_arr+i)->cond_2,j*sizeof(char*)); j=0;
    i++;
    printf("alim_clause_arr : Succesful insertion of clause  4 Án");

    (clause_arr+i)->id = 5;
    (clause_arr+i)->fp = data_occurs_cl;
    *(((clause_arr+i)->cond_1)+j) = "OCCURS"; j++;
    realloc((clause_arr+i)->cond_1,j*sizeof(char*)); j=0;
    realloc((clause_arr+i)->cond_2,j*sizeof(char*)); j=0;
    i++;
    printf("alim_clause_arr : Succesful insertion of clause  5 Án");

    fp_t *temp = realloc(clause_arr,i*sizeof(fp_t));

    if (temp == NULL)È
       printf("Error allocating memory!Án");
       return 0;
    Ë
    else È
       clause_arr = temp;
       printf("Succesful reallocation!Án");
    printf("sizeof(clause_arr) realloc : (%d) Án",sizeof(*clause_arr));
    Ë
    return 1;

Ë
*/

int
tkn_in_array (str_arr conditions)È

   int i;

   debug_3("tkn_in_array: conditions.len = (%d) Án",conditions.len);

   for(i=0;i<conditions.len;i++)È

      debug_3("tkn_in_array: conditions.arr:(%s) Án",conditions.arr›i~);
      if (equal_val(conditions.arr›i~)) È
         debug_3("tkn_in_array: lookahead found(%s) Án",
                conditions.arr›i~);
         return 1;
      Ë
   Ë

   return 0;
Ë

fp_t_nod*
delete_clauses(fp_t_nod* clauses,fp_t_nod* to_delete)È

/* printf("delete_clauses: clauses = (%d) to_delete(%d) Án",
                           clauses ,      to_delete);
*/ fp_t_nod* temp;

   /* list is empty */
   if(clauses == NULL) È
     debug_3("delete_clauses : List is empty no destroying to do. Án");
     return clauses;

   Ë

   /* node to delete is the head of list */
   if(clauses == to_delete) È
     debug_3("delete_clauses : Beheading the List >:) ... Án");
     temp = clauses->next;
     free(clauses);
     return temp;
   Ë


   /* when other */
   /* tout pointer vers head of list */
   temp = clauses;
   fp_t_nod* beforeTemp = clauses;

   /* refaire tant qu'on est pas ‡ null (fin liste) */
   while (temp ß= NULL)È

      /* si adresse d'element a supprimer trouver */
      if(temp == to_delete)È
         debug_3("delete_clauses : node found, destroying ... Án");
         /* pointer le next du maillon d'avant vers celui d'apres */
         /* c-a-d : skip temp */
         beforeTemp->next = temp->next;
         /* liberer element a supprimer */
         free(temp);
         return clauses;
      Ë

      beforeTemp = temp;
      temp = temp->next;


   Ë
Ë

int
clause_print(fp_t clause,char* txt)È

    int i = 0;
    txt ="";
    printf("clause.id           :(%d)Án",clause.id);
    printf("clause.cond_1.len   :(%d)Án",clause.cond_1.len);
    for(i=0;i<clause.cond_1.len;i++)
       printf("clause.cond_1.arr(%d):(%s)Án",i,clause.cond_1.arr›i~);
    printf("clause.cond_2.len   :(%d)Án",clause.cond_2.len);
    for(i=0;i<clause.cond_2.len;i++)
       printf("clause.cond_2.arr(%d):(%s)Án",i,clause.cond_2.arr›i~);

    return 1;
Ë

int
clause_nod_print(fp_t_nod* clause_nod,char* txt)È

    printf("*************************************Án");
    printf("* Current * clause_nod       (%d) ***Án",clause_nod);
    printf("* Next    * clause_nod->next (%d) ***Án",clause_nod->next);
    clause_print(clause_nod->val,txt);
    printf("*************************************Án");

    return 1;
Ë

int
print_clauses(fp_t_nod* clauses)È

    printf("printf_clauses Start...ÁnÁn");

    fp_t_nod *iterator = clauses;

    do È

       clause_nod_print(iterator,"");
       iterator = iterator->next;
    /* assert(iterator == NULL); */

    Ë
    while (iterator ß= NULL);

    printf("printf_clauses End.Án");
    return 1;
Ë

/*---------------------- Build AST from attr ------------------------*/
/* cette fonction peut etre remplacer par un simple make_literal */
/* avec en parametres les equal_attr comme des int */
ast*
build_literal(int bool_all)È

    ast* ret=NULL;

    int   bool_numeric      =0;
    int   bool_alphanumeric =0;
    int   bool_hexadecimal  =0;
    int   bool_positive     =0;
    int   bool_negative     =0;
    int   bool_unsigned     =0;
    int   bool_singl_q      =0;
    int   bool_doubl_q      =0;
    int   bool_intgr        =0;
    int   bool_decim        =0;
    int   bool_figurative   =0;
    int   char_length       =0;
    char* value;

    if(equal_attr("NUMERIC"))          bool_numeric      =1;
    if(equal_attr("ALPHANUMERIC"))     bool_alphanumeric =1;
    if(equal_attr("HEX"))              bool_hexadecimal  =1;
    if(equal_attr("POSITIVE"))         bool_positive     =1;
    if(equal_attr("NEGATIVE"))         bool_negative     =1;
    if(equal_attr("UNSIGNED"))         bool_unsigned     =1;
    if(equal_attr("SINGLE QUOTE"))     bool_singl_q      =1;
    if(equal_attr("DOUBLE QUOTE"))     bool_doubl_q      =1;
    if(equal_attr("INTEGER"))          bool_intgr        =1;
    if(equal_attr("DECIMAL"))          bool_decim        =1;
    if(equal_attr("FIGURATIVE CONST")) bool_figurative   =1;

    char_length = get_token_len();
    value       = get_token_val();
    /*value    = "Hard-coded value";*/
    /*strcpy(value,get_token_val());*/

    ret=make_literal(value,bool_all, bool_numeric, bool_alphanumeric,
                     bool_hexadecimal, bool_positive,
                     bool_negative, bool_unsigned,
                     bool_singl_q, bool_doubl_q,
                     bool_intgr, bool_decim,
                     bool_figurative,
                     char_length);

    return ret;
Ë

/*---------------------- Auxiliary functions ------------------------*/
int
equal_type(char* expected)È

    if ((strcasecmp(lookahead.tkn_type,       expected) == 0 ))È
        debug_2("equal_type (%s) ?? Án",expected);
        return 1;
    Ë
    else È
    /*  printf("FALSE Án");
    */  return 0;
    Ë
Ë
/*----*/
int
equal_val(char* expected)È

    if ((strcasecmp(lookahead.tkn_val,        expected) == 0 )) È
        debug_2("equal_val (%s) ?? TRUE Án",expected);
        return 1;
    Ë

    else È
    /*  printf("FALSE Án"); */
        return 0;
    Ë
Ë
/*----*/
int
equal_attr(char* expected)È


    int i;

    for(i=0;i<lookahead.tkn_attr_len;i++)È

       if (strcasecmp(lookahead.tkn_attr›i~, expected) == 0)È
          debug_2("equal_attr (%s) ?? TRUE Án",expected);
          return 1;
       Ë
    Ë

    /*printf("FALSE Án"); */
    return 0;
Ë
/*----*/
int
match_type(char* expected)È

    debug_2("match_type : Trying to match type  : <%s> Án", expected);

    if (equal_type(expected)) È
        consume();
        return 1;
    Ë
    else
        return 0;
Ë
/*----*/
int
match_val (char* expected)È

    debug_2(" Trying to match Value <%s> with <%s>Án",
              expected,get_token_val());

    if (equal_val(expected)) È
        consume();
        return 1;
    Ë
    else
        return 0;
Ë
/*----*/
int
match_attr(char* expected)È

    debug_2("match_attr : Trying to match Attr  : <%s> Án", expected);

    if (equal_attr(expected)) È
        consume();
        return 1;
    Ë
    else
        return 0;
Ë
/*----*/
int
consume()È

    debug_3("consume(%s).Án ",lookahead.tkn_val);
    lookahead = getNextToken();
    debug_3("current(%s). Án",lookahead.tkn_val);

    return 1;
Ë
/*----*/
int
error(char* msg )È

    printf("error : %s",msg);
    exit(EXIT_FAILURE);

Ë

/*----*/

int
match(char* terminal)È
    printf("match()    : Trying to match token : <%s> Án",terminal);

    /*
    if    ((strcasecmp(lookahead.tkn_val,  "ZERO") == 0 )
        && (strcasecmp(lookahead.tkn_type, "ZERO") == 0 )
        && (strcasecmp(lookahead.tkn_type2,"ZERO") == 0 ) )
    È
        printf("match()    : Lookahead ZERO, Get next token");
        lookahead = getNextToken();

    Ë  */

    if    ((strcasecmp(lookahead.tkn_val,     terminal) == 0 )
        !! (strcasecmp(lookahead.tkn_type,    terminal) == 0 )
        !! (strcasecmp(lookahead.tkn_attr›0~, terminal) == 0 )
        !! (strcasecmp(lookahead.tkn_attr›1~, terminal) == 0 ))
    È
        printf("match()    : Token recognized : %s Án",terminal);
    /* mettre lookahead a zero en attendant le chargement de context */
    /*  lookahead.tkn_val    = "ZERO";
        lookahead.tkn_type   = "ZERO";
        lookahead.tkn_type2  = "ZERO"; */

        lookahead = getNextToken();

    Ë
    else
    È
        printf("match()    : Syntax error expected %s found<%s><%s>Án",
		      terminal, lookahead.tkn_type,lookahead.tkn_val);
        return 0;
    Ë
    return 1;
Ë

/*------*/

int
tknEqual(char* expected)È
/*  printf("tknEqual() : is Current token equal to:<%s>? Án",expected);
*/ /*
    if    ((strcasecmp(lookahead.tkn_val,  "ZERO") == 0 )
        && (strcasecmp(lookahead.tkn_type, "ZERO") == 0 )
        && (strcasecmp(lookahead.tkn_type2,"ZERO") == 0 ) )
    È
        printf("match()    : Lookahead ZERO, Get next token");
        lookahead = getNextToken();

    Ë
    */
    if ((strcasecmp(lookahead.tkn_val,        expected) == 0 )
        !! (strcasecmp(lookahead.tkn_type,    expected) == 0 )
        !! (strcasecmp(lookahead.tkn_attr›0~, expected) == 0 )
        !! (strcasecmp(lookahead.tkn_attr›1~, expected) == 0 ) )
    È
        printf("tknEqual() : Current token == to <%s> Án",expected);
        return 1;

    Ë
    else
    È
    /*  printf("tknEqual() : Current token != to <%s> Án",expected);*/
        return 0;
    Ë

Ë
/*------------------------- Auxiliary functions ---------------------*/

char*
get_token_val()È
    return lookahead.tkn_val;
Ë

char*
get_token_type()È
    return lookahead.tkn_type;
Ë
int
get_token_len()È
    return lookahead.tkn_len;
Ë

int
get_token_line()È
    return lookahead.tkn_lnnum;
Ë

int
get_token_col()È
    return lookahead.tkn_colnum;
Ë

