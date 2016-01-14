£include <stdio.h>
£include <stdlib.h>
£include <assert.h>
£include <string.h>

£define __UU
£include <strings.h>

£include "Grammarh"
£include "Lexerh"
£include "Rexxcomh"
£include "Helperh"

extern ast* global_ret;

int main()
È
    /* ast* tree; */

    getArgsRexx();

    /*
    printf("main()        : ");
    printf("argc    : (%d) Án",argc);
    printf("main()        : ");
    printf("cursc   : (%d) Án",cursc);
    printf("main()        : ");
    printf("cursl   : (%d) Án",cursl);
    printf("main()        : ");
    printf("lnumlast: (%d) Án",lnumlast);
    */

    lookahead = getNextToken();

    ast* ret = parse();

    /* Print AST */

    scr_line* screen;

    screen=init_screen();

    printf("Drawing Ast from parsing (%s)... Án",tagValues›ret->tag~);
    printf("Drawing Ast from parsing (%d)... Án",ret->tag);

    assert(ret->tag == SENTENCE);

    affich_node(ret,screen);

    /*
    screen=draw_box(screen,"DISPLAY"    ,""         ,  1);
    screen=draw_box(screen,"LITERAL"    ,"'A'"      ,  1);
    screen=draw_box(screen,"LITERAL"    ,"'B'"      ,  0);
    screen=draw_box(screen,"IDENTIFIER" ,""         ,  0);
    screen=draw_box(screen,"NAME"       ,"WS-NAME"  ,  1);
    screen=draw_box(screen,"QUALIF"     ,""         ,  0);
    screen=draw_box(screen,""           ,"QUALIF-1" ,  1);
    screen=draw_box(screen,""           ,"QUALIF-2" ,  0);
    screen=draw_box(screen,"SUBSCR"     ,""         , -1);
    screen=draw_box(screen,""           ,"SUBSCR-1" ,  1);
    screen=draw_box(screen,""           ,"SUBSCR-2" ,  0);
    screen=draw_box(screen,"REFMOD"     ,""         , -1);
    screen=draw_box(screen,""           ,"REFMOD-1" ,  1);
    screen=draw_box(screen,""           ,"REFMOD-2" ,  0);
    screen=draw_box(screen,"LITERAL"    ,"'C'"      , -2);

    screen=draw_box(screen,"MOVE"       ,""         , -1);
    screen=draw_box(screen,"IDENTIFIER" ,""         ,  1);
    screen=draw_box(screen,"NAME"       ,"WS-DATE-1",  1);
    screen=draw_box(screen,"QUALIF"     ,""         ,  0);
    screen=draw_box(screen,""           ,"QUALIF-1" ,  1);
    screen=draw_box(screen,"SUBSCR"     ,""         , -1);
    screen=draw_box(screen,""           ,"SUBSCR-1" ,  1);
    screen=draw_box(screen,"IDENTIFIER" ,""         , -2);
    screen=draw_box(screen,"NAME"       ,"WS-DATE-2",  1);
    */

    printf("Printing Ast from parsing (%s)... Án",tagValues›ret->tag~);
    print_boxes(screen);

    free_node(ret);

    /*
    assert(tree->tag == SENTENCE);

    printf("Tree nb statement :(%i)Án",
            tree->node.sentence.nb_statement);

    printf("main() end  ! Án free tree... ");

    free(tree);

    printf(" Done. Án");
    */
    printf(" END MAIN. Án");
    return 0;
Ë
£include <stdio.h>
£include <stdlib.h>
£include <stddef.h>

£include "Grammarh"
£include "Lexerh"
£include "asth"

£define MAX_FP_ARR   12
£define MAX_STR_ARR  20
£define COUNT_OF( arr) (sizeof(arr)/sizeof(0›arr~))

ast* global_ret;

/* Typedef pour function to Pointer */
typedef int (*IntFunc)(void);

/* Typedef pour array of string with length */
typedef struct str_arrÈ
   int    len;
   char*  arr ›MAX_STR_ARR~;
Ë str_arr;

/* Typedef pour Struct de :         */
/* - Pointer to function            */
/* - lookahead condition 1          */
/* - lookahead condition 2          */
typedef struct fp_tÈ
   IntFunc fp;
   str_arr cond_1;
   str_arr cond_2;
   int    id;
Ë fp_t;

/* Typedef pour array of fp_t with length */
typedef struct fp_t_nodÈ
   fp_t              val;
   struct fp_t_nod* next;
Ë fp_t_nod;

fp_t_nod* alim_clauses();
int tkn_in_array (str_arr);
fp_t_nod* delete_clauses(fp_t_nod*,fp_t_nod*);

context _context=È"","","","","",""Ë;
context save;

ast* build_literal(int);
                        /*----------*/
ast*
parse()
È

    ast* ret=NULL;

    if(dclrtn())È
      ;
    Ë

    else if (ret=sntce())È
      ;
    Ë

    else return NULL;

    printf("ret   tag (%d) Án",ret->tag);

    return ret;
Ë


/*---------------------------------  working storage        ---------*/
int
working_storage_section()È


    if(match_val("WORKING-STORAGE"))È
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

    /* 1-49, 66, 77 et 88 */
    while  (equal_attr("LEVEL NUMBER"))È

           if(dclrtn())È
              ;
           Ë
           else return 0;
    Ë

    printf("Rule recognized: working_storage_section Án");

    return 1;
Ë

/*---------------------------------  Sentence and Statement ---------*/

ast*
sntce()
È
    ast* ret=NULL;
    ast* stmnt_ret=NULL;

    int nb_statement =  0;
    ast* list_statement = NULL;

    printf("Trying to match rule : sntce Án");

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


    /* xxx */ printf("5 nb_statement   (%d)Án",nb_statement);
    /* xxx */ printf("5 list_statement (%d)Án",list_statement);

    /* xxx */ printf("5 list_statement->next (%d)Án",
                                                 list_statement->next);

      Ë
      else return NULL;

    Ë

/*  BUILD AST : SENTENCE */
    ret = make_sentence(nb_statement,list_statement);

    /* optional */
    if (equal_val("."))
        consume();

    printf("Rule recognized: sntce Án");

    printf("ret   tag (%d) Án",ret->tag);
    return ret;
Ë

ast*
stmnt()È
    printf("Trying to match rule : stmnt Án");

    ast* ret=NULL;

    if (equal_val("MOVE"))È

       if (move())È
           ;
       Ë
       else return NULL;

    Ë
    else if (equal_val("INITIALIZE"))È

       if (intlz())È
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


    printf("Rule recognized: stmnt Án.");
    printf("ret   tag (%d) Án",ret->tag);
    /* xxx */ printf("3 stmnt ret (%d)Án",ret);
    /* xxx */ printf("3 stmnt ret->next (%d)Án",ret->next);

    return ret;
Ë

/*--------------------  move, display and initialize Statement ------*/

int
move()
È
    printf("Trying to match rule : move Án");
/*
    if (move_2()) È
        ;
    Ë
    else if (move_1())È
        ;
    Ë
    else return 0;
*/
    if(match_val("MOVE"))È
        ;
    Ë
    else return 0;

    if (move_oprnd())È
        ;
    Ë
    else return 0;

    printf("Rule recognized: move Án");
    return 1;
Ë

ast*
dsply()
È
    printf("Trying to match rule : dsply Án");

    ast* ret=NULL;
    ast* sub_ret=NULL;

/*  BUILD AST : DISPLAY_STM */
    ret = make_display(0,0,"",0,NULL);

    /* xxx */ printf("1 display ret (%d)Án",ret);
    /* xxx */ printf("1 display ret->next (%d)Án",ret->next);

    if(match_val("DISPLAY"))È
        ;
    Ë
    else return NULL;

    if(sub_ret=ids_litrs())È
    /* xxx */ printf("after ids_litrs Án");

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

    printf("Rule recognized: dsply Án");

    printf("ret   tag (%d) Án",ret->tag);
    /* xxx */ printf("2 display ret (%d)Án",ret);
    /* xxx */ printf("2 display ret->next (%d)Án",ret->next);

    return ret;
Ë

int
intlz()
È
    printf("Trying to match rule : intlz Án");

    if(match_val("INITIALIZE"))È
        ;
    Ë
    else return 0;

    if(ids())È
        ;
    Ë
    else return 0;

    /* optional */
    if (equal_val("REPLACING"))È

       if(intlz_rplc())È
           ;
       Ë
       else return 0;

    Ë

    printf("Rule recognized: intlz Án");

    return 1;
Ë

/*------------------ initialize body --------------------------------*/

int
intlz_rplc ()
È
    printf("Trying to match rule : intlz_rplc Án");

    if(match_val("REPLACING"))È
        ;
    Ë
    else return 0;

    if(intlz_rplc_oprnds())È
        ;
    Ë
    else return 0;

    printf("Rule recognized: intlz_rplc Án");

    return 1;
Ë

int
intlz_rplc_oprnds()
È
    printf("Trying to match rule : intlz_rplc_oprnds Án");

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

    if (ret == 1)   printf("Rule recognized: intlz_rplc_oprnds Án");
    return ret;
Ë

int
intlz_rplc_oprnd()È

    printf("Trying to match rule : intlz_rplc_oprnd Án");

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

    printf("Rule recognized: intlz_rplc_oprnd Án");
    return 1;
Ë

int
chartype()
È
    printf("Trying to match rule : chartype Án");

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

    printf("Rule recognized: chartype Án");
    return 1;
Ë

/*-------------------------- move body ------------------------------*/
/*
int move_1()È

    printf("Trying to match rule : move_1 Án");

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

    printf("Rule recognized: move_1 Án");
    return 1;

Ë
*/
/* backtracking ? */
/*
int move_2()
È
    printf("Trying to match rule : move_2 Án");

    if(match("MOVE"))È
        ;
    Ë
    else return  0;

    if(corspnd())È
        ;
    Ë
    else return  0;

    printf("Rule recognized: move_2 Án");

    return 1;
Ë
*/
int
move_oprnd()È

    printf("Trying to match rule : move_oprnd Án");

    if((equal_val("CORR")) !!
       (equal_val("CORRESPONDING"))) È
       if(corspnd())È
          ;
       Ë
       else return 0;

       if(id())È
          ;
       Ë
       else return 0;

       if(match_val("TO"))È
          ;
       Ë
       else return 0;

       if(id())È
          ;
       Ë
       else return 0;

    Ë
    else È

       if(id_litr())È
          ;
       Ë
       else return 0;

       if(match_val("TO"))È
          ;
       Ë
       else return 0;

       if(ids())È
          ;
       Ë
       else return 0;
    Ë

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
    printf("Rule recognized: move_oprnd Án");
    return 1;

Ë

int
corspnd()
È
    printf("Trying to match rule : corspnd Án");

    if(match_val("CORRESPONDING"))È
        ;
    Ë
    else if (match_val("CORR"))È
        ;
    Ë
    else return  0;

    printf("Rule recognized : corspnd Án");
    return 1;
Ë

/*--------------------------- display body --------------------------*/

int
dsply_upon()
È
    printf("Trying to match rule : dsply_upon Án");

    if(match_val("UPON"))È
        ;
    Ë
    else return  0;

    if(dsply_upon_oprnd())È
        ;
    Ë
    else return  0;

    printf("Rule recognized : dsply_upon Án");

    return 1;
Ë

int
dsply_noadv()
È
    printf("Trying to match rule : dsply_noadv Án");

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

    printf("Rule recognized : dsply_noadv Án");

    return 1;
Ë

int
dsply_upon_oprnd()
È
    printf("Trying to match rule : dsply_upon_oprnd Án");

    if(mnemo_or_envir())È
        ;
    Ë
    else return  0;

    printf("Rule recognized : dsply_upon_oprnd Án");
    return 1;
Ë

int
mnemo_or_envir()
È
    printf("Trying to match rule : mnemo_or_envir Án");

    if(id_name())È
        ;
    Ë
    else return  0;

    printf("Rule recognized : mnemo_or_envir Án");
    return 1;
Ë


/*----------------------  Identifiers and Literals ------------------*/

ast*
ids_litrs()
È
    printf("Trying to match rule : ids_litrs Án");

    ast* ret    =NULL;
    ast* sub_ret=NULL;

    while(sub_ret=id_litr())È

        ret=append_list(ret,sub_ret);
        ;
    Ë

    if (ret)     printf("Rule recognized: ids_litrs (%d) Án",ret);
    printf("ids_litrs     (%s) address(%d)Án",ret->node.literal.value
                                             ,ret);

    return ret;
Ë

ast*
id_litr() È

    printf("Trying to match rule : id_litr Án");

    ast* ret=NULL;

    if(equal_type("IDENTIFIER") !! equal_attr("SPECIAL REGISTER"))È

       if (ret=id())È
           ;
       Ë
       else return NULL;

    Ë

    else È

       if (ret=litr())È
           printf("id_litr (%s) address(%d)Án",ret->node.literal.value
                                              ,ret);
           ;
       Ë
       else return NULL;

    Ë

    printf("Rule recognized: id_litr Án");
    return ret;
Ë

ast*
ids() È

    printf("Trying to match rule : ids Án");

    ast* ret     =NULL;
    ast* sub_ret =NULL;

    while(equal_type("IDENTIFIER") !! equal_attr("SPECIAL REGISTER"))È
       if(sub_ret=id())È

          ret = append_list(ret,sub_ret);

       Ë
       else return NULL;
    Ë

    if (ret)     printf("Rule recognized: ids Án");
    return ret;
Ë

/*-----------------------  Identifier and Literal -------------------*/

ast*
litr() È

    printf("Trying to match rule : litr Án");

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
    printf("1 liter (%s) address(%d) char_len(%d)"Á
           "  single quote (%d) alphanumeric (%d)"
                       ,ret->node.literal.value
                       ,ret
                       ,ret->node.literal.char_length
                       ,ret->node.literal.bool_singl_q
                       ,ret->node.literal.bool_alphanumeric);
        global_ret = ret;
        consume();
    printf("2 liter (%s) address(%d) char_len(%d)"Á
           "  single quote (%d) alphanumeric (%d)"
                       ,ret->node.literal.value
                       ,ret
                       ,ret->node.literal.char_length
                       ,ret->node.literal.bool_singl_q
                       ,ret->node.literal.bool_alphanumeric);
    Ë
    else return  NULL;

    printf("Rule recognized: litr Án");
    printf("ret tag (%s)(%d) Án",tagValues›ret->tag~,ret->tag);
    return ret;
Ë

ast*
figurative_constants() È

    ast* ret=NULL;
    ast* figurative_ret=NULL;

    int bool_all=0;

    printf("Trying to match rule : figurative_constants Án");

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

    printf("Rule recognized: figurative_constants Án");
    return ret;
Ë

ast*
id() È

    printf("Trying to match rule : id Án");

    ast* ret=NULL;
    ast* sub_ret=NULL;

    if (equal_attr("SPECIAL REGISTER"))È
       if (sub_ret=special_register())È
          ret=append_list(ret,sub_ret);
       Ë
    Ë
    else

    if (sub_ret=id_name())È
          ret=append_list(ret,sub_ret);
        ;
    Ë
    else return NULL;

    /* optional */
    if (equal_val("OF"))È
       if (sub_ret=id_qualif())È
           ;
       Ë
       else return  NULL;
    Ë

    /* optional subscript and refmodifier */
    if (equal_val("("))È

        /* une fois rentrÈ, ca devient obligatoire */
        if (sub_ret=id_subs_refm())È
           ;
        Ë
        else return  NULL;
    Ë

    printf("Rule recognized: id Án");
    return ret;
Ë


ast*
special_register() È

    printf("Trying to match rule : special_register Án");

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
          ret=make_identifier(bool_length,bool_address,
                              get_token_val(),NULL,NULL,NULL,NULL);
          consume();
       Ë
       else return NULL;


    printf("Rule recognized: special_register Án");
    return ret;
Ë

ast*
id_name_qualif()
È
    ast* ret    =NULL;
    ast* sub_ret=NULL;

    ret = make_ident_name_qualif(NULL,NULL);


    if (sub_ret=id_name())È
        ret->node.ident_name_qualif.name=sub_ret;
    Ë
    else return NULL;

    /* optional */
    if (equal_val("OF"))È
       if (sub_ret=id_qualif())È
          ret->node.ident_name_qualif.qualif=sub_ret;

       Ë
       else return NULL;
    Ë

    return ret;

Ë

ast*
id_names()
È
    ast* ret    =NULL;
    ast* sub_ret=NULL;

    printf("Trying to match rule : id_names Án");

    while(equal_type("IDENTIFIER"))È

        if (sub_ret=id_name())È

           ret=append_list(ret,sub_ret);
        Ë
        else return NULL;

    Ë

    if(ret) printf("Rule recognized: id_names Án");

    return ret;
Ë

ast*
id_name()
È
    printf("Trying to match rule : id_name Án");

    ast* ret    =NULL;
    ast* sub_ret=NULL;

    if (equal_type("IDENTIFIER"))È
        ret=make_ident_name(get_token_len(),get_token_val());
        consume();
    Ë
    else return NULL;

    printf("Rule recognized: id_name Án");
    return ret;
Ë

ast*
id_qualif()
È
    printf("Trying to match rule : id_qualif Án");

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

    if (ret)     printf("Rule recognized: id_qualif Án");
    return ret;

Ë

