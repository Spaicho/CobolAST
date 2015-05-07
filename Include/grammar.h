#ifndef GRAMMAR_H_INCLUDED
#define GRAMMAR_H_INCLUDED

#pragma map(dsply_upon_oprnds,    "dsupops")
#pragma map(dsply_upon_oprnd,     "dsupop")
#pragma map(intlz_rplc_oprnds,    "inrpops")
#pragma map(intlz_rplc_oprnd ,    "inrpop")
#pragma map(refmodif_length,      "rfmol")
#pragma map(subscripts,           "subscs")
#pragma map(id_qualif_oprnd,      "idquop")
#pragma map(arith_expr2,          "arex2")
#pragma map(arith_expr_oprnd,     "arexopd")
#pragma map(arith_expr_oprtn,     "arexopt")
#pragma map(id_subs_refm,         "idsbrf")
#pragma map(id_subs_refm_rest,    "idsbrfr")
#pragma map(id_subs_rest,         "idsbrst")

#pragma map(data_field,           "dtfield")
#pragma map(data_fields,          "dtfilds")
#pragma map(data_index_key_cls,   "dtinkcs")
#pragma map(data_index_by_cl,     "dtinbc")
#pragma map(data_index_key_cl,    "dtinkc")
#pragma map(data_pic_cl,          "dtpcc")
#pragma map(data_pic_str,         "dtpcs")
#pragma map(data_pic_size_local,  "dtpcsl")
#pragma map(data_pic_chars,       "dtpcchs")


#pragma map(get_token_type,       "gttktp")
#pragma map(get_token_val,        "gttkval")
#pragma map(get_token_len,        "gttklen")

#include "ast.h"
#include "Lexer.h"

#define MAX_STR_ARR  20
/* Declaration pour les fonctions et varaibles de permutations */

/* Typedef pour function to Pointer */
typedef ast* (*AstFunc)(void);

/* Typedef pour array of string with length */
typedef struct str_arr{
   int    len;
   char*  arr [MAX_STR_ARR];
} str_arr;

typedef struct fp_t{
   AstFunc fp;
   str_arr cond_1;
   str_arr cond_2;
   int    id;
   tag_t  tag;
} fp_t;

/* Typedef pour array of fp_t with length */
typedef struct fp_t_nod{
   fp_t              val;
   struct fp_t_nod* next;
} fp_t_nod;

fp_t_nod* alim_clauses();
int tkn_in_array (str_arr);
fp_t_nod* delete_clauses(fp_t_nod*,fp_t_nod*);

/*  End declaration pour permutation */

token lookahead ={0,0,0,"",""};

/* Grammar functions return */
typedef struct ast_ret {
          struct ast*  _ast;             /* AST     */
          int          _ret;             /* return  */
} ast_ret;


/* _context Context   */
typedef struct context{
          char*  division;             /* Division                   */
          char*  section;              /* Section                    */
          char*  sentence;             /* Sentence                   */
          char*  clause;               /* Clause                     */
          char*  keyword;              /* Keyword                    */
          char*  other;                /* Other                      */
} context;

extern context _context;

/*
  Cobol RAN Grammar Version 0.01
  Parsing algorithm : Recursive descent parser
  Procedures corresponding to grammar non-terminals.
*/

ast* get_sentence();
ast* get_data();
ast* data_division();
ast* file_section();
ast* working_storage_section();
ast* linkage_section();


/*-----------------------  Sentence and Statement -------------------*/
/*
sntce:		stmnt
			|	stmnt '.'
	;

stmnt:	 	intlz
			| 	dsply
			|	move
	;
*/
ast* sntce();
ast* stmnt();

/*--------------  move, display and initialize Statement ------------*/

ast* move();
ast* dsply();
ast* intlz();

/*-------------------------- initialize body ------------------------*/
/*
	intlz:		INITIALIZE ids intlz.rplc
	;

	intlz.rplc:
			|	REPLACING intlz.rplc.oprnds
	;

	intlz.rplc.oprnds:	intlz.rplc.oprnds chartype BY id.litr
			|	chartype BY id.litr
	;

	chartype:	ALPHABETIC
			|	ALPHANUMERIC
			|	NUMERIC
	;
*/
int intlz_rplc ();
int intlz_rplc_oprnds();
int intlz_rplc_oprnd();
int chartype();