ast*
id_qualif_oprnd ()È

    ast* ret    =NULL;
    ast* sub_ret=NULL;

    printf("Trying to match rule : id_qualif_oprnd Án");

    if (match_val("OF"))È
        ;
    Ë
    else return NULL;

    if(sub_ret=id_name())È
        ret=append_list(ret,sub_ret);
    Ë
    else return NULL;

    printf("Rule recognized: id_qualif_oprnd Án");
    return ret;
Ë
/* continue implementing ast here ... */
ast*
id_subs_refm()È

    ast* ret    =NULL;
    ast* sub_ret=NULL;

    printf("Trying to match rule : id_subs_refm Án");

    if (match_val("("))È
        ;
    Ë
    else return NULL;

    if(sub_ret=id_oprnd_1_subs_refm())È
        ;
    Ë
    else return NULL;

    if(sub_ret=id_subs_refm_rest())È
        ;
    Ë
    else return NULL;

    printf("Rule recognized : id_subs_refm Án");
    return ret;

Ë

ast*
id_oprnd_1_subs_refm()È


    ast* ret    =NULL;
    ast* sub_ret=NULL;

    printf("Trying to match rule : id_oprnd_1_subs_refm Án");

    if (sub_ret=arith_expr())È
        ;
    Ë
    else return NULL;

    printf("Rule recognized : id_oprnd_1_subs_refm Án");
    return ret;

Ë

ast*
id_subs_refm_rest()È

    printf("Trying to match rule : id_subs_refm_rest Án");

    ast* ret    =NULL;
    ast* sub_ret=NULL;

    if (equal_val(":"))È
        if (sub_ret=id_refm_rest())È
           ;
        Ë
        else return NULL;
    Ë
    else if (sub_ret=id_subs_rest())È

             if (equal_val("("))È
                if (sub_ret=id_refmodif())È
                    ;
                Ë
                else return  NULL;
             Ë

    Ë

    else return  NULL;

    printf("Rule recognized : id_subs_refm_rest Án");
    return  ret;

Ë

ast*
id_refm_rest()
È
    printf("Trying to match rule : id_refm_rest Án");

    ast* ret    =NULL;
    ast* sub_ret=NULL;


    if (match_val(":"))È
        ;
    Ë
    else return  NULL;

    if(sub_ret=refmodif_length())È
        ;
    Ë
    else return  NULL;

    if (match_val(")"))È
        ;
    Ë
    else return  NULL;

    printf("Rule recognized : id_refm_rest Án");
    return  ret;

Ë

ast*
id_subs_rest()
È
    printf("Trying to match rule : id_subs_rest Án");

    ast* ret    =NULL;
    ast* sub_ret=NULL;

    if (match_val(")"))È
        ;
    Ë
    else
    È
        if(sub_ret=subscripts())È

            if (match_val(")"))È
                ;
            Ë
            else return  NULL;
        Ë
        else return  NULL;
    Ë

    printf("Rule recognized : id_subs_rest Án");
    return  ret;

Ë

ast*
id_subscript()
È
    printf("Trying to match rule : id_subscript Án");

    ast* ret    =NULL;
    ast* sub_ret=NULL;


    if (match_val("("))È
        ;
    Ë
    else return  NULL;

    if(sub_ret=subscripts())È
        ;
    Ë
    else return  NULL;

    if (match_val(")"))È
        ;
    Ë
    else return  NULL;

    printf("Rule recognized: id_subscript Án");
    return ret;
Ë

ast*
id_refmodif()
È
    printf("Trying to match rule : id_refmodif Án");

    ast* ret    =NULL;
    ast* sub_ret=NULL;


    if (match_val("("))È
        ;
    Ë
    else return  NULL;

    if(sub_ret=refmodif())È
        ;
    Ë
    else return  NULL;

    if (match_val(")"))È
        ;
    Ë
    else return  NULL;

    printf("Rule recognized: id_refmodif Án");
    return ret;
Ë


/*---------------------------  Identifier body ----------------------*/

ast*
subscripts()
È
    printf("Trying to match rule : subscripts Án");


    ast* ret    =NULL;
    ast* sub_ret=NULL;

    while(sub_ret=subscript())È
        ;
    Ë

    if (ret)     printf("Rule recognized: subscripts Án");
    return ret;
Ë

ast*
subscript()
È
    printf("Trying to match rule : subscript Án");

    ast* ret    =NULL;
    ast* sub_ret=NULL;

    if (sub_ret=arith_expr2())È
        ;
    Ë
    else return  NULL;

    printf("Rule recognized: subscript Án");
    return ret;
Ë

ast*
refmodif()
È

    ast* ret    =NULL;
    ast* sub_ret=NULL;

    printf("Trying to match rule : refmodif Án");

    if(sub_ret=charleftpos())È
        ;
    Ë
    else return  NULL;

    if(match_val(":"))È
        ;
    Ë
    else return  NULL;

    if(sub_ret=refmodif_length())È
        ;
    Ë
    else return  NULL;

    printf("Rule recognized: refmodif Án");
    return ret;
Ë

ast*
charleftpos()
È

    ast* ret    =NULL;
    ast* sub_ret=NULL;

    printf("Trying to match rule : charleftpos Án");

    if (sub_ret=arith_expr())È
        ;
    Ë
    else return  NULL;

    printf("Rule recognized: charleftpos Án");
    return ret;
Ë

ast*
refmodif_length()
È
    printf("Trying to match rule : refmodif_length Án");

    /*optional */

    ast* ret    =NULL;
    ast* sub_ret=NULL;


    if(ßequal_val(")"))È
       if (sub_ret=arith_expr())È
           ;
       Ë
       else return NULL;
    Ë

    printf("Rule recognized: refmodif_length Án");
    return ret;
Ë


/*-------------------------  Arithmetic expression ------------------*/
/*
int arith_expr_old()
È
    printf("Trying to match rule : arith_expr_old Án");

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

    printf("Rule recognized: arith_expr_old Án");
    return 1;
Ë
*/
ast*
arith_expr()
È
    printf("Trying to match rule : arith_expr Án");

    ast* ret    =NULL;
    ast* sub_ret=NULL;


    if(sub_ret=times_div())È
        ;
    Ë
    else return  NULL;

    while((equal_val("+")) !! (equal_val("-")))È

       consume();

       if(sub_ret=times_div())È
          ;
       Ë
       else return NULL;

    Ë

    printf("Rule recognized: arith_expr Án");
    return ret;
Ë

ast*
times_div()
È
    printf("Trying to match rule : times_div Án");

    ast* ret    =NULL;
    ast* sub_ret=NULL;


    if(sub_ret=power())È
        ;
    Ë
    else return  NULL;

    while((equal_val("*")) !! (equal_val("/")))È

       consume();

       if(sub_ret=power())È
          ;
       Ë
       else return NULL;

    Ë

    printf("Rule recognized: times_div Án");
    return ret;
Ë

ast*
power()
È
    printf("Trying to match rule : power Án");

    ast* ret    =NULL;
    ast* sub_ret=NULL;


    if ((equal_val("+")))È

       consume();

    Ë
    else if((equal_val("-")))È

       consume();

    Ë

    if(sub_ret=basis())È
        ;
    Ë
    else return  NULL;

    while((equal_val("**")))È

       consume();

       if(sub_ret=basis())È
          ;
       Ë
       else return NULL;

    Ë

    printf("Rule recognized: power Án");
    return ret;
Ë

ast*
basis()
È
    printf("Trying to match rule : basis Án");


    ast* ret    =NULL;
    ast* sub_ret=NULL;

    if ((equal_type("IDENTIFIER"))!!(equal_attr("SPECIAL REGISTER")))È

       if (sub_ret=id())È
          ;
       Ë
       else return NULL;
    Ë
    else if((equal_val("(")))È

            /* bug de caca ! ne pas oublier de consommer le ( */
            consume();

            if (sub_ret=arith_expr())È
               ;
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
                  ;
               Ë
               else return NULL;
            Ë
            else /* KEYWORD (ZERO/ZEROS/ZEROS) */
            È
               consume();
            Ë

         Ë

    else return NULL;

    printf("Rule recognized: basis Án");
    return ret;
Ë

ast*
arith_expr2()
È
    printf("Trying to match rule : arith_expr2 Án");

    ast* ret    =NULL;
    ast* sub_ret=NULL;

    if((equal_attr("INTEGER"))&&(equal_attr("UNSIGNED")))È

        consume();

    Ë
    else if(sub_ret=id_name_qualif())È

            /* optional */
            if((equal_val("+"))!!(equal_val("-"))) È

               consume();

               if((equal_attr("INTEGER"))&&(equal_attr("UNSIGNED")))È

                  consume();

               Ë
               else return  NULL;
            Ë

         Ë
    else return NULL;

    printf("Rule recognized: arith_expr2 Án");
    return ret;
Ë
/*
int arith_expr2_old()
È
    printf("Trying to match rule : arith_expr2_old Án");

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

    printf("Rule recognized: arith_expr2_old Án");
    return 1;
Ë

int arith_expr_oprnd()
È
    printf("Trying to match rule : arith_expr_oprnd Án");

    if (match("INTEGER"))È
        ;
    Ë
    else if (id_name_qualif())È
        ;
    Ë
    else return  0;

    printf("Rule recognized: arith_expr_oprnd Án");
    return 1;
Ë

int arith_expr_oprtn()
È
    printf("Trying to match rule : arith_expr_oprtn Án");

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

    printf("Rule recognized: arith_expr_oprtn Án");
    return 1;
Ë
*/
/*---------------------- Data declaration    ------------------------*/
int
dclrtn()È

    printf("Trying to match rule : dclrtn Án");

    if  (equal_attr("LEVEL NUMBER")&&
        ßequal_val ("66")          &&
        ßequal_val ("88")          )È

         consume();

        if (equal_type("IDENTIFIER"))È

           if (id_name())È
              ;
           Ë
           else return  0;
        Ë
        else if (equal_val("FILLER"))È

                consume();
             Ë
             else ;

        if (data_desc())È
           ;
        Ë
        else return  0;

        if (match_val("."))È
           ;
        Ë
        else return  0;

    Ë
    else if (equal_attr("LEVEL NUMBER")&&
             equal_val ("66")          )È

             consume();

        if (id_name())È
           ;
        Ë
        else return  0;

        if (renames_cl())È
           ;
        Ë
        else return  0;

        if (match_val("."))È
           ;
        Ë
        else return  0;

    Ë
    else if (equal_attr("LEVEL NUMBER")&&
             equal_val ("88")          )È

             consume();

        if (cond_name())È
           ;
        Ë
        else return  0;

        if (cond_val_cl())È
           ;
        Ë
        else return  0;

        if (match_val("."))È
           ;
        Ë
        else return  0;

    Ë
    else return 0;

    printf("Rule recognized: dclrtn Án");
    return 1;

Ë
/*---------------------- Declaration  body   ------------------------*/

int
cond_name()
È
    printf("Trying to match rule : cond_name Án");

    if (match_type("IDENTIFIER"))È
        ;
    Ë
    else return  0;

    printf("Rule recognized: cond_name Án");
    return 1;
Ë

/*------*/

int
data_desc()
È
    printf("Trying to match rule : data_desc Án");


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

       if (data_redefines_cl())È
          ;
       Ë
       else return  0;
    Ë

    /* Array of clauses to permute      */
    fp_t_nod *clauses;
    clauses = alim_clauses();
    print_clauses(clauses);

    fp_t_nod *iterator= clauses;

    printf("Permutation loop start ... Án list head (%d)Án",iterator);

    /* parcourir la liste chainÈe */
    while (iterator ß= NULL)È

   /*printf("Permutation loop .iterator (%d)Án",iterator);
   */  /* Known bug : 'IS' is accepted before each clause !! */
       /* if should be for external et gloabal only          */
       /* A deleguer a l'analyse semantique                  */
       if (equal_val("IS"))È

          consume();

       Ë

       /* if lookahead match    */
       if (tkn_in_array(iterator->val.cond_1))È
          /* invoquer la function pointer */
          if (iterator->val.fp())È
             printf("Function pointer (%d) invoked after cond Án",
                    iterator->val.id);
          Ë
          else return 0;

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

    /*
    if (tknEqual("IS"))È

       if (match("IS"))È
          ;
       Ë
       else return  0;
    Ë

    if (tknEqual("EXTERNAL"))È

       if (data_external_cl())È
          ;
       Ë
       else return  0;
    Ë

    if (tknEqual("BLANK"))È

       if (data_blankzero_cl())È
          ;
       Ë
       else return  0;
    Ë
    */
    /* Not implemented clause : Format */
    /*
    if (tknEqual("IS"))È

       if (match("IS"))È
          ;
       Ë
       else return  0;
    Ë

    if (tknEqual("GLOBAL"))È

       if (data_global_cl())È
          ;
       Ë
       else return  0;
    Ë

    if ((tknEqual("JUST")) !!
        (tknEqual("JUSTIFIED")) )È

       if (data_just_cl())È
          ;
       Ë
       else return  0;
    Ë

    if (tknEqual("OCCURS"))È

       if (data_occurs_cl())È
          ;
       Ë
       else return  0;
    Ë

    if ((tknEqual("PIC")) !!
        (tknEqual("PICTURE")) )È

       if (data_pic_cl())È
          ;
       Ë
       else return  0;
    Ë

    if ((tknEqual("SIGN")) !!
        (tknEqual("LEADING")) !!
        (tknEqual("TRAILING")))È

       if (data_sign_cl())È
          ;
       Ë
       else return  0;
    Ë


    if (tknEqual("VALUE"))È

       if (data_value_cl())È
          ;
       Ë
       else return  0;
    Ë


    if ((tknEqual("SYNC")) !!
        (tknEqual("SYNCHRONIZED")) )È

       if (data_sync_cl())È
          ;
       Ë
       else return  0;
    Ë
    */
    /* Not implemented clause : Type    */
    /*
    if ((tknEqual("USAGE"))           !!
        (tknEqual("BINARY"))          !!
        (tknEqual("COMPUTATIONAL"))   !!
        (tknEqual("COMP"))            !!
        (tknEqual("COMPUTATIONAL-1")) !!
        (tknEqual("COMP-1"))          !!
        (tknEqual("COMPUTATIONAL-2")) !!
        (tknEqual("COMP-2"))          !!
        (tknEqual("COMPUTATIONAL-3")) !!
        (tknEqual("COMP-3"))          !!
        (tknEqual("COMPUTATIONAL-4")) !!
        (tknEqual("COMP-4"))          !!
        (tknEqual("DISPLAY"))         !!
        (tknEqual("DISPLAY-1"))       !!
        (tknEqual("INDEX"))           !!
        (tknEqual("PACKED-DECIMAL"))  !!
        (tknEqual("POINTER"))         !!
        (tknEqual("PROCEDURE-POINTER")))È

       if (data_usage_cl())È
          ;
       Ë
       else return  0;
    Ë
    */
    printf("Rule recognized: data_desc Án");
    return 1;
Ë

/*--------------------- Data declaration functions ------------------*/

int
data_redefines_cl()È

    printf("Trying to match rule : data_redefines_cl Án");

    if (match_val("REDEFINES"))È
       ;
    Ë
    else return 0;

    if (id_name())È
       ;
    Ë
    else return 0;

    printf("Rule recognized: data_redefines_cl Án");
    return 1;
Ë

/*------*/

int
data_external_cl()È

    printf("Trying to match rule : data_external_cl  Án");

    if (match_val("EXTERNAL"))È
       ;
    Ë
    else return 0;


    printf("Rule recognized: data_external_cl  Án");
    return 1;
Ë

/*------*/

int
data_blankzero_cl()È

    printf("Trying to match rule : data_blankzero_cl Án");

    if (match_val("BLANK"))È
       ;
    Ë
    else return 0;

    if (equal_val("WHEN"))È

       consume();

    Ë

    if (match_val("ZERO"))È
       ;
    Ë
    else return 0;


    printf("Rule recognized: data_blankzero_cl Án");
    return 1;
Ë

/*------*/

int
data_global_cl()È

    printf("Trying to match rule : data_global_cl Án");

    if (match_val("GLOBAL"))È
       ;
    Ë
    else return 0;


    printf("Rule recognized: data_global_cl Án");
    return 1;
Ë

/*------*/

int
data_just_cl()È

    printf("Trying to match rule : data_just_cl Án");

    if ((equal_val("JUST"))!!(equal_val("JUSTIFIED")))È

       consume();

    Ë

    if ((equal_val("RIGHT")))È

       consume();

    Ë

    printf("Rule recognized: data_just_cl Án");
    return 1;
Ë

/*------*/

int
data_occurs_cl()È

    printf("Trying to match rule : data_occurs_cl Án");

    if (match_val("OCCURS"))È
       ;
    Ë
    else return 0;

    if ((equal_attr("INTEGER"))!!(equal_attr("UNSIGNED")))È

       consume();
    Ë
    else return 0;

    /* Format 2 */
    if ((equal_val("TO")))È

        consume();

        if ((equal_attr("INTEGER"))!!(equal_attr("UNSIGNED")))È

           consume();
        Ë
        else return 0;

        if ((equal_val("TIMES")))È

           consume();
        Ë

        if (match_val("DEPENDING"))È
           ;
        Ë
        else return 0;

        if ((equal_val("ON")))È

           consume();
        Ë

        if (id_name())È
           ;
        Ë
        else return 0;

        /* Key-indexed-by phrase */

        if ((equal_val("ASCENDING")) !!
            (equal_val("DESCENDING")) )È

            if (data_index_key_cls())È
               ;
            Ë
            else return 0;
        Ë

        if ((equal_val("INDEX")))È

            if (data_index_by_cl())È
               ;
            Ë
            else return 0;
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

            if (data_index_key_cls())È
               ;
            Ë
            else return 0;
        Ë

        if ((equal_val("INDEX")))È

            if (data_index_by_cl())È
               ;
            Ë
            else return 0;
        Ë

    Ë

    printf("Rule recognized: data_occurs_cl Án");
    return 1;