/*-------------------------- move body ------------------------------*/
/*
	move:		move1
			|	move2
	;

	move1:		MOVE id.litr TO ids
	;

	move2:		MOVE corresp id TO id
	;

	corresp:	CORR
			|	CORRESPONDING
	;

 Left factoring

 move:  MOVE move_oprnd

 move_oprnd:   corresp id TO id
             | id.litr TO ids
 ;
*/

/* int move_1(); */
/* int move_2(); */
ast* move_oprnd();
ast* corspnd();

/*--------------------------- display body --------------------------*/
/*
    dsply:		DISPLAY ids.litrs dsply.upon dsply.noadv
	;

	dsply.upon:
			|	UPON dsply.upon.oprnds
	;

	dsply.upon.oprnds:	mnemo.or.envir
	;

	mnemo.or.envir: id.name
	;

	dsply.noadv:
			|	WITH NO ADVANCING
			|	NO ADVANCING
	;
*/

int dsply_upon();
int dsply_noadv();
int dsply_upon_oprnds();
int dsply_upon_oprnd();
int mnemo_or_envir();

/*------------------------  Identifiers and Literals ----------------*/

/*

    ids.litrs:	ids.litrs id.litr
			|	id.litr
	;

	id.litr:	id
			|	litr
	;

	(unused) litrs:		litrs litr |	litr	;

	ids:		ids	id
			|	id
	;

*/

ast* ids_litrs();
ast* id_litr();
ast* ids();

/*------------------------  Identifier and Literal ------------------*/

/*
    litr:		LITERAL
			 	   |  HEXLITERAL
			 	   |  INTEGER
			 	   |  DECIMAL
	;

	id:			id.name id.qualif id.subscript id.refmodif
	;

	id.name: 	IDENTIFIER
	;

	id.qualif:
			|	id.qualif OF id.name
	;

	id.subscript:
			|	'(' subscripts ')'
    ;

    id.refmodif:
			|	'(' refmodif ')'
	;
*/

ast* litr();
ast* id();
ast* id_name_qualif();
ast* id_name();
ast* id_qualif();
ast* id_subscript();
ast* id_refmodif();

/*--15*07*2014-----------  Additional production  -------------------*/

ast* figurative_constants();
ast* special_register();
ast* id_subs_refm();
ast* id_oprnd_1_subs_refm();
ast* id_subs_refm_rest();
ast* id_refm_rest();
ast* id_subs_rest();
ast* times_div();
ast* power();
ast* basis();

/*-----------------------  Identifier body --------------------------*/

/*

    subscripts:	subscripts subscript
			| 	subscript
	;

    subscript:	INTEGER
			|	id.name id.qualif
			|	id.name id.qualif '-' INTEGER
			|	id.name id.qualif '+' INTEGER
	;
    subscript : arith.expr2;


    refmodif:	charleftpos ':' refmodif.length
	;

	charleftpos: 	| 	INTEGER
					|	id.name id.qualif
					|	arith.expr
	;

	refmodif.length: 	arith.expr
		 	| 	INTEGER
			|	id.name id.qualif
    ;

*/

ast* id_qualif_oprnd();
ast* subscripts();
ast* subscript();
ast* refmodif();
ast* charleftpos();
ast* refmodif_length();
ast* arith_expr();
ast* arith_expr2();


/*------------------------  Arithmetic expression -------------------*/

/*
	arith.expr:	 arith.expr.oprnd arith.expr.oprtn arith.expr
                | arith.expr.oprnd
	;
	4+(3*(2-(1)))

	arith.expr.oprnd:	INTEGER
				|	id.name id.qualif
	;

	arith.expr.oprtn: '+'
				|	'-'
				|	'*'
	;
    arith.expr2: arith.expr.oprnd arith.expr.oprtn arith.expr.oprnd
                | arith.expr.oprnd
	;

*/

ast* arith_expr_oprnd();
ast* arith_expr_oprtn();

/*--------------------- Data Declaration    -------------------------*/

ast* data_fields();
ast* data_field();
ast* data_desc();
ast* data_redefines_cl();
ast* data_index_key_cls();
ast* data_index_key_cl();
ast* data_index_by_cl();
ast* data_pic_str();
ast* data_pic_chars();
ast* data_pic_repeat();
ast* data_pic_size_local();
ast* renames_cl();
ast* cond_val_cl();
ast* cond_name();

/*--------------------- Auxiliary functions -------------------------*/

int      match(char*);
char*    get_token_val();
char*    get_token_type();
int      expect(char*);
int      error(char*);
context  set_context(char* );
int      restore_context(context);
char*    get_token_val();
char*    get_token_type();
#endif
/* GRAMMAR_H_INCLUDED */