Ë

int data_index_key_cls()È

    int ret=0;
    printf("Trying to match rule : data_index_key_cls Án");

    while ((equal_val("ASCENDING")) !!
           (equal_val("DESCENDING")))È

        if (data_index_key_cl())È
           ;
        Ë
        else return 0;

        ret = 1;

    Ë

    if(ret==1) printf("Rule recognized: data_index_key_cls Án");

    return ret;
Ë

int
data_index_key_cl()È

    printf("Trying to match rule : data_index_key_cl Án");

    if ((equal_val("ASCENDING")) !!
        (equal_val("DESCENDING")) )È

       consume();

       if ((equal_val("KEY")))È

          consume();
       Ë

       if ((equal_val("IS")))È

          consume();
       Ë

       if (id_names())È
          ;
       Ë
       else return 0;

    Ë
    else return 0;

    printf("Rule recognized: data_index_key_cl Án");
    return 1;
Ë

int
data_index_by_cl()È

    printf("Trying to match rule : data_index_by_cl Án");

    if (match_val("INDEX"))È
       ;
    Ë
    else return 0;

    if ((equal_val("BY")))È

       consume();
    Ë

    if (id_names())È
       ;
    Ë
    else return 0;


    printf("Rule recognized: data_index_by_cl Án");
    return 1;
Ë

/*------*/

int
data_pic_cl()È


    printf("Trying to match rule : data_pic_cl Án");

    save = set_context("data_pic_chars");

    if(match_val("PIC"))È
       ;
    Ë
    else if(match_val("PICTURE"))È
            ;
         Ë
    else return 0;


    if (data_pic_str())È
       ;
    Ë
    else return  0;

    restore_context(save);


    if (equal_val("SIZE"))È
       if (data_pic_size_local())È
          ;
       Ë
       else return  0;
    Ë


    /* consommer Space qui vient apres la fin de pic str */
    if (equal_type("SPACE"))È

       consume();
    Ë


    printf("Rule recognized: data_pic_cl Án");
    return 1;
Ë


int
data_pic_str()È


    printf("Trying to match rule : data_pic_str Án");


    if (equal_val("IS"))È

       consume();

    Ë

    /* Lexer/Parser Hack */
    /* pour ne pas accepter espace apres repeat : */
    /* PIC 9(9) V                                 */
    /* on consomme le premier espace apres pic et IS */
    /* et puis enlever les espaces de token picchar  */

    /* Space */

    if (match_type("SPACE"))È
       ;
    Ë
    else return  0;

    /* Currency */
    if (equal_val("$"))È

       consume();

    Ë

    while (equal_type("PICCHARS"))È

   /*  set_context("data_pic_chars");
   */
       /* PicChars */
       if (data_pic_chars())È
          ;
       Ë
       else return  0;

   /*  restore_context(save);
   */
       /* Repeat */
       if (equal_val("("))È

          if (data_pic_repeat())È
             ;
          Ë
          else return  0;

       Ë
    Ë


    printf("Rule recognized: data_pic_str Án");
    return 1;
Ë

/****/

int
data_pic_chars()È

    printf("Trying to match rule : data_pic_chars Án");

    if (match_type("PICCHARS"))È
       ;
    Ë
    else
    È
       return  0;
    Ë

    printf("Rule recognized: data_pic_chars Án");

    return 1;
Ë

int
data_pic_repeat()È

    printf("Trying to match rule : data_pic_repeat Án");


    if (match_val("("))È
       ;
    Ë
    else return  0;

    if ((equal_attr("UNSIGNED"))&&(equal_attr("INTEGER")))È
       consume();
    Ë
    else return  0;

    if (match_val(")"))È
       ;
    Ë
    else return  0;

    printf("Rule recognized: data_pic_repeat Án");
    return 1;
Ë


int
data_pic_size_local()È

    printf("Trying to match rule : data_pic_size_local Án");


    if (match_val("SIZE"))È
       ;
    Ë
    else return  0;

    if (equal_val("IS"))È

       consume();

    Ë

    if (match_attr("INTEGER"))È
       ;
    Ë
    else return  0;

    if (match_val("LOCALE"))È
       ;
    Ë
    else return  0;

    if (equal_val("IS"))È

       consume();

       if (mnemo_or_envir())È
          ;
       Ë
       else return  0;
    Ë

    else È
       if (equal_type("IDENTIFIER"))È
          if (mnemo_or_envir())È
             ;
          Ë
          else return  0;
       Ë
    Ë

    printf("Rule recognized: data_pic_size_local Án");
    return 1;
Ë

/*------*/

int
data_sign_cl()È

    printf("Trying to match rule : data_sign_cl Án");

    if (equal_val("SIGN"))È

       consume();

       if (equal_val("IS"))È

          consume();

       Ë

    Ë

    if (equal_val("LEADING"))È

       consume();

    Ë
    else if(equal_val("TRAILING"))È

             consume();
         Ë

    else return 0;

    if (equal_val("SEPARATE"))È

       consume();

       if (equal_val("CHARACTER"))È

          consume();

       Ë

    Ë


    printf("Rule recognized: data_sign_cl Án");
    return 1;
Ë

/*------*/

int
data_value_cl()È

    printf("Trying to match rule : data_value_cl Án");


    if (match_val("VALUE"))È
       ;
    Ë
    else return  0;

    if (equal_val("IS"))È

       consume();

    Ë

    if (litr())È
       ;
    Ë
    else return  0;


    printf("Rule recognized: data_value_cl Án");
    return 1;
Ë

/*------*/

int
data_sync_cl()È

    printf("Trying to match rule : data_sync_cl Án");

    if ((equal_val("SYNC"))) È

       consume();

    Ë
    else if (equal_val("SYNCHRONIZED"))È

       consume();
    Ë
    else return 0;

    if ((equal_val("LEFT"))) È

       consume();
    Ë
    else if (equal_val("RIGHT")) È

       consume();

    Ë

    printf("Rule recognized: data_sync_cl Án");
    return 1;
Ë

/*------*/

int
data_usage_cl()È

    printf("Trying to match rule : data_usage_cl Án");

    if (equal_val("USAGE"))È

       consume();

       if (equal_val("IS"))È

          consume();

       Ë

    Ë

    if (equal_val("BINARY"))È

        consume();


    Ë else if (equal_val("COMPUTATIONAL"))È

        consume();

    Ë else if (equal_val("COMP"))È

        consume();

    Ë else if (equal_val("COMPUTATIONAL-1"))È

        consume();

    Ë else if (equal_val("COMP-1"))È

        consume();

    Ë else if (equal_val("COMPUTATIONAL-2"))È

        consume();

    Ë else if (equal_val("COMP-2"))È

        consume();

    Ë else if (equal_val("COMPUTATIONAL-3"))È

        consume();

    Ë else if (equal_val("COMP-3"))È

        consume();

    Ë else if (equal_val("COMPUTATIONAL-4"))È

        consume();

    Ë else if (equal_val("COMP-4"))È

        consume();

    Ë else if (equal_val("DISPLAY"))È

        consume();

    Ë else if (equal_val("DISPLAY-1"))È

        consume();

    Ë else if (equal_val("INDEX"))È

        consume();

    Ë else if (equal_val("PACKED-DECIMAL"))È

        consume();

    Ë else if (equal_val("POINTER"))È

        consume();

    Ë else if (equal_val("PROCEDURE-POINTER"))È

        consume();

    Ë else return 0;

    printf("Rule recognized: data_usage_cl Án");
    return 1;
Ë
/*---------------------- renames and conditional function -----------*/

int
renames_cl()
È
    printf("Trying to match rule : renames_cl Án");

    if (match_val("RENAMES"))È
        ;
    Ë
    else return  0;

    if (id_name_qualif())È
        ;
    Ë
    else return  0;

    if ((equal_val("THROUGH")) !!
        (equal_val("THRU")) )È

       consume();

       if (id_name_qualif())È
           ;
       Ë
       else return  0;

    Ë

    printf("Rule recognized: renames_cl Án");
    return 1;
Ë

int
cond_val_cl()
È
    printf("Trying to match rule : cond_val_cl Án");

    int ret =0;

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
    else return  0;

    while (litr())È

       if ((equal_val("THROUGH")) !!
           (equal_val("THRU")) )È

           consume();

          if (litr())È
              ;
          Ë
          else return  0;

       Ë
    Ë

    printf("Rule recognized: cond_val_cl Án");
    return 1;
Ë

/*---------------------- Context function    ------------------------*/

int
affich_context()È

   printf("Án");
   printf("context.division : <%s>Án", _context.division);
   printf("context.section  : <%s>Án", _context.section );
   printf("context.sentence : <%s>Án", _context.sentence);
   printf("context.clause   : <%s>Án", _context.clause  );
   printf("context.keyword  : <%s>Án", _context.keyword );
   printf("context.other    : <%s>Án", _context.other   );
   printf("Án");

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

    printf("alim_clauses : Start Án");

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
    clauses_arr›i~.fp = data_value_cl;
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

 /*printf("tkn_in_array: conditions.len = (%d) Án",conditions.len);
 */
   for(i=0;i<conditions.len;i++)È

      printf("tkn_in_array: conditions.arr:(%s) Án",conditions.arr›i~);
      if (equal_val(conditions.arr›i~)) È
         printf("tkn_in_array: lookahead found(%s) Án",
                conditions.arr›i~);
         return 1;
      Ë
   Ë

   return 0;
Ë

fp_t_nod*
delete_clauses(fp_t_nod* clauses,fp_t_nod* to_delete)È

   printf("delete_clauses: clauses = (%d) to_delete(%d) Án",
                           clauses ,      to_delete);
   fp_t_nod* temp;

   /* list is empty */
   if(clauses == NULL) È
     printf("delete_clauses : List is empty no destroying to do. Án");
     return clauses;

   Ë

   /* node to delete is the head of list */
   if(clauses == to_delete) È
     printf("delete_clauses : Beheading the List >:) ... Án");
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
         printf("delete_clauses : node found, destroying ... Án");
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

    printf("built literal (%s) address(%d) char_len(%d)Án"
                                     ,ret->node.literal.value
                                     ,ret
                                     ,ret->node.literal.char_length);
    return ret;
Ë

/*---------------------- Auxiliary functions ------------------------*/
int
equal_type(char* expected)È

    printf("equal_type (%s) ?? ",expected);
    if ((strcasecmp(lookahead.tkn_type,       expected) == 0 ))È
        printf("TRUE Án");
        return 1;
    Ë
    else È
        printf("FALSE Án");
        return 0;
    Ë
Ë
/*----*/
int
equal_val(char* expected)È

    printf("equal_val (%s) ?? ",expected);
    if ((strcasecmp(lookahead.tkn_val,        expected) == 0 )) È
        printf("TRUE Án");
        return 1;
    Ë

    else È
        printf("FALSE Án");
        return 0;
    Ë
Ë
/*----*/
int
equal_attr(char* expected)È


    int i;

    printf("equal_attr (%s) ?? ",expected);
    for(i=0;i<lookahead.tkn_attr_len;i++)È

       if (strcasecmp(lookahead.tkn_attr›i~, expected) == 0)È
          printf("TRUE Án");
          return 1;
       Ë
    Ë

    printf("FALSE Án");
    return 0;
Ë
/*----*/
int
match_type(char* expected)È

    printf("match_type : Trying to match type  : <%s> Án", expected);

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

    printf("match_val  : Trying to match Value : <%s> Án", expected);

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

    printf("match_attr : Trying to match Attr  : <%s> Án", expected);

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

    printf("consume(%s). Án",lookahead.tkn_val);
    printf("1 bug tracker : global_ret (%s) (%d)Án",
                                  global_ret->node.literal.value,
                                  global_ret);
    lookahead = getNextToken();
    printf("2 bug tracker : global_ret (%s) (%d)Án",
                                  global_ret->node.literal.value,
                                  global_ret);

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

£include <stdio.h>
£include <stdlib.h>

£include "Lexerh"
£include "tokenzrh"

int i = 0;
ast* global_ret;

/* curr_ln_obj stores the actual string to tokenize */
static ln_obj curr_ln_obj;

token getNextToken()È

    printf("3 bug tracker global_ret (%s) address(%d) char_len(%d)"Á
           "  single quote (%d) alphanumeric (%d)"
                       ,global_ret->node.literal.value
                       ,global_ret
                       ,global_ret->node.literal.char_length
                       ,global_ret->node.literal.bool_singl_q
                       ,global_ret->node.literal.bool_alphanumeric);
    /* made static to preserve value after recursive call */
    static token _ret;
    ln_str_num next_ln;
    /*
    printf("getNextToken() : ");
    printf("curr_ln_num:(%d)curr_ln_obj.ln_8_72:<%s>Án",
            curr_ln_num,curr_ln_obj.ln_8_72);
    */
    /* still chars in curr_ln_obj.ln_8_72 ? */
    while(strlen(curr_ln_obj.ln_8_72)<1) È

       /* get next Line           */
       next_ln = getLineString(curr_ln_num);

       /* if  Line num = 0 end program  */
       if (next_ln.ln_num == 0 ) È

           printf("getNextToken() : ");
           printf(" *********** PROGRAM END ***********Án");
          _ret.tkn_type = "PROGRAM$";
          _ret.tkn_val  = ""        ;
          return _ret;

       Ë

       /* increment current line  */
       curr_ln_num++;

       /* call preprocessor to prepare line */
       curr_ln_obj = preprocessor(next_ln);
    /*
       printf("getNextToken() : ");
       printf("ln_8_72 length : (%d)Án",strlen(curr_ln_obj.ln_8_72));
    */
    Ë

    printf("5 bug tracker global_ret (%s) address(%d) char_len(%d)"Á
           "  single quote (%d) alphanumeric (%d)"
                       ,global_ret->node.literal.value
                       ,global_ret
                       ,global_ret->node.literal.char_length
                       ,global_ret->node.literal.bool_singl_q
                       ,global_ret->node.literal.bool_alphanumeric);
    /* call tokenizer to get token */
    _ret = tokenizer(curr_ln_obj.ln_8_72);
    _ret.tkn_lnnum =curr_ln_obj.ln_num;


    /*
    printf("getNextToken() : ");
    printf("tkn_lnnum      : (%d)Án",_ret.tkn_lnnum);
    */

    /* do not let ENDLine token escalde to parser */
    /* Recursive !!! */
    if (strcmp(_ret.tkn_type,"ENDLINE")==0) È
        printf("getNextToken() : getting recursive ! Án");
        getNextToken();
    Ë

    /* If Token = ERROR ERROR and lde to parser */
    /* Recursive !!! */
    /*
    if ((strcmp(_ret.tkn_type,"ERROR")==0) && (next_ln.ln_str=="$"))È
        printf("getNextToken() : ERROR & $ => PROGRAM$ Án");
        _ret.tkn_type="PROGRAM$";
        _ret.tkn_val="PROGRAM$";
        getNextToken();
    Ë
    */
    printf("4 bug tracker global_ret (%s) address(%d) char_len(%d)"Á
           "  single quote (%d) alphanumeric (%d)"
                       ,global_ret->node.literal.value
                       ,global_ret
                       ,global_ret->node.literal.char_length
                       ,global_ret->node.literal.bool_singl_q
                       ,global_ret->node.literal.bool_alphanumeric);
    return _ret;

Ë

ln_str_num getLineString (int linenum) È

    ln_str_num _ret;

    /* if current line num > num of last line return $ */
    if(linenum > lnumlast)È

     /*_ret.ln_str = "PROGRAM$"; */
       _ret.ln_num = 0;

    Ë
    else
    È
       if(linenum < 1)È

     /*   _ret.ln_str = "^";  */
          _ret.ln_num = 0;

       Ë
       else
       È
           /* else return line from rawcode and line number   */
           _ret.ln_str = rawcode›linenum-1~;
           _ret.ln_num = linenum;
       Ë

    Ë
    /*
    printf ("getLineString() : ");
    printf ("num:(%d)str:<%s>Án",_ret.ln_num,_ret.ln_str);
    */
    return _ret;

Ë

ln_obj preprocessor(ln_str_num lnstrnum)È

    ln_obj _ret=È"","","","",0,0Ë;
    int i=0;
    /*
    if ((strcmp(lnstrnum.ln_str,"PROGRAM$")==0)) È
        *(_ret.ln_8_72)='$';
        *(_ret.ln_8_72+1)='Á0';
        return _ret;
    Ë
    */
    if (strlen(lnstrnum.ln_str)==80)È

       strncpy(_ret.ln_1_6,lnstrnum.ln_str,6);
       *(_ret.ln_1_6+6) = 'Á0';
       strncpy(_ret.ln_7,lnstrnum.ln_str+6,1);
       *(_ret.ln_7+1) = 'Á0';
       strncpy(_ret.ln_8_72,lnstrnum.ln_str+7,65);
       *(_ret.ln_8_72+65) = 'Á0';
       strncpy(_ret.ln_73_80,lnstrnum.ln_str+72,8);
       *(_ret.ln_73_80+8) = 'Á0';

       while (isspace(*(_ret.ln_8_72 + i))) i++;

       _ret.ln_indent= i+1;
       _ret.ln_num=lnstrnum.ln_num;


    Ë
    /*
    printf("preprocessor() : ");
    printf("ln_1_6<%s>ln_7<%s>Án",_ret.ln_1_6,_ret.ln_7);

    printf("preprocessor() : ");
    printf("ln_8_72<%s>ln_73_80<%s>Án",_ret.ln_8_72,_ret.ln_73_80);
    printf("preprocessor() : ");
    printf("ln_indent(%d)ln_num(%d)Án",_ret.ln_indent,_ret.ln_num);
    */
    /* '*' = 92 */
    /* '-' = 96 */
    /* '/' = 97 */

    if (((*(_ret.ln_7))==92) !! ((*(_ret.ln_7))==97)) È
        printf ("preprocessor()1: Comment line (%d)Án",_ret.ln_num);
        printf ("preprocessor()2:_ret.ln_8_72 <%s>Án",_ret.ln_8_72);
    /*  sprintf(_ret.ln_8_72,"%-65s"); */
        *(_ret.ln_8_72)='Á0';
        printf ("preprocessor()3:_ret.ln_8_72 <%s>Án",_ret.ln_8_72);
        printf ("preprocessor()4: len ln_8_72 (%d)Án",
               strlen(_ret.ln_8_72));
        return _ret;
    Ë

    if ((*(_ret.ln_7))==96)  È
        printf ("preprocessor()5: Continuation not supported yet");
        printf ("(%d)Án",_ret.ln_num);
        *(_ret.ln_8_72)='$';
        *(_ret.ln_8_72+1)='Á0';
        return _ret;
    Ë

    if (_ret.ln_indent == 66) È
        printf ("preprocessor()6: Empty Line   (%d)Án",_ret.ln_num);
        *(_ret.ln_8_72)='Á0';
        return _ret;
    Ë

    return _ret;

Ë

token peekNextToken()È

    return getNextToken();
Ë

£include <stdio.h>
£include <stdlib.h>
£include <string.h>

£include "Rexxcomh"

       int    argc;                 /* nombre d'arguments  */
       int    cursl;                /* position ligne   de cursor */
       int    cursc;                /* position colonne de cursor */
       char   rawcode›20000~›81~;   /* code Cobol brute           */
       int    lnumlast;             /* numero de la derniËre ligne*/
       char*  mainret;              /* zone retour                */

       int    curr_ln_num;          /* current line being parsed  */

/* bug connu : rawcode depasse le code reel par 14 car ‡ la fin */
int getArgsRexx() È

       int    i=0;
       int    rawCode_length=0;
       int    rawCode_mod_80=0;
       int    rawCode_div_80=0;
       /*
       printf("first arg        : %s Án",        __osplist›0~) ;
       printf("strcmp           : %d Án", strcmp(__osplist›0~,""));
       printf("first arg to int : %d Án",   atoi(__osplist›0~));
       */
       if ((strcmp(__osplist›0~,"")) && (atoi(__osplist›0~) > 0)) È
          argc = atoi(__osplist›0~);
          printf("getArgsRexx() : ");
          printf("argc          : (%d) Án", argc);
       Ë
       else È
          printf("getArgsRexx() : ");
          printf("Required argument argc not found or not numeric Án");

          return -1;
       Ë

       if ((strcmp(__osplist›1~,"")) && (atoi(__osplist›1~) > 0)) È
          cursc = atoi(__osplist›1~);
          printf("getArgsRexx() : ");
          printf("cursc         : (%d) Án", cursc);
       Ë
       else È
          printf("getArgsRexx() : ");
          printf("Required argument cursc not found or not numericÁn");
          return -1;
       Ë

       if ((strcmp(__osplist›2~,"")) && (atoi(__osplist›2~) > 0)) È
          cursl = atoi(__osplist›2~);
          printf("getArgsRexx() : ");
          printf("cursl         : (%d) Án", cursl);
          /* current line number to increment on each read */
          curr_ln_num = cursl;
       Ë
       else È
          printf("getArgsRexx() : ");
          printf("Required argument cursl not found or not numericÁn");
          return -1;
       Ë


       if ((strcmp(__osplist›4~,"")) && (atoi(__osplist›4~) > 0)) È
          lnumlast = atoi(__osplist›4~);
          printf("getArgsRexx() : ");
          printf("lnumlast      : (%d) Án", lnumlast);
       Ë
       else È
          printf("getArgsRexx() : ");
       printf("Required argument lnumlast not found or not numericÁn");
          return -1;
       Ë

       rawCode_length = strlen(__osplist›3~);
       rawCode_mod_80 = strlen(__osplist›3~)%80;
       rawCode_div_80 = strlen(__osplist›3~)/80;

       printf("getArgsRexx() : ");
       printf("rawcode length : (%d) Án", rawCode_length);
       printf("getArgsRexx() : ");
       printf("modulo 80      : (%d) Án", rawCode_mod_80);
       printf("getArgsRexx() : ");
       printf("divide by 80   : (%d) Án", rawCode_div_80);
       /*
       printf("<%.*s>Án",80 + rawCode_mod_80,
              __osplist›3~+(rawCode_length-(80+rawCode_mod_80)));
       */
       if (rawCode_div_80 ß= lnumlast ) È

          printf("getArgsRexx() : ");
          printf("lnumlast is not equal to rawCode_div_80Án");
          return -1;
       Ë

       if ((rawCode_length       > 0 )
    /* && ((strlen(__osplist›3~) % 80) == 0) */
       && ((rawCode_div_80           ) <= 20000)) È

          for (i=0;i<(strlen(__osplist›3~)/80);i++) È

          strncpy(rawcode›i~,__osplist›3~+(80*i),80);
          rawcode›i~›80~ = 'Á0';
          Ë

       Ë
       else È
          printf("getArgsRexx() : ");
          printf("Required argument rawcode invalid Án");
          return -1;
       Ë
       /*
       printf ("i :   %d Án", i );
       int j;
       for (j=0;j<i;j=j+1000) È

          printf("%sÁn",rawcode›j~);
       Ë
       */

Ë

£include <regex.h>
£include <stdio.h>
£include <stdlib.h>
£include <string.h>

£include "tokenzrh"

£define NB_MATCH_MAX     7
£define NB_REGEX_MAX    30

  /*---------------------------------------------------------------*/
  /* FTA1: modulariser le code : regex, communication avec REXX    */
  /*       reduction du string , creation de la liste des tokens   */
  /*---------------------------------------------------------------*/
  /* la reduction du string enleve le separteur de debut           */
  /* (espace, virgule mais pas ' pour string )                     */
  /*---------------------------------------------------------------*/
  /* L'ordre de check des REgex semblables est :                   */
  /* -Keyword avant identifier, c ce qui en fait des mots reserves */
  /* -Dernier regex est : Espace puis enfin Erreur.                */
  /* -hexa literal avant identifier                                */
  /* exemple : x'ff'=> hex literal                                 */
  /* exemple : A'ff'=> identifier + string literal                 */
  /* -Choisir le match le plus long                                */
  /* exemple : **   => exponent au lieu de multiply                */
  /*           2,2  => decimal au lieu de integer                  */
  /*           a-b  => identifier a au lieu de a - b               */
  /*           a+b  => a + b                                       */
  /*---------------------------------------------------------------*/


token tokenizer(char* ln_8_72)
È
    token _ret = È0,0,0,"ERROR","ERROR"Ë;

    static int reduction_len;

    /* Regex for token type         */
    regex_t    pregIdent;
    regex_t    pregPicChars;
    regex_t    pregLiterNum;
    regex_t    pregLiterQuot;
    regex_t    pregKeywoAll;
    regex_t    pregSymbols;
    regex_t    pregEndLine;
    regex_t    pregSpace;

    /* Regex for token attributes   */
    regex_t    pregSpclReg;
    regex_t    pregFgrtvConst;
    regex_t    pregNumeric;
    regex_t    pregQuoted;
    regex_t    pregSQuoted;
    regex_t    pregDQuoted;
    regex_t    pregHex;
    regex_t    pregAlphanum;
    regex_t    pregIntgr;
    regex_t    pregDecim;
    regex_t    pregUnsigned;
    regex_t    pregPositive;
    regex_t    pregNegative;
    regex_t    pregLvlnum;
    regex_t    pregRelOp;
    regex_t    pregAritOp;

 /* regex_t    pregLiter1;
    regex_t    pregLiter2;
    regex_t    pregPerio;
    regex_t    pregLvl66;
    regex_t    pregLvl88;
    regex_t    pregHexL1;
    regex_t    pregHexL2;
    regex_t    pregLBrack;
    regex_t    pregRBrack;
    regex_t    pregPlus;
    regex_t    pregMinus;
    regex_t    pregExpon;
    regex_t    pregMultp;
    regex_t    pregDivid;
    regex_t    pregEqual;
    regex_t    pregColon;
    regex_t    pregDollar;
    regex_t    pregUintgr; */

  /*    _____________________________________________________
      _(                                                     )_
     =_                I D E N T I F I E R                    _=
       (_____________________________________________________)
                                                                  */

  /*----------------------------*/
  /* Pattern pour indentifier   */
  /*--------------------------------------------------------------*/
  /* - SÈparateur dÈbut: aucan ou plusieurs espaces ou virgules   */
  /* - Corps : Un mot cobol composÈ de lettres et chiffres        */
  /*   ainsi que tiret et undersoce qui doivent pas apparaitre    */
  /*   au debut ou ‡ a fin. doit contenir au moins une lettre     */
  /* - SÈparateur fin  : point, espace, virgule, fin, quote ou "  */
  /*--------------------------------------------------------------*/

    char     *ptrnIdent = "^( !,)*"                                Á
   "((›0-9~+›-_~*)*›0-9~*›A-Za-z~›A-Za-z0-9~*(›-_~+›A-Za-z0-9~+)*)"Á
                          "(.*)";

  /*    _____________________________________________________
      _(                                                     )_
     =_            P I C T U R E  C H A R A C T E R           _=
       (_____________________________________________________)
                                                                  */

  /*-------------------------------------------*/
  /* FTA1: ponctuation                         */
  /* FTA2: CR et DB                            */
  /*--------------------------------------------------------------*/
  /* - picture-string =  currency? (picchar+ repeat?)+            */
  /*   currency       =  $                                        */
  /*   picchar        =  ›ABEGPSVXZabegpsvxz90Á+Á-Á*Á$~           */
  /*   repeat         =  "(" ›0-9~+ ")"                           */
  /*--------------------------------------------------------------*/

    char     *ptrnPicChars = "(^"                              Á
                             "(›ABEGPSVXZabegpsvxz90ÁÁ+ÁÁ-ÁÁ*ÁÁ$~+))"Á
                             "(( !,)*!ÁÁ()(.*)";


  /*    _____________________________________________________
      _(                                                     )_
     =_             L I T E R A L  N U M E R I C              _=
       (_____________________________________________________)
                                                                  */

  /*--------------------------------------------------------------*/
  /* - SÈparateur dÈbut: Zero ou plusieurs : espaces ou virgules  */
  /* - Corps : Commence par le separateur de string quote ou "    */
  /*   puis zero ou une suite de caractËres sauf separateur de    */
  /*   string ou un double separateur de string et finit par le   */
  /*   meme separateur de string                                  */
  /* - SÈparateur fin  : point, espace, virgule, fin, quote ou "  */
  /*--------------------------------------------------------------*/
    char      *ptrnLiterNum = "^( !,)*("                          Á
                           "(›ÁÁ+ÁÁ-~?›0-9~*,›0-9~+)!"  /* -9,7 */Á
                           "(›ÁÁ+ÁÁ-~?›0-9~+)"         /* +987 */Á
                      /*    ")(›^'~!$)(.*)"; */                   Á
                           ")(.*)";                               Á
  /*    _____________________________________________________
      _(                                                     )_
     =_             L I T E R A L  Q U O T E                  _=
       (_____________________________________________________)
                                                                  */

    char      *ptrnLiterQuot = "^( !,)*("                         Á
                           "('(›^'~!'')*')!"            /*  '.' */ Á
                           "(Á"(›^Á"~!Á"Á")*Á")!"       /*  "." */ Á
                           "(›Xx~›'~›0-9A-Fa-f~+›'~)!"  /* x'.' */ Á
                           "(›Xx~›Á"~›0-9A-Fa-f~+›Á"~)" /* x"." */ Á
                      /*    ")(›^'~!$)(.*)"; */                    Á
                           ")(.*)";                                Á
  /*    _____________________________________________________
      _(                                                     )_
     =_                   K E Y W O R D                       _=
       (_____________________________________________________)
                                                                  */

    char       *ptrnKeywoAll = "^( !,)*("                          Á
    /*   A   */                                                    Á
    "ACCEPT!ALPHABETIC-LOWER!APPLY!"                               Á
    "ACCESS!ALPHABETIC-UPPER!ARE!"                                 Á
    "ADD!ALPHANUMERIC!AREA!"                                       Á
    "ALPHANUMERIC-EDITED!AREAS!ADDRESS!"                           Á
    "ADVANCING!ALSO!ASCENDING!"                                    Á
    "AFTER!ALTER!ASSIGN!"                                          Á
    "ALTERNATE!AT!ALL!"                                            Á
    "ALPHABET!AND!AUTHOR!"                                         Á
    "ALPHABETIC!ANY!"                                              Á
    /*   B   */                                                    Á
    "BASIS!BINARY!BOTTOM!"                                         Á
    "BEFORE!BLANK!BY!"                                             Á
    "BEGINNING!BLOCK!"                                             Á
    /*   C   */                                                    Á
    "CALL!COLUMN!COMPUTATIONAL-5!"                                 Á
    "CANCEL!COM-REG!COMPUTE!"                                      Á
    "CBL!COMMA!CONFIGURATION!"                                     Á
    "CD!COMMON!CONTAINS!"                                          Á
    "CF!COMMUNICATION!CONTENT!"                                    Á
    "CH!COMP!CONTINUE!"                                            Á
    "CHARACTER!COMP-1!CONTROL!"                                    Á
    "CHARACTERS!COMP-2!CONTROLS!"                                  Á
    "CLASS!COMP-3!CONVERTING!"                                     Á
    "CLASS-ID!COMP-4!COPY!"                                        Á
    "CLOCK-UNITS!COMP-5!CORR!"                                     Á
    "CLOSE!COMPUTATIONAL!CORRESPONDING!"                           Á
    "COBOL!COMPUTATIONAL-1!COUNT!"                                 Á
    "CODE!COMPUTATIONAL-2!CURRENCY!"                               Á
    "CODE-SET!COMPUTATIONAL-3!"                                    Á
    "COLLATING!COMPUTATIONAL-4!"                                   Á
    /*   D   */                                                    Á
    "DATA!DEBUG-SUB-1!DESTINATION!"                                Á
    "DATE-COMPILED!DEBUG-SUB-2!DETAIL!"                            Á
    "DATE-WRITTEN!DEBUG-SUB-3!DISPLAY!"                            Á
    "DAY!DEBUGGING!DISPLAY-1!"                                     Á
    "DAY-OF-WEEK!DECIMAL-POINT!DIVIDE!"                            Á
    "DBCS!DECLARATIVES!DIVISION!"                                  Á
    "DE!DELETE!DOWN!"                                              Á
    "DEBUG-CONTENTS!DELIMITED!DUPLICATES!"                         Á
    "DELIMITER!DYNAMIC!DEBUG-ITEM!"                                Á
    "DEPENDING!DEBUG-LINE!"                                        Á
    "DESCENDING!DEBUG-NAME!"                                       Á
    /*   E   */                                                    Á
    "EGCS!END-INVOKE!ENDING!"                                      Á
    "EGI!END-MULTIPLY!ENTER!"                                      Á
    "EJECT!END-OF-PAGE!ENTRY!"                                     Á
    "ELSE!END-PERFORM!ENVIRONMENT!"                                Á
    "EMI!END-READ!EOP!"                                            Á
    "ENABLE!END-RECEIVE!EQUAL!"                                    Á
    "END!END-RETURN!ERROR!"                                        Á
    "END-ADD!END-REWRITE!ESI!"                                     Á
    "END-CALL!END-SEARCH!EVALUATE!"                                Á
    "END-COMPUTE!END-START!EVERY!"                                 Á
    "END-DELETE!END-STRING!EXCEPTION!"                             Á
    "END-DIVIDE!END-SUBTRACT!EXIT!"                                Á
    "END-EVALUATE!END-UNSTRING!EXTEND!"                            Á
    "END-IF!END-WRITE!EXTERNAL!"                                   Á
    /*   F   */                                                    Á
    "FALSE!FILLER!FOR!"                                            Á
    "FD!FINAL!FROM!"                                               Á
    "FILE!FIRST!FUNCTION!"                                         Á
    "FILE-CONTROL!FOOTING!"                                        Á
    /*   G   */                                                    Á
                                                                   Á
    "GENERATE!GO!GROUP!"                                           Á
    "GIVING!GOBACK!"                                               Á
    "GLOBAL!GREATER!"                                              Á
    /*   H   */                                                    Á
                                                                   Á
    "HEADING!HIGH-VALUE!HIGH-VALUES!"                              Á
    /*   I   */                                                    Á
    "I-O!INDICATE!INSPECT!"                                        Á
    "I-O-CONTROL!INHERITS!INSTALLATION!"                           Á
    "ID!INITIAL!INTO!"                                             Á
    "IDENTIFICATION!INITIALIZE!INVALID!"                           Á
    "IF!INITIATE!INVOKE!"                                          Á
    "IN!INPUT!IS!"                                                 Á
    "INDEX!INPUT-OUTPUT!"                                          Á
    "INDEXED!INSERT!"                                              Á
    /*   J   */                                                    Á
    "JUST!JUSTIFIED!"                                              Á
    /*   K   */                                                    Á
    "KANJI!KEY!"                                                   Á
    /*   L   */                                                    Á
    "LABEL!LIMIT!LINES!"                                           Á
    "LAST!LIMITS!LINKAGE!"                                         Á
    "LEADING!LINAGE!LOCAL-STORAGE!"                                Á
    "LEFT!LINAGE-COUNTER!LOCK!"                                    Á
    "LINE!LENGTH!LOW-VALUE!"                                       Á
    "LESS!LINE-COUNTER!LOW-VALUES!"                                Á
    /*   M   */                                                    Á
    "MEMORY!METHOD!MORE-LABELS!"                                   Á
    "MERGE!METHOD-ID!MOVE!"                                        Á
    "MESSAGE!MODE!MULTIPLE!"                                       Á
    "METACLASS!MODULES!MULTIPLY!"                                  Á
    /*   N   */                                                    Á
    "NATIVE!NO!NUMBER!"                                            Á
    "NATIVE_BINARY!NOT!NUMERIC!"                                   Á
    "NEGATIVE!NULL!NUMERIC-EDITED!"                                Á
    "NEXT!NULLS!"                                                  Á
    /*   O   */                                                    Á
    "OBJECT!ON!OTHER!"                                             Á
    "OBJECT-COMPUTER!OPEN!OUTPUT!"                                 Á
    "OCCURS!OPTIONAL!OVERFLOW!"                                    Á
    "OF!OR!OVERRIDE!"                                              Á
    "OFF!ORDER!"                                                   Á
    "OMITTED!ORGANIZATION!"                                        Á
    /*   P   */                                                    Á
    "PACKED-DECIMAL!PIC!PROCEDURE-POINTER!"                        Á
    "PADDING!PICTURE!PROCEDURES!"                                  Á
    "PAGE!PLUS!PROCEED!"                                           Á
    "PAGE-COUNTER!POINTER!PROCESSING!"                             Á
    "PASSWORD!POSITION!PROGRAM!"                                   Á
    "PERFORM!POSITIVE!PROGRAM-ID!"                                 Á
    "PF!PRINTING!PURGE!"                                           Á
    "PH!PROCEDURE!"                                                Á
    /*   Q   */                                                    Á
    "QUEUE!QUOTE!QUOTES!"                                          Á
    /*   R   */                                                    Á
    "RANDOM!RELATIVE!RESERVE!"                                     Á
    "RD!RELEASE!RESET!"                                            Á
    "READ!RELOAD!RETURN!"                                          Á
    "READY!REMAINDER!RETURN-CODE!"                                 Á
    "RECEIVE!REMOVAL!RETURNING!"                                   Á
    "RECORD!RENAMES!REVERSED!"                                     Á
    "RECORDING!REPLACE!REWIND!"                                    Á
    "RECORDS!REPLACING!REWRITE!"                                   Á
    "RECURSIVE!REPORT!RF!"                                         Á
    "REDEFINES!REPORTING!RH!"                                      Á
    "REEL!REPORTS!RIGHT!"                                          Á
    "REFERENCE!REPOSITORY!ROUNDED!"                                Á
    "REFERENCES!RERUN!RUN!"                                        Á
    /*   S   */                                                    Á
    "SAME!SIGN!STANDARD!"                                          Á
    "SD!SIZE!STANDARD-1!"                                          Á
    "SEARCH!SKIP1!STANDARD-2!"                                     Á
    "SECTION!SKIP2!START!"                                         Á
    "SECURITY!SKIP3!STATUS!"                                       Á
    "SEGMENT!SORT!STOP!"                                           Á
    "SEGMENT-LIMIT!SORT-CONTROL!STRING!"                           Á
    "SELECT!SORT-CORE-SIZE!SUB-QUEUE-1!"                           Á
    "SELF!SORT-FILE-SIZE!SUB-QUEUE-2!"                             Á
    "SEND!SORT-MERGE!SUB-QUEUE-3!"                                 Á
    "SENTENCE!SORT-MESSAGE!SUBTRACT!"                              Á
    "SEPARATE!SORT-MODE-SIZE!SUM!"                                 Á
    "SEQUENCE!SUPER!SORT-RETURN!"                                  Á
    "SEQUENTIAL!SOURCE!SUPPRESS!"                                  Á
    "SERVICE!SOURCE-COMPUTER!SYMBOLIC!"                            Á
    "SET!SYNC!SPACE!"                                              Á
    "SHIFT-IN!SYNCHRONIZED!SPACES!"                                Á
    "SHIFT-OUT!SPECIAL-NAMES!"                                     Á
    /*   T   */                                                    Á
    "TABLE!TEXT!TITLE!"                                            Á
    "THAN!TO!TALLY!"                                               Á
    "TALLYING!THEN!TOP!"                                           Á
    "TAPE!THROUGH!TRACE!"                                          Á
    "TERMINAL!THRU!TRAILING!"                                      Á
    "TERMINATE!TIME!TRUE!"                                         Á
    "TEST!TIMES!TYPE!"                                             Á
    /*   U   */                                                    Á
    "UNIT!UP!USE!"                                                 Á
    "UNSTRING!UPON!USING!"                                         Á
    "UNTIL!USAGE!"                                                 Á
    /*   V   */                                                    Á
    "VALUE!VALUES!VARYING!"                                        Á
    /*   W   */                                                    Á
    "WHEN!WORDS!WRITE-ONLY!"                                       Á
    "WORKING-STORAGE!WHEN-COMPILED!"                               Á
    "WITH!WRITE"                                                   Á
    /*   X   */                                                    Á
    /*   Y   */                                                    Á
    /*   Z   */                                                    Á
    "ZERO!ZEROES!ZEROS!"                                           Á
    /*  END  */                                                    Á
    ")(ÁÁ.! !,!$!'!Á")(.*)";

  /*    _____________________________________________________
      _(                                                     )_
     =_                   S Y M B O L S                       _=
       (_____________________________________________________)
                                                                  */

    char       *ptrnSymbols = "^( !,)*("                          Á
                            "ÁÁ.!"             /*  .        */    Á
                            "ÁÁ+!ÁÁ-!"         /*  +  -     */    Á
                            "ÁÁ(!ÁÁ)!"         /*  (  )     */    Á
                            "ÁÁ*ÁÁ*!ÁÁ*!ÁÁ/!"  /*  ** *  /  */    Á
                            "<=!>=!"           /*  <= >=    */    Á
                            "<!>!=!"           /*  <  >  =  */    Á
                            ":!ÁÁ$"            /*  :  $     */    Á
                            ")(.*)";

  /*    _____________________________________________________
      _(                                                     )_
     =_                   E N D  L I N E                     _=
       (_____________________________________________________)
                                                                  */

    char       *ptrnEndLine = "^(( !,)*)$";

  /*    _____________________________________________________
      _(                                                     )_
     =_                     S P A C E                        _=
       (_____________________________________________________)
                                                                  */

    char       *ptrnSpace = "(^( !,)+)";


  /*    ______________________________
      _(                              )_
     =_    SPECIAL REGISTER KEYWORD    _=
       (______________________________)
                                                                  */

    char       *ptrnSpclReg  = "^( !,)*"                           Á
                               "(ADDRESS!"                         Á
                               "DEBUG-ITEM!DEBUG-LINE!DEBUG-NAME!" Á
                               "LENGTH!RETURN-CODE!SORT-RETURN!"   Á
                               "WHEN-COMPILED!TALLY)"              Á
                               "(ÁÁ.! !,!$!'!Á")(.*)";

  /*    ______________________________
      _(                              )_
     =_  FIGURATIVE CONSTANTS KEYWORD  _=
       (______________________________)
                                                                  */

    char       *ptrnFgrtvConst = "^( !,)*("                        Á
                                 "ALL!"                            Á
                                 "ZERO!ZEROS!ZEROES!"              Á
                                 "SPACE!SPACES!"                   Á
                                 "HIGH-VALUE!HIGH-VALUES!"         Á
                                 "LOW-VALUE!LOW-VALUES!"           Á
                                 "QUOTE!QUOTES"                    Á
                                 ")(ÁÁ.! !,!$!'!Á")(.*)";

  /*    _____________________________
      _(                             )_
     =_        NUMERIC LITERAL        _=
       (_____________________________)
                                                                  */

    char       *ptrnNumeric = "^("                                  Á
                              "ZERO!ZEROS!ZEROES!"                  Á
                              "(›ÁÁ+ÁÁ-~?›0-9~+)!"       /* Intgr */Á
                              "(›ÁÁ+ÁÁ-~?›0-9~*,›0-9~+)" /* Decim */Á
                              ")$";

  /*    _____________________________
      _(                             )_
     =_        QUOTED LITERAL         _=
       (_____________________________)
                                                                  */

    char       *ptrnQuoted = "^("                                    Á
                             "('(›^'~!'')*')!"            /*  '.' */ Á
                             "(Á"(›^Á"~!Á"Á")*Á")!"       /*  "." */ Á
                             "(›Xx~›'~›0-9A-Fa-f~+›'~)!"  /* x'.' */ Á
                             "(›Xx~›Á"~›0-9A-Fa-f~+›Á"~)" /* x"." */ Á
                              ")$";

  /*    _____________________________
      _(                             )_
     =_    SINGLE QUOTED LITERAL      _=
       (_____________________________)
                                                                  */

    char       *ptrnSQuoted = "^("                                  Á
                             "('(›^'~!'')*')!"            /*  '.' */ Á
                             "(›Xx~›'~›0-9A-Fa-f~+›'~)"  /* x'.' */ Á
                              ")$";

  /*    _____________________________
      _(                             )_
     =_    DOUBLE QUOTED LITERAL      _=
       (_____________________________)
                                                                  */

    char       *ptrnDQuoted = "^("                                   Á
                             "(Á"(›^Á"~!Á"Á")*Á")!"       /*  "." */ Á
                             "(›Xx~›Á"~›0-9A-Fa-f~+›Á"~)" /* x"." */ Á
                              ")$";

  /*    _____________________________
      _(                             )_
     =_      HEXADECIMAL LITERAL      _=
       (_____________________________)
                                                                  */

    char       *ptrnHex     = "^("                                   Á
                             "(›Xx~›'~›0-9A-Fa-f~+›'~)!"  /* x'.' */ Á
                             "(›Xx~›Á"~›0-9A-Fa-f~+›Á"~)" /* x"." */ Á
                              ")$";

  /*    _____________________________
      _(                             )_
     =_      ALPHANUMERIC LITERAL     _=
       (_____________________________)
                                                                  */

    char       *ptrnAlphanum = "^("                                  Á
                             "('(›^'~!'')*')!"            /*  '.' */ Á
                             "(Á"(›^Á"~!Á"Á")*Á")"       /*  "." */ Á
                              ")$";

  /*    _____________________________
      _(                             )_
     =_        INTEGER LITERAL        _=
       (_____________________________)
                                                                  */

    char       *ptrnIntgr    = "^("                                 Á
                             "(›ÁÁ+ÁÁ-~?›0-9~+)"          /*  987 */ Á
                              ")$";

  /*    _____________________________
      _(                             )_
     =_        DECIMAL LITERAL        _=
       (_____________________________)
                                                                  */

    char       *ptrnDecim    = "^("                                Á
                             "(›ÁÁ+ÁÁ-~?›0-9~*,›0-9~+)"             Á
                              ")$";

  /*    _____________________________
      _(                             )_
     =_      UNSIGNED NUMERIC         _=
       (_____________________________)
                                                                  */

    char       *ptrnUnsigned = "^("                               Á
                             "(›0-9~+)!"                /* 987 */  Á
                             "(›0-9~*,›0-9~+)"          /* 9,7 */  Á
                              ")$";

  /*    _____________________________
      _(                             )_
     =_      POSITIVE NUMERIC         _=
       (_____________________________)
                                                                  */

    char       *ptrnPositive = "^("                               Á
                             "(ÁÁ+›0-9~+)!"             /* +987 */ Á
                             "(ÁÁ+›0-9~*,›0-9~+)"       /* +9,7 */ Á
                              ")$";

  /*    _____________________________
      _(                             )_
     =_      NEGATIVE NUMERIC         _=
       (_____________________________)
                                                                  */

    char       *ptrnNegative = "^("                                 Á
                             "(ÁÁ-›0-9~+)!"             /* -987 */ Á
                             "(ÁÁ-›0-9~*,›0-9~+)"       /* -9,7 */ Á
                              ")$";

  /*    _____________________________
      _(                             )_
     =_         LEVEL NUMBER          _=
       (_____________________________)
                                                                  */

    char       *ptrnLvlNum = "^("                                   Á
                             "(›0~?›1-9~!›1-4~›0-9~!66!77!88)"     Á
                              ")$";

  /*    _____________________________
      _(                             )_
     =_      RELATIONAL OPERATOR      _=
       (_____________________________)
                                                                  */

    char       *ptrnRelOp  = "^("                                   Á
                             "(<!>!<=!>=!=)"                       Á
                              ")$";

  /*    _____________________________
      _(                             )_
     =_      ARITHMITIC OPERATOR      _=
       (_____________________________)
                                                                  */

    char       *ptrnAritOp  = "^("                                  Á
                              "ÁÁ+!ÁÁ-!"         /*  +  -     */   Á
                              "ÁÁ(!ÁÁ)!"         /*  (  )     */   Á
                              "ÁÁ*ÁÁ*!ÁÁ*!ÁÁ/"  /*  ** *  /  */   Á
                              ")$";

  /*
    char       *ptrnLiter2 = "^( !,)*"                              Á
                            "(Á"(›^Á"~!Á"Á")*Á")"                   Á
                            "(›^Á"~!$)(.*)";
  */
  /*-----------------------------------*/
  /* Pattern pour HEXA Literal X'FF'   */
  /*-----------------------------------*/
  /*char       *ptrnHexL1  = "^( !,)*"                              Á
                            "(›Xx~›Á"~›0-9A-Fa-f~+›Á"~)"            Á
                            "(›^Á"~!$)(.*)";

    char       *ptrnHexL2  = "^( !,)*"                              Á
                            "(›Xx~›'~›0-9A-Fa-f~+›'~)"              Á
                            "(›^'~!$)(.*)";
  */
  /*-----------------------------*/
  /* Pattern pour Integer        */
  /*-----------------------------*/
  /*char       *ptrnIntgr = "^( !,)*"                             Á
                            "(›ÁÁ+ÁÁ-~?›0-9~+)"                   Á
                            "(.)(.*)";
  */
  /*-----------------------------*/
  /* Pattern pour Level Number   */
  /*-----------------------------*/
  /*char       *ptrnLvlnum = "(›0~?›1-9~!›1-4~›0-9~!77)";

  */
  /*-----------------------------*/
  /* Pattern pour Level 66       */
  /*-----------------------------*/
  /*char       *ptrnLvl66  = "66";
  */
  /*-----------------------------*/
  /* Pattern pour Level 88       */
  /*-----------------------------*/
  /*char       *ptrnLvl88  = "88";
  */
  /*-----------------------------*/
  /* Pattern pour Decimal        */
  /*-----------------------------*/
  /*char       *ptrnDecim  = "^( !,)*"                             Á
                            "(›ÁÁ+ÁÁ-~?›0-9~*,›0-9~+)"             Á
                            "(.)(.*)";
  */
  /*-------------------------------*/
  /* Pattern pour Unsigned integer */
  /*-------------------------------*/
  /*char       *ptrnUintgr  = "^(›0-9~+)$";
  */

  /*---------------------------------------------------------------*/
  /*---------------------------------------------------------------*/
  /*---------------------------------------------------------------*/

    int         rc=0;
    int         i=0;
    int         j=0;
    size_t      nmatch = NB_MATCH_MAX;
    regmatch_t  pmatch›NB_MATCH_MAX~;
    char        buffer›100~;
    char        str›480~;

    static int  rets_len =0;
    static char rets_data›480~="";

    char        args›480~="";

    strcpy(args,ln_8_72);

  /*---------------------------------------------------------------*/
  /*---------------------------------------------------------------*/
  /*---------------------------------------------------------------*/

  /*---------------------------------------------------------------*/
  /* Ordre des REGEX                                               */
  /*---------------------------------------------------------------*/
  /* 1  - Keyword                                                  */
  /* 10 - Special registers                                        */
  /* 101- Figurative constants                                     */
  /* 11 - Hexa Literal1 & Hexa Literal2                            */
  /* 2  - Identifier                                               */
  /* 3  - Literal1 & Literal2                                      */
  /* 31 - Decimal                                                  */
  /* 32 - Integer                                                  */
  /* 4  - Period                                                   */
  /*      & plus minus equal expon divid multp Lbrack Rbrack colon */
  /* 5  - EndLine                                                  */
  /* 6  - Error                                                    */
  /*---------------------------------------------------------------*/
    /* Pointer Array for pregs order for type*/
    regex_npp   pregs ›NB_REGEX_MAX~;

    int nb_regex_for_type;

    /* Default pregs order (empty context) */

    pregs›j~.name ="KEYWORD";
    pregs›j~.ptrn =ptrnKeywoAll;
    pregs›j~.preg =&pregKeywoAll;
    j++;
    pregs›j~.name ="LITERAL";
    pregs›j~.ptrn =ptrnLiterQuot;
    pregs›j~.preg =&pregLiterQuot;
    j++;
    pregs›j~.name ="LITERAL";
    pregs›j~.ptrn =ptrnLiterNum;
    pregs›j~.preg =&pregLiterNum;
    j++;
    pregs›j~.name ="IDENTIFIER";
    pregs›j~.ptrn =ptrnIdent;
    pregs›j~.preg =&pregIdent;
    j++;
    pregs›j~.name ="SYMBOL";
    pregs›j~.ptrn =ptrnSymbols;
    pregs›j~.preg =&pregSymbols;
    j++;
    pregs›j~.name ="ENDLINE";
    pregs›j~.ptrn =ptrnEndLine;
    pregs›j~.preg =&pregEndLine;
    j++;

    /* Space ??
    pregs›j~.name ="SPACE";
    pregs›j~.ptrn =ptrnSpace;
    pregs›j~.preg =&pregSpace;
    j++; */

 /* pregs›j~.name ="KEYWORD";
    pregs›j~.ptrn =ptrnKeywoAll;
    pregs›j~.preg =&pregKeywoAll;
    j++;
    pregs›j~.name ="SPECIAL REGISTER";
    pregs›j~.ptrn =ptrnSpclReg;
    pregs›j~.preg =&pregSpclReg;
    j++;
    pregs›j~.name ="FIGURATIVE CONST";
    pregs›j~.ptrn =ptrnFgrtvConst;
    pregs›j~.preg =&pregFgrtvConst;
    j++;
    pregs›j~.name ="HEXLITERAL";
    pregs›j~.ptrn =ptrnHexL1;
    pregs›j~.preg =&pregHexL1;
    j++;
    pregs›j~.name ="HEXLITERAL";
    pregs›j~.ptrn =ptrnHexL2;
    pregs›j~.preg =&pregHexL2;
    j++;
    pregs›j~.name ="IDENTIFIER";
    pregs›j~.ptrn =ptrnIdent;
    pregs›j~.preg =&pregIdent;
    j++;
    pregs›j~.name ="LITERAL";
    pregs›j~.ptrn =ptrnLiter1;
    pregs›j~.preg =&pregLiter1;
    j++;
    pregs›j~.name ="LITERAL";
    pregs›j~.ptrn =ptrnLiter2;
    pregs›j~.preg =&pregLiter2;
    j++;
    pregs›j~.name ="DECIMAL";
    pregs›j~.ptrn =ptrnDecim;
    pregs›j~.preg =&pregDecim;
    j++;
    pregs›j~.name ="INTEGER";
    pregs›j~.ptrn =ptrnIntgr;
    pregs›j~.preg =&pregIntgr;
    j++;
    pregs›j~.name ="SYMBOL";
    pregs›j~.ptrn =ptrnSymbols;
    pregs›j~.preg =&pregSymbols;
    j++;
    pregs›j~.name="ENDLINE";
    pregs›j~.ptrn=ptrnEndLine;
    pregs›j~.preg=&pregEndLine;
    j++;
  */
    nb_regex_for_type = j;

  /*---------------------------------------------------------------*/
  /*-------------- ! Context Sensitive Lexer ! --------------------*/
  /*---------------------------------------------------------------*/
  /* If clause data_pic_chars => add PICCHARS as the first regex   */
  /*---------------------------------------------------------------*/
  /*                          => next is the pattern for space     */
  /*---------------------------------------------------------------*/

    if((strcmp(_context.clause,"data_pic_chars"))==0)È


       j = 0;

       pregs›j~.name ="PICCHARS";
       pregs›j~.ptrn =ptrnPicChars;
       pregs›j~.preg =&pregPicChars;
       j++;
       pregs›j~.name ="SYMBOL";
       pregs›j~.ptrn =ptrnSymbols;
       pregs›j~.preg =&pregSymbols;
       j++;
       pregs›j~.name ="SPACE";
       pregs›j~.ptrn =ptrnSpace;
       pregs›j~.preg =&pregSpace;
       j++;
       pregs›j~.name ="KEYWORD";
       pregs›j~.ptrn =ptrnKeywoAll;
       pregs›j~.preg =&pregKeywoAll;
       j++;
       pregs›j~.name ="LITERAL";
       pregs›j~.ptrn =ptrnLiterQuot;
       pregs›j~.preg =&pregLiterQuot;
       j++;
       pregs›j~.name ="LITERAL";
       pregs›j~.ptrn =ptrnLiterNum;
       pregs›j~.preg =&pregLiterNum;
       j++;
       pregs›j~.name ="IDENTIFIER";
       pregs›j~.ptrn =ptrnIdent;
       pregs›j~.preg =&pregIdent;
       j++;
       pregs›j~.name ="ENDLINE";
       pregs›j~.ptrn =ptrnEndLine;
       pregs›j~.preg =&pregEndLine;
       j++;
/*
       pregs›j~.name ="PICCHARS";
       pregs›j~.ptrn =ptrnPicChars;
       pregs›j~.preg =&pregPicChars;
       j++;
*/   /*pregs›j~.name ="SYMBOL";
       pregs›j~.ptrn =ptrnPerio;
       pregs›j~.preg =&pregPerio;
       j++;*/
/*     pregs›j~.name ="SYMBOL";
       pregs›j~.ptrn =ptrnSymbols;
       pregs›j~.preg =&pregSymbols;
       j++;
       pregs›j~.name="SPACE";
       pregs›j~.ptrn=ptrnSpace;
       pregs›j~.preg=&pregSpace;
       j++;
       pregs›j~.name ="KEYWORD";
       pregs›j~.ptrn =ptrnKeywoAll;
       pregs›j~.preg =&pregKeywoAll;
       j++;
       pregs›j~.name ="SPECIAL REGISTER";
       pregs›j~.ptrn =ptrnSpclReg;
       pregs›j~.preg =&pregSpclReg;
       j++;
       pregs›j~.name ="FIGURATIVE CONST";
       pregs›j~.ptrn =ptrnFgrtvConst;
       pregs›j~.preg =&pregFgrtvConst;
       j++;
       pregs›j~.name ="HEXLITERAL";
       pregs›j~.ptrn =ptrnHexL1;
       pregs›j~.preg =&pregHexL1;
       j++;
       pregs›j~.name ="HEXLITERAL";
       pregs›j~.ptrn =ptrnHexL2;
       pregs›j~.preg =&pregHexL2;
       j++;
       pregs›j~.name ="IDENTIFIER";
       pregs›j~.ptrn =ptrnIdent;
       pregs›j~.preg =&pregIdent;
       j++;
       pregs›j~.name ="LITERAL";
       pregs›j~.ptrn =ptrnLiter1;
       pregs›j~.preg =&pregLiter1;
       j++;
       pregs›j~.name ="LITERAL";
       pregs›j~.ptrn =ptrnLiter2;
       pregs›j~.preg =&pregLiter2;
       j++;
       pregs›j~.name ="DECIMAL";
       pregs›j~.ptrn =ptrnDecim;
       pregs›j~.preg =&pregDecim;
       j++;
       pregs›j~.name ="INTEGER";
       pregs›j~.ptrn =ptrnIntgr;
       pregs›j~.preg =&pregIntgr;
       j++;
       pregs›j~.name="ENDLINE";
       pregs›j~.ptrn=ptrnEndLine;
       pregs›j~.preg=&pregEndLine;
       j++;
 */    nb_regex_for_type = j;
    Ë

  /* Additional Regex for token attributes   */
  regex_npp   pregs_attr ›NB_REGEX_MAX~;

  int nb_regex_for_attr;
  j =0;

  pregs_attr›j~.name ="SPECIAL REGISTER";
  pregs_attr›j~.ptrn =ptrnSpclReg;
  pregs_attr›j~.preg =&pregSpclReg;
  j++;
  pregs_attr›j~.name ="FIGURATIVE CONST";
  pregs_attr›j~.ptrn =ptrnFgrtvConst;
  pregs_attr›j~.preg =&pregFgrtvConst;
  j++;
  pregs_attr›j~.name ="NUMERIC";
  pregs_attr›j~.ptrn =ptrnNumeric;
  pregs_attr›j~.preg =&pregNumeric;
  j++;
  pregs_attr›j~.name ="QUOTED";
  pregs_attr›j~.ptrn =ptrnQuoted;
  pregs_attr›j~.preg =&pregQuoted;
  j++;
  pregs_attr›j~.name ="SINGLE QUOTE";
  pregs_attr›j~.ptrn =ptrnSQuoted;
  pregs_attr›j~.preg =&pregSQuoted;
  j++;
  pregs_attr›j~.name ="DOUBLE QUOTED";
  pregs_attr›j~.ptrn =ptrnDQuoted;
  pregs_attr›j~.preg =&pregDQuoted;
  j++;
  pregs_attr›j~.name ="HEX";
  pregs_attr›j~.ptrn =ptrnHex;
  pregs_attr›j~.preg =&pregHex;
  j++;
  pregs_attr›j~.name ="ALPHANUMERIC";
  pregs_attr›j~.ptrn =ptrnAlphanum;
  pregs_attr›j~.preg =&pregAlphanum;
  j++;
  pregs_attr›j~.name ="INTEGER";
  pregs_attr›j~.ptrn =ptrnIntgr;
  pregs_attr›j~.preg =&pregIntgr;
  j++;
  pregs_attr›j~.name ="DECIMAL";
  pregs_attr›j~.ptrn =ptrnDecim;
  pregs_attr›j~.preg =&pregDecim;
  j++;
  pregs_attr›j~.name ="UNSIGNED";
  pregs_attr›j~.ptrn =ptrnUnsigned;
  pregs_attr›j~.preg =&pregUnsigned;
  j++;
  pregs_attr›j~.name ="POSITIVE";
  pregs_attr›j~.ptrn =ptrnPositive;
  pregs_attr›j~.preg =&pregPositive;
  j++;
  pregs_attr›j~.name ="NEGATIVE";
  pregs_attr›j~.ptrn =ptrnNegative;
  pregs_attr›j~.preg =&pregNegative;
  j++;
  pregs_attr›j~.name ="LEVEL NUMBER";
  pregs_attr›j~.ptrn =ptrnLvlNum;
  pregs_attr›j~.preg =&pregLvlnum;
  j++;
  pregs_attr›j~.name ="RELATIONAL OP";
  pregs_attr›j~.ptrn =ptrnRelOp;
  pregs_attr›j~.preg =&pregRelOp;
  j++;
  pregs_attr›j~.name ="ARITHMITIC OP";
  pregs_attr›j~.ptrn =ptrnAritOp;
  pregs_attr›j~.preg =&pregAritOp;
  j++;

  nb_regex_for_attr = j;

  /*
  regex_npp   reg_lvlnum;
  regex_npp   reg_lvl66;
  regex_npp   reg_lvl88;
  regex_npp   reg_uintgr;

  reg_lvlnum.name="LVLNUM";
  reg_lvlnum.ptrn=ptrnLvlnum;
  reg_lvlnum.preg=&pregLvlnum;

  reg_lvl66.name="LVL66";
  reg_lvl66.ptrn=ptrnLvl66;
  reg_lvl66.preg=&pregLvl66;

  reg_lvl88.name="LVL88";
  reg_lvl88.ptrn=ptrnLvl88;
  reg_lvl88.preg=&pregLvl88;

  reg_uintgr.name="UINTEGER";
  reg_uintgr.ptrn=ptrnUintgr;
  reg_uintgr.preg=&pregUintgr;

  if(ß(compil_regexp(reg_lvlnum))) return _ret;
  if(ß(compil_regexp(reg_lvl66))) return _ret;
  if(ß(compil_regexp(reg_lvl88))) return _ret;
  if(ß(compil_regexp(reg_uintgr))) return _ret;
  */

  /*---------------------------------------------------------------*/
  /*-------------- ! Compilation des Regex  ! ---------------------*/
  /*---------------------------------------------------------------*/


     /* _______________________________
      _(                               )_
     =_  COMPILE REGEX FOR TOKEN TYPE   _=
       (_______________________________)*/

    i=0;
    while ((i < nb_regex_for_type) && (compil_regexp(pregs›i~)))

    È
    /* printf("Compilation regex (%s) reussie Án",pregs›i~.name); */
       i++;
    Ë


    /* Sortie prÈmature : erreur compilation */
    if (i < nb_regex_for_type) exit(EXIT_FAILURE);


     /* ____________________________________
      _(                                    )_
     =_  COMPILE REGEX FOR TOKEN ATTRIBUTES  _=
       (____________________________________)*/


    i=0;
    while ((i < nb_regex_for_attr) && (compil_regexp(pregs_attr›i~)))

    È
    /* printf("Compilation regex (%s) reussie Án",
              pregs_attr›i~.name); */
       i++;
    Ë


    /* Sortie prÈmature : erreur compilation */
    if (i < nb_regex_for_attr) exit(EXIT_FAILURE);


     /* _____________________________
      _(                             )_
     =_  MATCH REGEX FOR TOKEN TYPE   _=
       (_____________________________)*/

    i =0;
    while ((i < nb_regex_for_type) &&
          ((rc =regexec(pregs›i~.preg, args, nmatch, pmatch, 0)) ß= 0))

    È
     /*affich_fail_match(rc,args,pregs›i~.name,pregs›i~.preg);*/
       i++;
    Ë

    /* match found */
    if (i < nb_regex_for_type) È

        /* Display matched sub-expression */
      /*affich_subexpr(pmatch,args);*/

        /* extraire token vers var tmp : str */
        sprintf(str,"%.*s",pmatch›2~.rm_eo - pmatch›2~.rm_so,
                  args+pmatch›2~.rm_so);

        /* reduire args */
        /*
        sprintf(args,"%.*s",pmatch›3~.rm_eo - pmatch›3~.rm_so,
                  args+pmatch›3~.rm_so); */

        reduction_len  = 65 - strlen(args);

        sprintf(args,"%.*s",((strlen(args))-(pmatch›2~.rm_eo))
                 ,args+(pmatch›2~.rm_eo));

        _ret.tkn_colnum = pmatch›2~.rm_so + 1 + reduction_len;
        _ret.tkn_len    = pmatch›2~.rm_eo - pmatch›2~.rm_so;

      /*printf("tokenizer     :strlen(args) (%d) reduction_len (%d)" Á
        " tkn_colnum (%d) pmatch›2~.rm_so (%d) tkn_len (%d) Án",
        strlen(args),reduction_len,_ret.tkn_colnum,pmatch›2~.rm_so,
        _ret.tkn_len);
      */
        /* concat str avec rets */
        strcat(rets_data,pregs›i~.name);
        strcat(rets_data,";;");
        strcat(rets_data,str);
        strcat(rets_data,";;");
        char* temp="Á0";
        sprintf(temp, "%d", _ret.tkn_colnum);
        strcat(rets_data,temp);
        strcat(rets_data,";;");

        _ret.tkn_type   = pregs›i~.name;
        _ret.tkn_val    = str;

        /*
        if ((rc =regexec(reg_lvlnum.preg,str,nmatch,pmatch,0)) == 0)È
            _ret.tkn_attr›0~ = "LVLNUM";
            printf ("LVLNUM found Án");
        Ë
        if ((rc =regexec(reg_lvl66.preg,str,nmatch,pmatch,0)) == 0)È
            _ret.tkn_attr›0~= "LVL66";
            printf ("LVL66  found Án");
        Ë
        if ((rc =regexec(reg_lvl88.preg,str,nmatch,pmatch,0)) == 0)È
            _ret.tkn_attr›0~= "LVL88";
            printf ("LVL88  found Án");
        Ë
        if ((rc =regexec(reg_uintgr.preg,str,nmatch,pmatch,0)) == 0)È
            _ret.tkn_attr›1~= "UINTEGER";
            printf ("UINTEGER  found Án");
        Ë */
    Ë

    /* no match found */
    else È

       strcpy(rets_data,"ERROR;;");
       _ret.tkn_type = "ERROR";
       _ret.tkn_val = "ERROR";

       printf("ERROR, args :%s",args);
    Ë

     /* ____________________________________
      _(                                    )_
     =_  COMPILE REGEX FOR TOKEN ATTRIBUTES  _=
       (____________________________________)*/

    i =0;
    j =0;
    _ret.tkn_attr_len =0;
    while ((i < nb_regex_for_attr) &&
           (rc=strcmp(_ret.tkn_val,"ERROR"))ß=0)
    È
       if((rc =regexec(pregs_attr›i~.preg,str,nmatch,pmatch,0)) == 0)
       È
          /* Display matched sub-expression */
        /*affich_subexpr(pmatch,str); */
          _ret.tkn_attr›j~=pregs_attr›i~.name;
          j++;
       Ë
       else
       È
        /*affich_fail_match(rc,args,pregs›i~.name,pregs›i~.preg);*/
       Ë

       i++;
    Ë
    _ret.tkn_attr_len=j;

    rets_len = strlen(rets_data);
    /*
    printf("Án");
    printf("*----------------------------------------------*Án");
    printf("*--------------  END LEXERCOB  ----------------*Án");
    printf("*----------------------------------------------*Án");
    printf("*   Rets length : %d Án", rets_len);
    printf("*   Rets data   :'%s'Án", rets_data);
    printf("*----------------------------------------------*Án");
    */
    printf("Án");
    printf("*----------------------------------------------*Án");
    printf("*--------------   TOKENIZER    ----------------*Án");
    printf("*----------------------------------------------*Án");
    printf("*   Token Value : %s Án", _ret.tkn_val);
    printf("*   Token Type  : %s Án", _ret.tkn_type);
    printf("*   Token Line  : %d Án", _ret.tkn_lnnum);
    printf("*   Token Coln  : %d Án", _ret.tkn_colnum);
    printf("*   Token Length: %d Án", _ret.tkn_len);
    printf("*   Token attrs : %d Án", _ret.tkn_attr_len);
    printf("*----------------------------------------------*Án");

    i =0;
    while (i < _ret.tkn_attr_len) È
       printf("*   Token Attr  : %s Án", _ret.tkn_attr›i~);
       i++;
    Ë
    printf("*----------------------------------------------*Án");

    /*
    regfree(&pregIdent);
    regfree(&pregPerio);
    regfree(&pregLiter1);
    regfree(&pregLiter2);
    regfree(&pregHexL1);
    regfree(&pregHexL2);
    regfree(&pregKeywoAll);
    regfree(&pregLBrack);
    regfree(&pregRBrack);
    regfree(&pregPlus);
    regfree(&pregMinus);
    regfree(&pregMultp);
    regfree(&pregDivid);
    regfree(&pregExpon);
    regfree(&pregEqual);
    regfree(&pregColon);
    regfree(&pregIntgr);
    regfree(&pregDecim);

    printf("tokenizer()   : ");
    printf("Token Value <%s> Token Type   <%s> Án",
            _ret.tkn_val,_ret.tkn_type);
    */
    /*
    printf("tokenizer()   : ");
    printf("args        : <%s>Án",args);
    printf("len args    : <%d>Án",strlen(args));
    */
    strcpy(ln_8_72,args);

    /*
    printf("tokenizer()   : ");
    printf("ln_8_72     : <%s>Án",ln_8_72);
    printf("len ln_8_72 : <%d>Án",strlen(ln_8_72));
    */
    return _ret;

Ë


int affich_subexpr(regmatch_t pmatch›~,char args›~)È

   int i =0;

   printf("Whole expression :<");
   printf("%s",args);
   printf(">Án");

   for (i=1;i<NB_MATCH_MAX;i++)È

      printf("ÁnSub-expression %d, a matched sub-string " Á
             "Á"%.*sÁ" found at position %d to %d.Án ",
      i, pmatch›i~.rm_eo - pmatch›i~.rm_so,
      args+pmatch›i~.rm_so,pmatch›i~.rm_so,
      pmatch›i~.rm_eo - 1);

   Ë
   printf("Án");

   return 1;
Ë

int affich_fail_match(int rc,char args›~,char* ptrn,regex_t* preg)È

   char buffer›100~;

   regerror(rc, preg, buffer, 100);

   printf("failed to matchÁn'%s'withÁn'%s',ÁnRC :%d, '%s'Án"
             ,args, ptrn, rc, buffer);

   return 1;
Ë

int compil_regexp(regex_npp _regex_npp)È

    int  rc =0;
    char buffer›100~;

    /* Compiler la REGEXP pour ptrn dans preg */

    if ((rc = regcomp(_regex_npp.preg, _regex_npp.ptrn,
         REG_ICASE!REG_EXTENDED)) ß= 0)
    È
       regerror(rc, _regex_npp.preg, buffer, 100);
       printf("regcomp(%s) fail RC (%d : '%s')Án",_regex_npp.name,
              rc, buffer);
       return 0;
    Ë
    /* printf("regcomp for (%s) succesful Án",_regex_npp.name);*/

    return 1;
Ë
£include <stdio.h>
£include <stdlib.h>
£include <stddef.h>

£include "asth"



/*---   SENTENCE   ---*/
ast*
make_sentence    (int nb_statement, struct ast* list_statement)È

  printf("sizeof(ast*) sentence (%zd)Án",sizeof(ast*));
  printf("sizeof(ast ) sentence (%zd)Án",sizeof(ast));

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.sentence.ast_name          = "SENTENCE";
  e->tag = SENTENCE;

  e->node.sentence.nb_statement = nb_statement;
  e->node.sentence.list_statement = NULL;

  /* if(nb_statement > 0 ) */
  e->node.sentence.list_statement = list_statement;

  e->next =NULL;

  printf("Án");
  printf("**********   SENTENCE   **********Án");
  printf("* SENTENCE AST BUILT SUCCESFULLY *Án");
  printf("**********************************Án");

  return e;

Ë

affich_sentence(ast* tree,scr_line* screen)È

   printf("printing sentence ... Án");

   ast* temp = NULL;

   printf("Drawing ast name  ... Án");
   draw_box(screen,tree->node.sentence.ast_name,"",1);
   printf("Drawing ast name  OK  Án");

   printf("Init iterator ...     Án");

   temp=tree->node.sentence.list_statement;

   printf("Iterating ...         Án");
   while(temp ß= NULL)È
      printf("temp (%d) Án",temp);
      printf("Printinf inner stmnt ...  Án");
      affich_statement(temp,screen);
      printf("Printinf inner stmnt OK   Án");
      temp = temp->next;
      printf("temp (%d) Án",temp);
   Ë
   printf("Iterating OK      Án");

Ë

affich_statement(ast* tree,scr_line* screen)È

   printf("Switch for statement ... Án");
   ast* temp = NULL;

   printf("Statement (%s) Án",tagValues›tree->tag~);
   assert(tree->tag == DISPLAY_STM);

   if      (tagValues›tree->tag~ == "MOVE_STM")

           affich_move_stm(tree,screen);

   else if (tagValues›tree->tag~ == "DISPLAY_STM")

           affich_display_stm(tree,screen);

   else if (tagValues›tree->tag~ == "INITIALIZE_STM")

           affich_initialize_stm(tree,screen);

   else È

           printf("Unknown Tag for statement (%s) Án",
                                tagValues›tree->tag~);
           exit(EXIT_FAILURE);
   Ë
Ë

/*---   MOVE   ---*/
ast*
make_move        (int bool_corresp, struct ast* operand_g,
                  int nb_operand_r, struct ast* list_operand_r)È

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.move_stm.ast_name          = "MOVE";
  e->tag = MOVE_STM;



  e->next =NULL;
  return e;

Ë

affich_move_stm(ast* tree,scr_line* screen)È


Ë
/*---   DISPLAY   ---*/
ast*
make_display (int bool_upon, int bool_no_adv, char* upon_operand,
                   int nb_operand, struct ast* list_operand)È

  printf("sizeof(ast*) display (%zd)Án",sizeof(ast*));
  printf("sizeof(ast ) display (%zd)Án",sizeof(ast));
  ast* e = (ast*) malloc(sizeof(ast));
  e->node.display_stm.ast_name          = "DISPLAY";
  e->tag = DISPLAY_STM;

  e->node.display_stm.bool_upon         = bool_upon;
  e->node.display_stm.bool_no_adv       = bool_no_adv;
  /*strcpy(e->node.display_stm.upon_operand,upon_operand);*/
  e->node.display_stm.upon_operand = upon_operand;
  e->node.display_stm.nb_operand        = nb_operand;
  e->node.display_stm.list_operand   = NULL;

  if(nb_operand > 0 )
     e->node.display_stm.list_operand   = list_operand;

  e->next =NULL;

  printf("Án");
  printf("**********   DISPLAY    **********Án");
  printf("* DISPLAY  AST BUILT SUCCESFULLY *Án");
  printf("**********************************Án");

  return e;

Ë

affich_display_stm(ast* tree,scr_line* screen)È

   ast* temp = NULL;

   draw_box(screen,tree->node.display_stm.ast_name,"",1);

   temp=tree->node.display_stm.list_operand;

   while(temp ß= NULL)È
      affich_operand(temp,screen);
      temp=temp->next;
   Ë

Ë

ast*
make_initialize  (int bool_repl, int nb_operand,
                  struct ast* list_operand)È

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.initialize_stm.ast_name          = "INITIALIZE";
  e->tag = INITIALIZE_STM;



  e->next =NULL;
  return e;


Ë

affich_initialize_stm(ast* tree,scr_line* screen)È


Ë
/*---   OPERAND   ---*/
ast*
make_operand (int bool_literal, int bool_identifier,
                  struct ast* operand)È

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.operand.ast_name          = "OPERAND";
  e->tag = OPERAND;


  e->next =NULL;
  printf("Án");
  printf("**********   OPERAND    **********Án");
  printf("* OPERAND  AST BUILT SUCCESFULLY *Án");
  printf("**********************************Án");

  return e;

Ë

affich_operand(ast* tree,scr_line* screen)È

   ast* temp = NULL;

   if      (tagValues›tree->tag~ == "LITERAL")

           affich_literal(tree,screen);

   else if (tagValues›tree->tag~ == "IDENTIFIER")

           affich_identifier(tree,screen);

   else exit(EXIT_FAILURE);

Ë

/*---   LITERAL   ---*/
ast*
make_literal     (char* value,
                  int bool_all, int bool_numeric,
                  int bool_alphanumeric,
                  int bool_hexadecimal, int bool_positive,
                  int bool_negative, int bool_unsigned,
                  int bool_singl_q, int bool_doubl_q,
                  int bool_intgr,   int bool_decim,
                  int bool_figurative,
                  int char_length)È

  printf("sizeof(ast*) literal (%zd)Án",sizeof(ast*));
  printf("sizeof(ast ) literal (%zd)Án",sizeof(ast));
  ast* e = (ast*) malloc(sizeof(ast));
  e->node.literal.ast_name          = "LITERAL";
  e->tag = LITERAL;

  e->node.literal.bool_all          = bool_all;
  e->node.literal.bool_numeric      = bool_numeric;
  e->node.literal.bool_alphanumeric = bool_alphanumeric;
  e->node.literal.bool_hexadecimal  = bool_hexadecimal;
  e->node.literal.bool_positive     = bool_positive;
  e->node.literal.bool_negative     = bool_negative;
  e->node.literal.bool_unsigned     = bool_unsigned;
  e->node.literal.bool_singl_q      = bool_singl_q;
  e->node.literal.bool_doubl_q      = bool_doubl_q;
  e->node.literal.bool_intgr        = bool_intgr;
  e->node.literal.bool_decim        = bool_decim;
  e->node.literal.bool_figurative   = bool_figurative;
  e->node.literal.char_length       = char_length;

  /*strcpy(e->node.literal.value,value);*/
  e->node.literal.value=value;

  e->next =NULL;

  printf("Án");
  printf("**********   LITERAL    **********Án");
  printf("* LITERAL  AST BUILT SUCCESFULLY *Án");
  printf("**********************************Án");

  return e;

Ë

affich_literal(ast* tree,scr_line* screen)È

   draw_box(screen,tree->node.literal.ast_name,
                   tree->node.literal.value,1);

Ë

ast*
make_identifier  (int bool_length, int bool_address,
                  char* special_reg_value,
                  struct ast* name, struct ast* qualif,
                  struct ast* subscript, struct ast* refmod)È

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.identifier.ast_name          = "IDENTIFIER";
  e->tag = IDENTIFIER;

  e->node.identifier.bool_length       = bool_length;
  e->node.identifier.bool_address      = bool_address;
/*strcpy(e->node.identifier.special_reg_value,special_reg_value);*/
  e->node.identifier.special_reg_value=special_reg_value;
  e->node.identifier.name              = name;
  e->node.identifier.qualif            = qualif;
  e->node.identifier.subscript         = subscript;
  e->node.identifier.refmod            = refmod;

  e->next =NULL;
  printf("Án");
  printf("**********   IDENTIFIER   **********Án");
  printf("* IDENTIFIER AST BUILT SUCCESFULLY *Án");
  printf("************************************Án");

  return e;

Ë

affich_identifier(ast* tree,scr_line* screen)È

   ast* name = tree->node.identifier.name;
   draw_box(screen,tree->node.identifier.ast_name,
                   name->node.ident_name.value,1);

   if(tree->node.identifier.qualif ß= NULL)
      affich_ident_qualif(tree->node.identifier.qualif,screen);

   if(tree->node.identifier.refmod ß= NULL)
      affich_ident_refmod(tree->node.identifier.refmod,screen);

   if(tree->node.identifier.subscript ß= NULL)
      affich_ident_subscript(tree->node.identifier.subscript,screen);

Ë


ast*
make_ident_name_qualif
                 (struct ast* name, struct ast* qualif)È

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.ident_name_qualif.ast_name          = "IDENT_NAME_QUALIF";
  e->tag = IDENT_NAME_QUALIF;

  e->node.ident_name_qualif.name       = name;
  e->node.ident_name_qualif.qualif     = qualif;


  e->next =NULL;
  printf("Án");
  printf("***********  ID NAME QUALIF  ***********Án");
  printf("* ID NAME QUALIF AST BUILT SUCCESFULLY *Án");
  printf("****************************************Án");

  return e;

Ë

affich_ident_name_qualif(ast* tree,scr_line* screen)È


Ë

ast*
make_ident_name  (int length, char* value)È

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.ident_name.ast_name          = "IDENT_NAME";
  e->tag = IDENT_NAME;

  e->node.ident_name.length            = length;
  e->node.ident_name.value             = value;

  e->next =NULL;
  printf("Án");
  printf("***********  ID NAME  ***********Án");
  printf("* ID NAME AST BUILT SUCCESFULLY *Án");
  printf("*********************************Án");
  return e;


Ë

affich_ident_name(ast* tree,scr_line* screen)È

   draw_box(screen,tree->node.ident_name.ast_name,
                   tree->node.ident_name.value,1);


Ë

ast*
make_ident_qualif(struct ast* list_qualif)È

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.ident_qualif.ast_name          = "IDENT_QUALIF";
  e->tag = IDENT_QUALIF;

  e->node.ident_qualif.list_qualif     = list_qualif;


  e->next =NULL;
  printf("Án");
  printf("***********  ID QUALIF  ***********Án");
  printf("* ID QUALIF AST BUILT SUCCESFULLY *Án");
  printf("***********************************Án");
  return e;

Ë

affich_ident_qualif(ast* tree,scr_line* screen)È

   ast* temp = NULL;

   temp=tree->node.ident_qualif.list_qualif;

   while(temp ß= NULL)È
      affich_ident_name(temp,screen);
      temp=temp->next;
   Ë


Ë


ast*
make_ident_subscript
                 (struct ast* list_subscript)È

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.ident_subscript.ast_name          = "IDENT_SUBSCRIPT";
  e->tag = IDENT_SUBSCRIPT;

  printf("Án");
  printf("***********  ID SUBSCR  ***********Án");
  printf("* ID SUBSCR AST BUILT SUCCESFULLY *Án");
  printf("***********************************Án");


  e->next =NULL;
  return e;


Ë

affich_ident_subscript(ast* tree,scr_line* screen)È

   draw_box(screen,tree->node.ident_subscript.ast_name,
                   "subscript value",1);


Ë


ast*
make_ident_refmod(struct ast* charleft, struct ast* length)È

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.ident_refmod.ast_name          = "IDENT_REFMOD";
  e->tag = IDENT_REFMOD;


  printf("Án");
  printf("***********  ID REFMOD  ***********Án");
  printf("* ID REFMOD AST BUILT SUCCESFULLY *Án");
  printf("***********************************Án");


  e->next =NULL;
  return e;


Ë

affich_ident_refmod(ast* tree,scr_line* screen)È

   draw_box(screen,tree->node.ident_refmod.ast_name,
                   "refmod value",1);


Ë

ast*
make_arith_exp   (char* oper, struct ast* left, struct ast* right)È

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.arith_exp.ast_name          = "ARITH_EXP";
  e->tag = ARITH_EXP;


  e->next =NULL;
  return e;



Ë

affich_arith_exp(ast* tree,scr_line* screen)È


Ë

affich_special_reg(ast* tree,scr_line* screen)È


Ë

affich_binary_op(ast* tree,scr_line* screen)È


Ë

affich_unary_op(ast* tree,scr_line* screen)È


Ë

affich_declaration(ast* tree,scr_line* screen)È


Ë

                     /***                 ***/
ast*
append_list (struct ast* list, struct ast* toadd)È

  printf("Án");
  printf("append_list(%s) start ...Án",tagValues›list->tag~);
  ast* head;



  if(list == NULL)È

     printf("list==NULL ... return to_add Án");

     printf("toadd (%d)Án",toadd);
     printf("toadd->next (%d)Án",toadd->next);

     return toadd;
  Ë

  head = list;

  while(list ß= NULL)È
     printf("parcours de la liste ...     Án");
     list = list->next;
  Ë

  list=toadd;
  list->next=NULL;

  printf("append succesful             Án");
  printf("Án");

  return head;

Ë

/*              Affichage des AST                       */

affich_node (ast* tree,scr_line* screen)È

   if      (tree->tag == SENTENCE)

           affich_sentence(tree,screen);

   else if (tree->tag == DECLARATION)

           affich_declaration(tree,screen);

   else if (tree->tag == STATEMENT)

           affich_statement(tree,screen);

   else if (tree->tag == MOVE_STM)

           affich_move_stm(tree,screen);

   else if (tree->tag == DISPLAY_STM)

           affich_display_stm(tree,screen);

   else if (tree->tag == INITIALIZE_STM)

           affich_initialize_stm(tree,screen);

   else if (tree->tag == OPERAND)

           affich_operand(tree,screen);

   else if (tree->tag == LITERAL)

           affich_literal(tree,screen);

   else if (tree->tag == IDENTIFIER)

           affich_identifier(tree,screen);

   else if (tree->tag == IDENT_NAME)

           affich_ident_name(tree,screen);

   else if (tree->tag == IDENT_NAME_QUALIF)

           affich_ident_name_qualif(tree,screen);

   else if (tree->tag == IDENT_QUALIF)

           affich_ident_qualif(tree,screen);

   else if (tree->tag == IDENT_SUBSCRIPT)

           affich_ident_subscript(tree,screen);

   else if (tree->tag == IDENT_REFMOD)

           affich_ident_refmod(tree,screen);

   else if (tree->tag == SPECIAL_REG)

           affich_special_reg(tree,screen);

   else if (tree->tag == ARITH_EXP)

           affich_arith_exp(tree,screen);

   else if (tree->tag == BINARY_OP)

           affich_binary_op(tree,screen);

   else if (tree->tag == UNARY_OP)

           affich_unary_op(tree,screen);

   else    exit(EXIT_FAILURE);

Ë

/*              Free AST               */

free_node (ast* tree)È

   printf("free_node (%s) (%d) Án", tagValues›tree->tag~,tree->tag);
   printf("Looking for next ...Án");

   while (tree->next ß= NULL)È
      printf("Next found.Án");

      free_node(tree->next);

   Ë
   printf("Looking for next OK Án");

   if      (tree->tag == SENTENCE)

           free_sentence(tree);

   else if (tree->tag == DECLARATION)

           free_declaration(tree);

   else if (tree->tag == STATEMENT)

           free_statement(tree);

   else if (tree->tag == MOVE_STM)

           free_move_stm(tree);

   else if (tree->tag == DISPLAY_STM)

           free_display_stm(tree);

   else if (tree->tag == INITIALIZE_STM)

           free_initialize_stm(tree);

   else if (tree->tag == OPERAND)

           free_operand(tree);

   else if (tree->tag == LITERAL)

           free_literal(tree);

   else if (tree->tag == IDENTIFIER)

           free_identifier(tree);

   else if (tree->tag == IDENT_NAME)

           free_ident_name(tree);

   else if (tree->tag == IDENT_NAME_QUALIF)

           free_ident_name_qualif(tree);

   else if (tree->tag == IDENT_QUALIF)

           free_ident_qualif(tree);

   else if (tree->tag == IDENT_SUBSCRIPT)

           free_ident_subscript(tree);

   else if (tree->tag == IDENT_REFMOD)

           free_ident_refmod(tree);

   else if (tree->tag == SPECIAL_REG)

           free_special_reg(tree);

   else if (tree->tag == ARITH_EXP)

           free_arith_exp(tree);

   else if (tree->tag == BINARY_OP)

           free_binary_op(tree);

   else if (tree->tag == UNARY_OP)

           free_unary_op(tree);

   else È
           printf("Unknown Tag (%s) Án", tagValues›tree->tag~);
           exit(EXIT_FAILURE);
   Ë

Ë

free_sentence(ast* tree)È

   printf("Free_sentence ...Án");
   free_node(tree->node.sentence.list_statement);

   free(tree);
   printf("Free_sentence OK Án");

Ë

free_declaration(ast* tree)È

   printf("Free_declaration ...Án");
   free(tree);
   printf("Free_declaration OKÁn");

Ë

free_statement(ast* tree)È

   printf("Free_statement ...Án");
   free(tree);
   printf("Free_statement OKÁn");

Ë

free_move_stm(ast* tree)È

   printf("Free_move_stm ...Án");
   free(tree);
   printf("Free_move_stm OK Án");

Ë

free_display_stm(ast* tree)È

   printf("Free_display_stm ...Án");
   free_node(tree->node.display_stm.list_operand);

   free(tree);
   printf("Free_display_stm OK Án");

Ë

free_initialize_stm(ast* tree)È

   printf("Free_initialize_stm ...Án");
   free(tree);
   printf("Free_initialize_stm OK Án");

Ë

free_operand(ast* tree)È

   printf("Free_operand ...Án");
   free(tree);
   printf("Free_operand OK Án");

Ë

free_literal(ast* tree)È

   printf("Free_literal ...Án");
   printf("tree (%s)(%d)Án",tagValues›tree->tag~,tree);
   printf("value (%s)Án",tree->node.literal.value);
   printf("tree (%s) address(%d) char_len(%d)"Á
           "  single quote (%d) alphanumeric (%d)"
                       ,tree->node.literal.value
                       ,tree
                       ,tree->node.literal.char_length
                       ,tree->node.literal.bool_singl_q
                       ,tree->node.literal.bool_alphanumeric);
   free(tree);
   printf("Free_literal OKÁn");

Ë

free_identifier(ast* tree)È

   printf("Free_identifier ...Án");
   free_node(tree->node.identifier.name);
   free_node(tree->node.identifier.qualif);
   free_node(tree->node.identifier.subscript);
   free_node(tree->node.identifier.refmod);

   free(tree);
   printf("Free_identifier OKÁn");

Ë

free_ident_name(ast* tree)È

   printf("Free_ident_name ...Án");
   free(tree);
   printf("Free_ident_name OK Án");

Ë

free_ident_name_qualif(ast* tree)È

   printf("Free_ident_name_qualif ...Án");
   free_node(tree->node.ident_name_qualif.name);
   free_node(tree->node.ident_name_qualif.qualif);

   free(tree);
   printf("Free_ident_name_qualif OK Án");

Ë

free_ident_qualif(ast* tree)È

   printf("Free_ident_qualif ...Án");
   free_node(tree->node.ident_qualif.list_qualif);

   free(tree); /* ?? */
   printf("Free_ident_qualif OK Án");

Ë

free_ident_refmod(ast* tree)È

   printf("Free_ident_refmod ...Án");
   free_node(tree->node.ident_refmod.charleft);
   free_node(tree->node.ident_refmod.length);

   free(tree);
   printf("Free_ident_refmod OK Án");

Ë

free_ident_subscript(ast* tree)È

   printf("Free_ident_subscript ...Án");
   free_node(tree->node.ident_subscript.list_subscript);

   free(tree);
   printf("Free_ident_subscript OK Án");

Ë

free_special_reg(ast* tree)È

   printf("Free_special_reg ...Án");
   free(tree);
   printf("Free_special_reg OK Án");

Ë

free_arith_exp(ast* tree)È

   printf("Free_arith_exp   ...Án");
   free_node(tree->node.arith_exp.left);
   free_node(tree->node.arith_exp.right);

   free(tree);
   printf("Free_arith_exp   OK Án");

Ë

free_unary_op(ast* tree)È

   printf("Free_unary_op    ...Án");
   free_node(tree->node.unary_op.uexp);

   free(tree);
   printf("Free_unary_op    OK Án");

Ë

free_binary_op(ast* tree)È

   printf("Free_binary_op    ...Án");
   free(tree);
   printf("Free_binary_op    OK Án");

Ë

£include <stdio.h>
£include <stdlib.h>
£include <string.h>

£include "helperh"

scr_line*
init_screen()È

   scr_line* scr=(scr_line*) malloc(sizeof(scr_line));
   scr->lvl       =-1;
   scr->value›0~  ='Á0';
   scr->border    =0;
   scr->next      =NULL;

   /* printf("init_screen() succesfully.Án"); */
   return scr;

Ë

scr_line*
draw_box(scr_line* screen, char* value_1, char* value_2, int lvl)È

   /* printf("draw_box() start ... Án"); */


   /* level = 0 => sister */
   /* level = 1 => child  */
   /* level < 0 => parent */

   scr_line* last_line=NULL;
   scr_line* temp     =NULL;
   scr_line* ret      =NULL;

   int shift          =0;
   int length         =0;

   ret = screen;


   if(lvl > 1) È

      printf("Saut de plusieurs level non permis : %dÁn",lvl);
      exit(EXIT_FAILURE);
   Ë

   /* get last line of screen */
   last_line =get_last_line(screen);

   if((lvl < 0) && ((last_line->lvl + lvl) < 0)) È

      printf("Parent excessive : last lvl (%d) lvl (%d)Án",
                                 last_line->lvl,lvl);
      exit(EXIT_FAILURE);
   Ë

   /* calculate shift                          */
   shift = (last_line->lvl + lvl) * 5;
   /* get max length of values                 */
   length= max_str_len(value_1,value_2);
   /*
   printf("draw_box():last_line->lvl  (%d) Án",last_line->lvl);
   printf("draw_box():box to draw lvl (%d) Án",lvl);
   printf("draw_box():shift           (%d) Án",shift);
   printf("draw_box():max_str_len     (%d) Án",length);
   */

   /* draw first border                        */
   temp  = draw_border(length,shift);
   /* append to screen                         */
   ret   = scr_append(ret   ,temp);

   /* draw value 1                             */
   temp  = draw_value (length,shift,value_1);
   /* append to screen                         */
   ret   = scr_append(ret   ,temp);

   /* draw value 2                             */
   temp  = draw_value (length,shift,value_2);
   /* append to screen                         */
   ret   = scr_append(ret   ,temp);

   /* draw last  border                        */
   temp  = draw_border(length,shift);
   /* append to screen                         */
   ret   = scr_append(ret   ,temp);

   /* printf("draw_box() succesfully.  Án"); */

   return ret   ;

Ë

scr_line*
get_last_line(scr_line* screen) È

   scr_line* temp=NULL;
   scr_line* ret =NULL;

   int i;

   temp = screen;
   ret  = temp;

   /* printf ("get_last_line() start.Án"); */

   for(i=0;temp;i++)È

   /* printf ("get_last_line() screen-%d : (%d):%sÁn",
                               i,temp,temp->value); */
      ret=temp;
      temp=temp->next;
   Ë

   /* printf("get_last_line(): last line is the (%d th) next.Án",i);
   */
   return ret;

Ë

scr_line*
scr_append(scr_line* screen,scr_line* to_append) È

   scr_line* ret =NULL;

   ret =get_last_line(screen);
   ret ->next = to_append;

   /* printf("scr_append() : succesfully       .Án"); */
   return screen;

Ë

int
max_str_len(char* val_a, char* val_b) È

   int a,b;
   a= strlen(val_a);
   b= strlen(val_b);
   /* printf("max_str_len(): a (%d) b (%d).Án",a,b); */

   if(a>b)
     return a;
   else
     return b;
Ë

scr_line*
draw_border(int length, int shift) È

   scr_line* ret=(scr_line*) malloc(sizeof(scr_line));

   int lvl;
   int indent =4;
   char  temp›1024~;

   temp›0~='Á0';

   sprintf(temp,"%*s"  "%.*s"  "Á0"
           ,shift,""                     /* build shift  */
           ,length+indent, dummy_border  /* build asterisk */
           );


   /*
   strcat(buffer,temp);
   printf("temp_len = (%d)Án",temp_len);
   printf("draw_border(shift): temp=(%.*s)Án",temp_len,buffer);


   temp=h_realloc(temp,temp_len+length+indent);
   sprintf(temp+temp_len,"%.*s", length+indent, dummy_border);
   temp_len+=(length+indent);

   sprintf(temp,"%*s",length+indent, dummy_border);
   strcat(buffer,temp);
   printf("temp_len = (%d)Án",temp_len);
   printf("draw_border(***)  : temp=(%.*s)Án",temp_len,buffer);

   temp=h_realloc(temp,temp_len+1);
   sprintf(temp+temp_len,"%c", 'Á0');
   temp_len+=1;
   printf("temp_len = (%d)Án",temp_len);
   printf("draw_border(ÁÁ0)   : temp=(%.*s)Án",temp_len,temp);
   */

   strcpy(ret->value,temp);
   /* printf("draw_border()    : value=(%s)Án",ret->value); */

   /* compute level */
   lvl = shift/5;
   ret->lvl    =lvl;
   ret->border =1;
   ret->next   =NULL;

   return ret;
Ë


scr_line*
draw_value (int length, int shift,char* value) È

   scr_line* ret=(scr_line*) malloc(sizeof(scr_line));

   int   lvl;
   int   indent =4;
   char  temp›1024~;

   temp›0~='Á0';

   sprintf(temp,"%*s"  "%.*s"  "%c"  "%s"  "%*s"  "%c"  "%.*s"  "Á0"
           ,shift,""                     /* build shift      */
           ,1 , dummy_border             /* build asterisk 1 */
           ,' '                          /* indent 1         */
           ,value                        /* build value      */
           ,length-strlen(value),""      /* space pad to max */
           ,' '                          /* indent 2         */
           ,1 , dummy_border             /* build asterisk 2 */
           );


   /*
   temp=h_realloc(temp,temp_len+shift);
   sprintf(temp+temp_len,"%*s", shift, " ");
   temp_len+=shift;

   printf("temp_len = (%d)Án",temp_len);
   printf("draw_value (shift): temp=(%.*s)Án",temp_len,temp);

   temp=h_realloc(temp,temp_len+1);
   sprintf(temp+temp_len,"%.*s", 1,dummy_border);
   temp_len+=1;


   printf("temp_len = (%d)Án",temp_len);
   printf("draw_value (*)    : temp=(%.*s)Án",temp_len,temp);

   temp=h_realloc(temp,temp_len+1);
   sprintf(temp+temp_len,"%c", ' ');
   temp_len+=1;

   printf("temp_len = (%d)Án",temp_len);
   printf("draw_value ( )    : temp=(%.*s)Án",temp_len,temp);

   temp=h_realloc(temp,temp_len+strlen(value));
   strcpy(temp+temp_len,value);
   temp_len+=strlen(value);

   printf("temp_len = (%d)Án",temp_len);
   printf("draw_value (value): temp=(%.*s)Án",temp_len,temp);

   if(strlen(value)<length)È
      int diff=0;
      diff = length-strlen(value);
      printf("padding difference between values length (%d)Án",diff);

      temp=h_realloc(temp,temp_len+diff);
      sprintf(temp+temp_len,"%*s", diff , " ");
      temp_len+=diff;

      printf("temp_len = (%d)Án",temp_len);
      printf("draw_value (padd):temp=(%.*s)Án",temp_len,temp);

   Ë

   temp=h_realloc(temp,temp_len+1);
   sprintf(temp+temp_len,"%c", ' ');
   temp_len+=1;

   printf("temp_len = (%d)Án",temp_len);
   printf("draw_value ( ): temp=(%.*s)Án",temp_len,temp);

   temp=h_realloc(temp,temp_len+1);
   sprintf(temp+temp_len,"%.*s", 1,dummy_border);
   temp_len+=1;


   printf("temp_len = (%d)Án",temp_len);
   printf("draw_value (*): temp=(%.*s)Án",temp_len,temp);

   temp=h_realloc(temp,temp_len+1);
   sprintf(temp+temp_len,"%c", 'Á0');
   temp_len+=1;

   printf("temp_len = (%d)Án",temp_len);
   printf("draw_value (Á0): temp=(%.*s)Án",temp_len,temp);
   */

   strcpy(ret->value,temp);
   /* printf("draw_border() : value=(%s)Án",ret->value); */

   /* compute level */
   lvl         =shift/5;
   ret->lvl    =lvl;
   ret->border =0;
   ret->next   =NULL;

   return ret;
Ë

scr_line*
draw_blank ()È
   /* inutile, faire un double printf("Án") suffit */
   scr_line* ret=(scr_line*) malloc(sizeof(scr_line));

   ret->lvl          = 0;
   sprintf(ret->value,"%0*s", 1024 , " ");
   ret->value›1023~  ='Á0';
   ret->border       =0;
   ret->next         =NULL;

   return ret;

Ë

int
print_boxes(scr_line* scr)È

   printf("printing screen boxes ... Án");

   int x   =1;
   int y   =1;
   int i;

   /*printf(" X    <%d>  Y    <%d> Án",x,y);
   */
   scr_line* temp =scr;

   /* skip first node */
   for(i=1;temp=temp->next;i++)È

    printf("%.*sÁn",79,temp->value);
   /* if (ß(i%4))
       printf("Án");
   */
   Ë

   return 0;

Ë

char*
h_realloc(char* temp,int size)È

   printf("ÁnÁn");
   printf("h_realloc start. size (%d) Án",size);
   printf("h_realloc start. temp (%d) Án",temp);

   char* ret;

   printf("ret before (%d)Án",ret);
   ret=(char*) realloc(temp,(size) * sizeof(char));

   printf("ret after  (%d)Án",ret);
   printf("Án");

   if((ret==NULL) && (size>0)) È
     printf("Realloc Failed ! Án");
     exit(EXIT_FAILURE);
   Ë
   return ret;

Ë

