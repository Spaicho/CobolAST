£include <stdio.h>
£include <stddef.h>
£include <stdlib.h>
£include "asth"

static int lvl=-1;


/*---   SENTENCE   ---*/
ast*
make_sentence    (int nb_statement, struct ast* list_statement)é

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.sentence.ast_name          = "SENTENCE";
  e->tag = SENTENCE;

  e->node.sentence.nb_statement = nb_statement;
  e->node.sentence.list_statement = NULL;

  /* if(nb_statement > 0 ) */
  e->node.sentence.list_statement = list_statement;

  e->next =NULL;

  debug_2("**********  SENTENCE   ***************çn");
  debug_2("* SENTENCE AST BUILT SUCCESFULLY (%d)*çn",e);
  debug_2("**************************************çn");

  return e;

è

ast*
make_ast ()é

  ast* e = (ast*) malloc(sizeof(ast));
  e->next =NULL;
  e->tag = UNKNOWN_AST;

  return e;

è

affich_sentence(ast* tree,scr_line* screen)é


   ast* temp = NULL;

   lvl++;
   draw_box(screen,tree->node.sentence.ast_name,"",lvl);

   temp=tree->node.sentence.list_statement;

   while(temp §= NULL)é
      affich_statement(temp,screen);
      temp = temp->next;
   è

   lvl--;

è

affich_statement(ast* tree,scr_line* screen)é

   debug_2("Switch for statement ... çn");
   ast* temp = NULL;

   debug_3("Statement (%s) çn",tagValuesÝtree->tag~);
   debug_2("Statement (%d) çn",tree->tag);

   lvl++;

   if      (tree->tag == MOVE_STM)

           affich_move_stm(tree,screen);

   else if (tree->tag == DISPLAY_STM)

           affich_display_stm(tree,screen);

   else if (tree->tag == INITIALIZE_STM)

           affich_initialize_stm(tree,screen);

   else é

        /* printf("Unknown Tag for statement (%s) çn",
                                tagValuesÝtree->tag~);
        */ printf("Unknown Tag for statement (%d) çn",
                                          tree->tag );
           exit(EXIT_FAILURE);
   è

   lvl--;
è

/*---   MOVE   ---*/
ast*
make_move        (int bool_corresp, int nb_operand_r,
                  struct ast* operand_g, struct ast* list_operand_r)é

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.move_stm.ast_name          = "MOVE";
  e->tag = MOVE_STM;

  e->node.move_stm.bool_corresp      = bool_corresp;
  e->node.move_stm.nb_operand_r      = nb_operand_r;
  e->node.move_stm.operand_g         = operand_g   ;
  e->node.move_stm.list_operand_r    = list_operand_r;

  e->next =NULL;
  debug_2("**********  MOVE       **********çn");
  debug_2("* MOVE    AST BUILT SUCCESFULLY *çn");
  debug_2("**********************************çn");

  return e;

è

affich_move_stm(ast* tree,scr_line* screen)é

   ast* temp = NULL;

   char* value=malloc(125);

   if (tree->node.move_stm.bool_corresp)
      strcpy(value,"CORRESP ");
   else
      strcpy(value,"");

   draw_box(screen,tree->node.move_stm.ast_name,value,lvl);
   strcpy(value,"");

   lvl++;
   affich_node(tree->node.move_stm.operand_g,screen);
   lvl--;

   draw_box(screen,"TO","",lvl);
   strcpy(value,"");

   temp=tree->node.move_stm.list_operand_r;

   lvl++;
   while(temp §= NULL)é
      debug_3("Printing inner nodes (%s) çn",tagValuesÝtemp->tag~);
      debug_2("Printing inner nodes (%d) çn",          temp->tag );
      affich_operand(temp,screen);
      temp=temp->next;
   è
   lvl--;

è
/*---   DISPLAY   ---*/
ast*
make_display (int bool_upon, int bool_no_adv, char* upon_operand,
                   int nb_operand, struct ast* list_operand)é

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.display_stm.ast_name          = "DISPLAY";
  e->tag = DISPLAY_STM;

  e->node.display_stm.bool_upon         = bool_upon;
  e->node.display_stm.bool_no_adv       = bool_no_adv;
  strcpy(e->node.display_stm.upon_operand,upon_operand);
  /*e->node.display_stm.upon_operand = upon_operand; */
  e->node.display_stm.nb_operand        = nb_operand;
  e->node.display_stm.list_operand   = NULL;

  if(nb_operand > 0 )
     e->node.display_stm.list_operand   = list_operand;

  e->next =NULL;

  debug_2("**********  DISPLAY    **********çn");
  debug_2("* DISPLAY AST BUILT SUCCESFULLY *çn");
  debug_2("**********************************çn");

  return e;

è

affich_display_stm(ast* tree,scr_line* screen)é

   ast* temp = NULL;

   draw_box(screen,tree->node.display_stm.ast_name,"",lvl);

   temp=tree->node.display_stm.list_operand;
   lvl++;
   while(temp §= NULL)é
      debug_3("Printing inner nodes (%s) çn",tagValuesÝtemp->tag~);
      debug_2("Printing inner nodes (%d) çn",          temp->tag );
      affich_operand(temp,screen);
      temp=temp->next;
   è
   lvl--;

è

ast*
make_initialize  (int bool_repl, int nb_operand,
                  struct ast* list_operand)é

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.initialize_stm.ast_name          = "INITIALIZE";
  e->tag = INITIALIZE_STM;

  e->node.initialize_stm.bool_repl         = bool_repl;
  e->node.initialize_stm.nb_operand        = nb_operand;
  e->node.initialize_stm.list_operand      = list_operand;

  e->next =NULL;
  debug_2("**********  INITIALIZE   **********çn");
  debug_2("* INITIALIZE AST BUILT SUCCESFULLY *çn");
  debug_2("************************************çn");

  return e;


è

affich_initialize_stm(ast* tree,scr_line* screen)é

   ast* temp = NULL;

   char* value=malloc(125);

   if (tree->node.initialize_stm.bool_repl)
      strcpy(value,"REPLACING ");
   else
      strcpy(value,"");

   draw_box(screen,tree->node.initialize_stm.ast_name,value,lvl);
   strcpy(value,"");


   temp=tree->node.initialize_stm.list_operand;

   lvl++;
   while(temp §= NULL)é
      debug_3("Printing inner nodes (%s) çn",tagValuesÝtemp->tag~);
      debug_2("Printing inner nodes (%d) çn",          temp->tag );
      affich_operand(temp,screen);
      temp=temp->next;
   è
   lvl--;
è


/*---   OPERAND   ---*/
ast*
make_operand (int bool_literal, int bool_identifier,
                  struct ast* operand)é

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.operand.ast_name          = "OPERAND";
  e->tag = OPERAND;


  e->next =NULL;
  debug_3("**********  OPERAND    **********çn");
  debug_3("* OPERAND AST BUILT SUCCESFULLY (%d)*çn",e);
  debug_3("**********************************çn");

  return e;

è

affich_operand(ast* tree,scr_line* screen)é

   ast* temp = NULL;

   if      (tree->tag == LITERAL)

           affich_literal(tree,screen);

   else if (tree->tag == IDENTIFIER)

           affich_identifier(tree,screen);

   else exit(EXIT_FAILURE);

è

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
                  int char_length)é

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


    strcpy(e->node.literal.value,value);
  /* e->node.literal.value=value; */
  /*sprintf(e->node.literal.value,"%.*s",strlen(value),value);*/

  e->next =NULL;

  debug_2("**********  LITERAL   **********çn");
  debug_2("* LITERAL AST BUILT SUCCESFULLY (%d)*çn",e);
  debug_2("*********************************çn");

  return e;

è

affich_literal(ast* tree,scr_line* screen)é

   /* comportement bizzare des strings */
   /* str continue toujours a garder sa valeur tout au long du pgm */
   char* value=malloc(125);
   strcpy(value,"ALL ");

   if (tree->node.literal.bool_all)
      draw_box(screen,tree->node.literal.ast_name,
      strcat(value,tree->node.literal.value),lvl);

   else

   draw_box(screen,tree->node.literal.ast_name,
            tree->node.literal.value,lvl);

   strcpy(value,"");

è

ast*
make_identifier  (int bool_length, int bool_address,
                  int bool_special_reg,
                  struct ast* name, struct ast* qualif,
                  struct ast* subscript, struct ast* refmod)é

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.identifier.ast_name          = "IDENTIFIER";
  e->tag = IDENTIFIER;

  e->node.identifier.bool_length       = bool_length;
  e->node.identifier.bool_address      = bool_address;
  e->node.identifier.bool_special_reg  = bool_special_reg;
/*strcpy(e->node.identifier.special_reg_value,special_reg_value);*/
/*e->node.identifier.special_reg_value=special_reg_value;*/

  e->node.identifier.name              = name;
  e->node.identifier.qualif            = qualif;
  e->node.identifier.subscript         = subscript;
  e->node.identifier.refmod            = refmod;

  e->next =NULL;
  debug_2("**********  IDENTIFIER   **********çn");
  debug_2("* IDENTIFIER AST BUILT SUCCESFULLY (%d)*çn",e);
  debug_2("************************************çn");

  return e;

è

affich_identifier(ast* tree,scr_line* screen)é

   char* value_1=malloc(125);
   char* value_2=malloc(125);
   strcpy(value_1,"");
   strcpy(value_2,"");

   if(tree->node.identifier.bool_address)
      strcpy(value_1,"ADDRESS OF ");

   if(tree->node.identifier.bool_length)
      strcpy(value_1,"LENGTH OF ");

   if(tree->node.identifier.bool_special_reg)
      strcpy(value_2,"SPECIAL REG ");


   ast* name = tree->node.identifier.name;
   draw_box(screen,strcat(value_2,tree->node.identifier.ast_name),
                          value_1,lvl);

   strcpy(value_1,"");
   strcpy(value_2,"");

   lvl++;

   debug_2("Identifier name  ? (%d)çn",tree->node.identifier.name);
   if(tree->node.identifier.name §= NULL)
      affich_ident_name(tree->node.identifier.name,screen);

   debug_2("Identifier qualif? (%d)çn",tree->node.identifier.qualif);
   if(tree->node.identifier.qualif §= NULL)
      affich_ident_qualif(tree->node.identifier.qualif,screen);

   debug_2("Identifier subscr  (%d)çn",tree->node.identifier.subscript);;
   if(tree->node.identifier.subscript §= NULL)
      affich_ident_subscript(tree->node.identifier.subscript,screen);

   debug_2("Identifier refmod ? (%d)çn",tree->node.identifier.refmod);
   if(tree->node.identifier.refmod §= NULL)
      affich_ident_refmod(tree->node.identifier.refmod,screen);
   lvl--;
è


ast*
make_ident_name_qualif
                 (struct ast* name, struct ast* qualif)é

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.ident_name_qualif.ast_name          = "IDENT_NAME_QUALIF";
  e->tag = IDENT_NAME_QUALIF;

  e->node.ident_name_qualif.name       = name;
  e->node.ident_name_qualif.qualif     = qualif;


  e->next =NULL;
  debug_2("*********** ID NAME QUALIF  ***********çn");
  debug_2("* ID NAME QUALIF AST BUILT SUCCESFULLY (%d)*çn",e);
  debug_2("****************************************çn");

  return e;

è

affich_ident_name_qualif(ast* tree,scr_line* screen)é


è

ast*
make_ident_name  (int length, char* value)é

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.ident_name.ast_name          = "IDENT_NAME";
  e->tag = IDENT_NAME;

  e->node.ident_name.length            = length;
  strcpy(e->node.ident_name.value,value);

  e->next =NULL;
  debug_2("*********** ID NAME  ***********çn");
  debug_2("* ID NAME AST BUILT SUCCESFULLY (%d)*çn",e);
  debug_2("*********************************çn");
  return e;


è

affich_ident_name(ast* tree,scr_line* screen)é

   draw_box(screen,tree->node.ident_name.ast_name,
                   tree->node.ident_name.value,lvl);
è

ast*
make_ident_qualif(struct ast* list_qualif)é

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.ident_qualif.ast_name          = "IDENT_QUALIF";
  e->tag = IDENT_QUALIF;

  e->node.ident_qualif.list_qualif     = list_qualif;


  e->next =NULL;
  debug_2("*********** ID QUALIF  ***********çn");
  debug_2("* ID QUALIF AST BUILT SUCCESFULLY (%d)*çn",e);
  debug_2("***********************************çn");
  return e;

è

affich_ident_qualif(ast* tree,scr_line* screen)é

   ast* temp = NULL;


   temp=tree->node.ident_qualif.list_qualif;

   lvl++;
   while(temp §= NULL)é
      draw_box(screen,tree->node.ident_qualif.ast_name,
                   temp->node.ident_name.value,lvl);

      temp=temp->next;
   è
   lvl--;

è


ast*
make_ident_subscript
                 (struct ast* list_subscript)é

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.ident_subscript.ast_name          = "IDENT_SUBSCRIPT";
  e->tag = IDENT_SUBSCRIPT;

  e->node.ident_subscript.list_subscript  = list_subscript;

  debug_2("*********** ID SUBSCR  ***********çn");
  debug_2("* ID SUBSCR AST BUILT SUCCESFULLY *çn");
  debug_2("***********************************çn");


  e->next =NULL;
  return e;


è

affich_ident_subscript(ast* tree,scr_line* screen)é

   ast* temp = NULL;

   draw_box(screen,tree->node.ident_subscript.ast_name,"",lvl);

   temp=tree->node.ident_subscript.list_subscript;

   lvl++;
   while(temp §= NULL)é
      debug_3("Printing (%s) (%d)     çn",tagValuesÝtemp->tag~,temp);
      debug_2("Printing (%d) (%d)     çn",          temp->tag ,temp);
      affich_arith_exp(temp,screen);
      /*
      draw_box(screen,tree->node.ident_subscript.ast_name,
                      temp->node.arith_exp.value,lvl);
      */
      temp=temp->next;
   è
   lvl--;
è


ast*
make_ident_refmod(struct ast* charleft, struct ast* length)é

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.ident_refmod.ast_name          = "IDENT_REFMOD";
  e->tag = IDENT_REFMOD;

  e->node.ident_refmod.charleft        = charleft;
  e->node.ident_refmod.length          = length;

  debug_2("*********** ID REFMOD  ***********çn");
  debug_2("* ID REFMOD AST BUILT SUCCESFULLY *çn");
  debug_2("***********************************çn");


  e->next =NULL;
  return e;


è

affich_ident_refmod(ast* tree,scr_line* screen)é


   draw_box(screen,tree->node.ident_refmod.ast_name,"",lvl);

   lvl++;

   draw_box(screen,"OFFSET","",lvl);
   affich_arith_exp(tree->node.ident_refmod.charleft,screen);

   if(tree->node.ident_refmod.length)é
     draw_box(screen,"LENGTH","",lvl);
     affich_arith_exp(tree->node.ident_refmod.length,screen);
   è
   lvl--;

è

ast*
make_arith_exp   (char* value, char* oper, char* sign,
                  struct ast* left, struct ast* right)é

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.arith_exp.ast_name          = "ARITH_EXP";
  e->tag = ARITH_EXP;

  strcpy(e->node.arith_exp.value,value);
  strcpy(e->node.arith_exp.oper ,oper );
  strcpy(e->node.arith_exp.sign ,sign );

  e->node.arith_exp.left              = left;
  e->node.arith_exp.right             = right;

  e->next =NULL;
  return e;

è

affich_arith_exp(ast* tree,scr_line* screen)é

   /*draw_box(screen,tree->node.arith_exp.ast_name,"",lvl);*/

   if (strlen(tree->node.arith_exp.sign)>0)
      draw_box(screen,"SIGN",tree->node.arith_exp.sign,lvl);

   if (tree->node.arith_exp.left)
      affich_node(tree->node.arith_exp.left,screen);

   if (strlen(tree->node.arith_exp.oper)>0)
      draw_box(screen,"OPERATION",tree->node.arith_exp.oper,lvl);

   if (tree->node.arith_exp.right)
      affich_node(tree->node.arith_exp.right,screen);

è

/*--- DATA_DIV ---*/
ast*
make_data_div    (struct ast* file_sect, struct ast* ws_sect,
                  struct ast* link_sect)é

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.data_div.ast_name          = "DATA_DIV";
  e->tag = DATA_DIV;

  e->node.data_div.file_sect         = file_sect;
  e->node.data_div.ws_sect           = ws_sect;
  e->node.data_div.link_sect         = link_sect;

  debug_2("*********** DATA DIV   ***********çn");
  debug_2("* DATA DIV  AST BUILT SUCCESFULLY *çn");
  debug_2("***********************************çn");

  e->next =NULL;
  return e;

è

/*---   FIELD    ---*/
ast*
make_field (struct ast*  name,
            struct ast*  copy,
            field_name   field_name,
            field_lvl    field_lvl,
            int          lvl,
            int          name_length,
            int          size,
            int          offset,
            int          nb_indexes,
            int          nb_parents,
            int          bool_blank_zero,
            int          bool_justified,
            int          bool_global,
            int          bool_external,
            int          bool_bouchon,
            int          nb_bouchon,
            struct ast*  occurs,
            struct ast*  usage,
            struct ast*  field_value,
            struct ast*  cond_88,
            struct ast*  parent,
            struct ast*  children,
            struct ast*  redefines,
            struct ast*  renames,
            struct ast*  search,
            struct ast*  picture,
            struct ast*  field_sign,
            struct ast*  field_sync,
            section_t    section
           )é

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.field.ast_name                = "FIELD";
  e->tag = FIELD;

  e->node.field.name                    = name;
  e->node.field.copy                    = copy;
  e->node.field.field_name              = field_name;
  e->node.field.field_lvl               = field_lvl;
  e->node.field.lvl                     = lvl;
  e->node.field.name_length             = name_length;
  e->node.field.size                    = size;
  e->node.field.offset                  = offset;
  e->node.field.nb_indexes              = nb_indexes;
  e->node.field.nb_parents              = nb_parents;
  e->node.field.bool_blank_zero         = bool_blank_zero;
  e->node.field.bool_justified          = bool_justified;
  e->node.field.bool_global             = bool_global;
  e->node.field.bool_external           = bool_external;
  e->node.field.bool_bouchon            = bool_bouchon;
  e->node.field.nb_bouchon              = nb_bouchon;
  e->node.field.occurs                  = occurs;
  e->node.field.usage                   = usage;
  e->node.field.field_value             = field_value;
  e->node.field.cond_88                 = cond_88;
  e->node.field.parent                  = parent;
  e->node.field.children                = children;
  e->node.field.redefines               = redefines;
  e->node.field.renames                 = renames;
  e->node.field.search                  = search;
  e->node.field.picture                 = picture;
  e->node.field.field_sign              = field_sign;
  e->node.field.field_sync              = field_sync;
  e->node.field.section                 = section;

  e->next =NULL;

  debug_2("**********  FIELD   **********çn");
  debug_2("* FIELD AST BUILT SUCCESFULLY (%d)*çn",e);
  debug_2("*******************************çn");

  return e;

è

ast*
update_field_init(struct ast* field, struct ast* name,
                  field_name field_name, field_lvl field_lvl, int lvl)é

  field->node.field.name                    = name;
  field->node.field.field_name              = field_name;
  field->node.field.field_lvl               = field_lvl;
  field->node.field.lvl                     = lvl;

  return field;

è

ast*
update_field     (struct ast* field, struct ast* clause, tag_t tag)é

  switch(tag)é

     case CL_EXTERNAL  :
        field->node.field.bool_external      = 1;
        return field;

     case CL_BLANK_WHEN_ZERO :
        field->node.field.bool_blank_zero    = 1;
        return field;

     case CL_GLOBAL    :
        field->node.field.bool_global        = 1;
        return field;

     case CL_JUSTIFIED :
        field->node.field.bool_justified     = 1;
        return field;

     case CL_OCCURS    :
        field->node.field.occurs             = clause;
        return field;

     case CL_PICTURE   :
        field->node.field.picture            = clause;
        return field;

     case CL_SIGN      :
        field->node.field.field_sign         = clause;
        return field;

     case CL_VALUE     :
        field->node.field.field_value        = clause;
        return field;

     case CL_SYNCHRONIZED :
        field->node.field.field_sync         = clause;
        return field;

     case CL_USAGE        :
        field->node.field.usage              = clause;
        return field;

     default :
        printf("Update_field : Unknown clause (%d)çn",tag);
        exit(EXIT_FAILURE);

  è

è

ast*
make_occurs (int times, int to_times, ast* depend_on, ast* indexes,
                                                      ast* keys )é

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.occurs.ast_name               = "OCCURS";
  e->tag = OCCURS;

  e->node.occurs.times                   = times;
  e->node.occurs.to_times                = to_times;
  e->node.occurs.depend_on               = depend_on;
  e->node.occurs.keys                    = keys;
  e->node.occurs.indexes                 = indexes;

  e->next =NULL;

  debug_2("*********** OCCURS   **********çn");
  debug_2("* OCCURS AST BUILT SUCCESFULLY (%d)*çn",e);
  debug_2("********************************çn");

  return e;
è

ast*
make_occurs_key (int bool_asc, int bool_des, ast* key)é

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.occurs_key.ast_name               = "OCCURS_KEY";
  e->tag = OCCURS_KEY;

  e->node.occurs_key.bool_asc            = bool_asc;
  e->node.occurs_key.bool_des            = bool_des;
  e->node.occurs_key.key                 = key;

  e->next =NULL;

  debug_2("*********** OCCURS_KEY *********çn");
  debug_2("* OCCURS_KEY BUILT SUCCESFULLY (%d)*çn",e);
  debug_2("********************************çn");

  return e;
è

ast*
make_pic_cmpnt(pic_cmpnt_t pic_cmpnt,int repeat, char* chars,
                                                 char* currency)é
  ast* e = (ast*) malloc(sizeof(ast));
  e->node.pic_cmpnt.ast_name               = "PIC_CMPNT";
  e->tag = PIC_CMPNT;

  e->node.pic_cmpnt.pic_cmpnt            = pic_cmpnt;

  switch (pic_cmpnt)   é
     case PIC_REPEAT   :
          e->node.pic_cmpnt.pic_val.repeat       = repeat;
          break;
     case PIC_CHARS    :
          strcpy(e->node.pic_cmpnt.pic_val.chars,chars);
          break;
     case PIC_CURRENCY :
          strcpy(e->node.pic_cmpnt.pic_val.currency,currency);
          break;

     default           :
          printf("pic_cmpnt unknown çn");
          exit(EXIT_FAILURE);
  è

  e->next =NULL;

  debug_2("*********** PIC_CMPNT *********çn");
  debug_2("* PIC_CMPNT BUILT SUCCESFULLY (%d)*çn",e);
  debug_2("*******************************çn");

  return e;
è

ast*
make_field_sign(int bool_leading, int bool_trailing, int bool_separate,
                int bool_character)é

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.field_sign.ast_name               = "FIELD_SIGN";
  e->tag = FIELD_SIGN;

  e->node.field_sign.bool_leading         = bool_leading;
  e->node.field_sign.bool_trailing        = bool_trailing;
  e->node.field_sign.bool_separate        = bool_separate;
  e->node.field_sign.bool_character       = bool_character;

  e->next =NULL;

  debug_2("*********** FIELD_SIGN *********çn");
  debug_2("* FIELD_SIGN BUILT SUCCESFULLY (%d)*çn",e);
  debug_2("*******************************çn");

  return e;
è

ast*
make_field_value(ast* value, ast* thru_value)é

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.field_value.ast_name            = "FIELD_VALUE";
  e->tag = FIELD_VALUE;

  e->node.field_value.value               = value;
  e->node.field_value.thru_value          = thru_value;

  e->next =NULL;

  debug_2("*********** FIELD_VALUE *********çn");
  debug_2("* FIELD_VALUE BUILT SUCCESFULLY (%d)*çn",e);
  debug_2("*********************************çn");

  return e;
è

ast*
make_usage(usage_t usage)é

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.usage.ast_name                  = "USAGE";
  e->tag = USAGE;

  e->node.usage.usage                     = usage;

  e->next =NULL;

  debug_2("*********** USAGE *********çn");
  debug_2("* USAGE BUILT SUCCESFULLY (%d)*çn",e);
  debug_2("***************************çn");

  return e;
è

ast*
make_renames(ast* id_qualif,ast* thru_id_qualif)é

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.renames.ast_name                  = "RENAMES";
  e->tag = RENAMES;

  e->node.renames.id_qualif                 = id_qualif;
  e->node.renames.thru_id_qualif            = thru_id_qualif;

  e->next =NULL;

  debug_2("*********** RENAMES *********çn");
  debug_2("* RENAMES BUILT SUCCESFULLY (%d)*çn",e);
  debug_2("*****************************çn");

  return e;
è

ast*
make_field_sync(int bool_right, int bool_left)é

  ast* e = (ast*) malloc(sizeof(ast));
  e->node.field_sync.ast_name            = "FIELD_SYNC";
  e->tag = FIELD_SYNC;

  e->node.field_sync.bool_right          = bool_right;
  e->node.field_sync.bool_left           = bool_left;

  e->next =NULL;

  debug_2("*********** FIELD_SYNC *********çn");
  debug_2("* FIELD_SYNC BUILT SUCCESFULLY *çn");
  debug_2("********************************çn");

  return e;
è

affich_field (ast* tree,scr_line* screen)é

   assert(tree->tag==FIELD);
   assert((§tree->next)!!tree->next->tag==FIELD);
   static int nb_call=0;
   nb_call++;
   debug_3("repere nb call (%d)çn",nb_call);


   ast*  temp    =NULL;
   debug_3("tree->tag (%s) value (%s) çn",tagValuesÝtree->tag~
                                         ,tree->node.field.name->
                                          node.ident_name.value);
   char* buffer_1=malloc(125);
   char* buffer_2=malloc(125);
   char* buffer  =malloc(125);


   /* buffer 1 */

   itoa(tree->node.field.lvl,buffer_1,10); /* lvl */
   strcat(buffer_1," ");

   itoa(tree->node.field.nb_parents,buffer,10); /* nb_parents */
   strcat(buffer_1,buffer);
   strcat(buffer_1," ");
   strcpy(buffer,"");

 //itoa(tree->node.field.nb_bouchon,buffer,10); /* nb_bouchon */
 /*strcat(buffer_1,buffer);
   strcat(buffer_1," ");
   strcpy(buffer,"");
   */
   strcat(buffer_1,FLD_NAME(tree));


   if(tree->node.field.occurs       ) é
      strcat(buffer_1," OCCURS ");
      itoa(tree->node.field.occurs->node.occurs.times,buffer,10);
      strcat(buffer_1,buffer);                        /* times */
      strcpy(buffer,"");
      if(tree->node.field.occurs->node.occurs.to_times>0)é
         strcat(buffer_1," TO ");
         itoa(tree->node.field.occurs->node.occurs.to_times,buffer,10);
         strcat(buffer_1,buffer);                     /* to_times */
         strcpy(buffer,"");
      è
   è


   if(tree->node.field.redefines    ) é
      strcat(buffer_1," REDEF ");
      strcat(buffer_1,tree->node.field.redefines
                          ->node.ident_name.value);
   è


   if(tree->node.field.picture      ) é
      strcat(buffer_1," PIC ");
      temp=tree->node.field.picture;
      while(temp)é
         switch (temp->node.pic_cmpnt.pic_cmpnt) é
            case PIC_REPEAT :
                 itoa(temp->node.pic_cmpnt.pic_val.repeat,buffer,10);
                 strcat(buffer_1,"(");
                 strcat(buffer_1,buffer);
                 strcat(buffer_1,")");
                 break;
            case PIC_CHARS  :
                 strcat(buffer_1,temp->node.pic_cmpnt.pic_val.chars);
                 break;
            case PIC_CURRENCY :
                 strcat(buffer_1,temp->node.pic_cmpnt.pic_val.currency);
                 break;
            default         :
                 printf("pic_cmpnt unknown !çn");
                 exit(EXIT_FAILURE);
         è
         temp=temp->next;
      è

   è


   temp=tree->node.field.field_value;
   if(temp)strcat(buffer_1," VALUE ");

   while(temp)é
      strcpy(buffer," ");
      strcat(buffer,
      temp->node.field_value.value->node.literal.value);
      if (temp->node.field_value.thru_value)é
          strcat(buffer," THRU ");
          strcat(buffer,
          temp->node.field_value.thru_value->node.literal.value);
      è
      strcat(buffer_1,buffer);
      strcpy(buffer,"");
      temp=temp->next;
   è


   if(tree->node.field.usage        ) é
      strcat(buffer_1," USAGE ");
      strcat(buffer_1,usageValuesÝtree->node.field.usage
                                      ->node.usage.usage~);
   è


   if(tree->node.field.renames          ) é
      strcat(buffer_1," RENAMES ");
      strcat(buffer_1,
      tree->node.field.renames->node.renames.id_qualif
                              ->node.identifier.name
                              ->node.ident_name.value);
      if (tree->node.field.renames->node.renames.thru_id_qualif)é
          strcat(buffer_1," THRU ");
          strcat(buffer_1,
          tree->node.field.renames->node.renames.thru_id_qualif
                                  ->node.identifier.name
                                  ->node.ident_name.value);
      è
   è


   /* buffer 2 */

   if(tree->node.field.bool_blank_zero) é
      strcat(buffer_2," BLANK WHEN ZERO -");
   è
   if(tree->node.field.bool_justified ) é
      strcat(buffer_2," JUSTIFIED -");
   è
   if(tree->node.field.field_sign       ) é
      strcat(buffer_2," SIGN ");
      if(tree->node.field.field_sign->node.field_sign.bool_leading) é
         strcat(buffer_2,"LEAD ");
      è
      if(tree->node.field.field_sign->node.field_sign.bool_trailing) é
         strcat(buffer_2,"TRAIL ");
      è
      if(tree->node.field.field_sign->node.field_sign.bool_separate) é
         strcat(buffer_2,"SEPARATE ");
      è
      if(tree->node.field.field_sign->node.field_sign.bool_character) é
         strcat(buffer_2,"CHAR ");
      è
      strcat(buffer_2,"-");
   è


   if(tree->node.field.field_sync) é
      strcat(buffer_2," SYNC ");
      if(tree->node.field.field_sync->node.field_sync.bool_right)é
         strcat(buffer_2,"RIGHT -");
      è else if(tree->node.field.field_sync->node.field_sync.bool_left)é
         strcat(buffer_2,"LEFT -");
      è else é
         strcat(buffer_2,"-");
      è
   è
   if(tree->node.field.bool_global) é
      strcat(buffer_2," GLOBAL -");
   è
   if(tree->node.field.bool_external) é
      strcat(buffer_2," EXTERNAL -");
   è


   lvl = tree->node.field.nb_parents;// + tree->node.field.nb_bouchon;
   debug_3("nb_parents  (%d) nb_bouchon(%d) draw lvl  (%d)çn",
   tree->node.field.nb_parents,tree->node.field.nb_bouchon,lvl);

   draw_box(screen,buffer_1,buffer_2,lvl);

   strcpy(buffer_1,"");
   strcpy(buffer_2,"");
   strcpy(buffer,"");
   free(buffer_1);
   free(buffer);


   temp =tree->node.field.children;

   if(temp) é
  /*  lvl++; */
      affich_field(temp,screen);
  /*  lvl--; */
   è

   temp =tree->next;

   if(temp) é
      debug_2("afficher next field : addr (%d) çn",temp);

      affich_field(temp,screen);
   è

è

affich_binary_op(ast* tree,scr_line* screen)é


è

affich_data_div(ast* tree,scr_line* screen)é

   debug_1("afficher file_sectçn");
   affich_node(tree->node.data_div.file_sect);
   debug_1("afficher ws_sectçn");
   affich_node(tree->node.data_div.ws_sect);
   debug_1("afficher link_sectçn");
   affich_node(tree->node.data_div.link_sect);

è

affich_declaration(ast* tree,scr_line* screen)é


è

affich_special_reg(ast* tree,scr_line* screen)é


è

int
chain_length(ast* tree)é

   ast* p=NULL;
   int  n=0;

   for(p=tree;p;p=p->next)é
      n++;
      debug_3("p%d : %d (%d) (%s) çn",n,p,p->tag,
                        p->node.field.name->node.ident_name.value);
   è
      debug_3("Chain  length (%d) çn",n);
   return n;
è

                     /***                 ***/
ast*
append_list (struct ast* list, struct ast* toadd)é

  debug_3("çn*******************************************");
  debug_3("çn");
  debug_3("append_list element(%s) to list (%s) start ...çn",
            tagValuesÝtoadd->tag~    ,tagValuesÝlist->tag~);
  debug_3("list (%d) list->next (%d) toadd (%d) toadd->next (%d) çn",
          list,list->next,toadd,toadd->next);
  debug_3("çn*******************************************çn");

  ast* head;

  if(list == NULL)é


     debug_3("list (%d) list->next (%d)çn",toadd,toadd->next);

     return toadd;
  è

  head = list;

  while(list->next §= NULL)é
     debug_3("noeud visité non non null passer au suivant ... çn");
     list = list->next;
  è

  list->next=toadd;
  /*list->next=NULL;*/

  debug_3("append succesful            çn");
  debug_3("çn*****************************************çn");
  debug_3("head (%d) head->next (%d) list (%d) list->next (%d) çn",
          head,head->next,list,list->next);
  debug_3("çn*******************************************");
  debug_3("çn");

  return head;

è

void
append_child(struct ast* dad, struct ast* child)é

  ast* head;
  ast* temp=NULL;

  if(FLD_CHILD(dad)) debug_3("dad first child (%s)çn",
  FLD_NAME(FLD_CHILD(dad)));

  if(FLD_CHILD(dad) == NULL)é

     debug_3("Dad has no children çn");
     FLD_CHILD(dad) = child;
     return;
  è

  temp = FLD_CHILD(dad);

  while(temp->next)é
     debug_3("Hi bro (%s)çn",FLD_NAME(temp->next));
     temp = temp->next;
  è

  debug_3("dad put your child (%s) next bro (%s) çn",
           FLD_NAME(child),FLD_NAME(temp));

  temp->next=child;


è

/*              Affichage des AST                       */

affich_node (ast* tree,scr_line* screen)é

   if (tree==NULL) return;

   debug_1("  afficher node (%d) çn",tree->tag);

   if      (tree->tag == SENTENCE)

           affich_sentence(tree,screen);

   else if (tree->tag == DECLARATION)

           affich_declaration(tree,screen);

   else if (tree->tag == DATA_DIV   )

           affich_data_div(tree,screen);

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

   else if (tree->tag == FIELD)

           affich_field(tree,screen);

   else é
          /* printf("node to print not allowed (%s) çn",
                     tagValuesÝtree->tag~);
          */ printf("node to print not allowed (%d) (%d)çn",
                               tree,tree->tag );
             exit(EXIT_FAILURE);
   è

è

/*              Free AST               */

free_node   (ast* tree)é

   /* si ast n'est pas créée */
   if (tree==NULL) return;

   /* Cas spécial ast : free children first */
   if ((tree->tag == FIELD) && (tree->node.field.children)) é
      debug_2("Child to free found (%d)çn",tree->node.field.children);
      free_node(tree->node.field.children);
   è

   if(tree->next)é
      debug_2("Next to free found (%d)(%d)çn",
                                           tree->next->tag,tree->next);
      free_node(tree->next);
   è

   debug_3("Real free start switch (%d)(%d)çn",tree->tag,tree);

   switch (tree->tag) é

      case SENTENCE          : free_sentence(tree);tree=NULL;break;
      case DECLARATION       : free_declaration(tree);tree=NULL;break;
      case DATA_DIV          : free_data_div(tree);tree=NULL;break;
      case STATEMENT         : free_statement(tree);tree=NULL;break;
      case MOVE_STM          : free_move_stm(tree);tree=NULL;break;
      case DISPLAY_STM       : free_display_stm(tree);tree=NULL;break;
      case INITIALIZE_STM    : free_initialize_stm(tree);               ;
                               tree=NULL;break;
      case OPERAND           : free_operand(tree);tree=NULL;break;
      case LITERAL           : free_literal(tree);tree=NULL;break;
      case IDENTIFIER        : free_identifier(tree);tree=NULL;break;
      case IDENT_NAME        : free_ident_name(tree);tree=NULL;break;
      case IDENT_NAME_QUALIF : free_ident_name_qualif(tree);
                               tree=NULL;break;
      case IDENT_QUALIF      : free_ident_qualif(tree);tree=NULL;break;
      case IDENT_SUBSCRIPT   : free_ident_subscript(tree);              k;
                               tree=NULL;break;
      case IDENT_REFMOD      : free_ident_refmod(tree);tree=NULL;break;
      case SPECIAL_REG       : free_special_reg(tree);tree=NULL;break;
      case ARITH_EXP         : free_arith_exp(tree);tree=NULL;break;
      case BINARY_OP         : free_binary_op(tree);tree=NULL;break;
      case FIELD             : free_field(tree);tree=NULL;break;
      case OCCURS            : free_occurs(tree);tree=NULL;break;
      case OCCURS_KEY        : free_occurs_key(tree);tree=NULL;break;
      case PIC_CMPNT         : free_pic_cmpnt(tree);tree=NULL;break;
      case FIELD_SIGN        : free_field_sign(tree);tree=NULL;break;
      case FIELD_VALUE       : free_field_value(tree);tree=NULL;break;
      case FIELD_SYNC        : free_field_sync(tree);tree=NULL;break;
      case USAGE             : free_usage(tree);tree=NULL;break;
      case RENAMES           : free_renames(tree);tree=NULL;break;
      default:
        /* printf("Unknown Tag (%d)(%s) çn", tree->tag,
           tagValuesÝtree->tag~); */
           printf("Unknown Tag (%d)(%d) çn", tree->tag,tree);
           exit(EXIT_FAILURE);
   è

   debug_3("Real free end for (%d)(%d)çn",tree->tag,tree);
è



free_sentence(ast* tree)é

   free_node(tree->node.sentence.list_statement);

   free(tree);

è

free_declaration(ast* tree)é

   free(tree);

è

free_statement(ast* tree)é /* to_del */

   free(tree);

è

free_move_stm(ast* tree)é

   free_node(tree->node.move_stm.operand_g);
   free_node(tree->node.move_stm.list_operand_r);
   free(tree);

è

free_display_stm(ast* tree)é

   free_node(tree->node.display_stm.list_operand);
   free(tree);

è

free_initialize_stm(ast* tree)é

   free_node(tree->node.initialize_stm.list_operand);
   free(tree);

è

free_operand(ast* tree)é

   free_node(tree->node.operand.operand);
   free(tree);
è

free_literal(ast* tree)é

   free(tree);
è

free_identifier(ast* tree)é

   free_node(tree->node.identifier.name);
   free_node(tree->node.identifier.qualif);
   free_node(tree->node.identifier.subscript);
   free_node(tree->node.identifier.refmod);

   free(tree);

è

free_ident_name(ast* tree)é

   free(tree);

è

free_ident_name_qualif(ast* tree)é /* to_del */

   free_node(tree->node.ident_name_qualif.name);
   free_node(tree->node.ident_name_qualif.qualif);

   free(tree);

è

free_ident_qualif(ast* tree)é

   free_node(tree->node.ident_qualif.list_qualif);

   free(tree);

è

free_ident_refmod(ast* tree)é

   free_node(tree->node.ident_refmod.charleft);
   free_node(tree->node.ident_refmod.length);

   free(tree);

è

free_ident_subscript(ast* tree)é

   free_node(tree->node.ident_subscript.list_subscript);

   free(tree);

è

free_special_reg(ast* tree)é

   free(tree);

è

free_arith_exp(ast* tree)é

   free_node(tree->node.arith_exp.left);
   free_node(tree->node.arith_exp.right);

   free(tree);
è

free_data_div(ast* tree)é

   free_node(tree->node.data_div.file_sect);
   free_node(tree->node.data_div.ws_sect);
   free_node(tree->node.data_div.link_sect);

   free(tree);
è

free_field(ast* tree)é

   free_node(tree->node.field.name);
   free_node(tree->node.field.copy);
   free_node(tree->node.field.occurs);
   free_node(tree->node.field.usage);
   free_node(tree->node.field.field_value);
   free_node(tree->node.field.cond_88);
 /*free_node(tree->node.field.parent);*/
 /*free(tree->node.field.parent);tree->node.field.parent =NULL;*/
 /*free_node(tree->node.field.children);*/
   free_node(tree->node.field.redefines);
   free_node(tree->node.field.renames);
   free_node(tree->node.field.search);
   free_node(tree->node.field.picture);
   free_node(tree->node.field.field_sign);
   free_node(tree->node.field.field_sync);
   free(tree);

è

free_occurs(ast* tree)é

   free_node(tree->node.occurs.depend_on);
   free_node(tree->node.occurs.keys);
   free_node(tree->node.occurs.indexes);

   free(tree);

è

free_occurs_key(ast* tree)é

   free_node(tree->node.occurs_key.key);

   free(tree);

è

free_pic_cmpnt(ast* tree)é

   free(tree);

è

free_field_sign(ast* tree)é

   free(tree);

è

free_field_value(ast* tree)é

   free_node(tree->node.field_value.value);
   free_node(tree->node.field_value.thru_value);
   free(tree);

è

free_field_sync(ast* tree)é

   free(tree);
è

free_usage(ast* tree)é

   free(tree);

è

free_renames(ast* tree)é

   free_node(tree->node.renames.id_qualif);
   free_node(tree->node.renames.thru_id_qualif);
   free(tree);

è

free_binary_op(ast* tree)é /* to_del */

   free(tree);

è

/* Maj de nombre de bouchon pour tous les childs */
/* en entrée : premier child */
void
maj_nb_bouchon(ast* tree)é

   assert(tree->tag==FIELD);

   tree->node.field.nb_bouchon++;

   ast* p =NULL;

   for(p=tree->node.field.children;p;p=p->node.field.children)é

      maj_nb_bouchon(p);

   è

   for(p=tree->next;p;p=p->next)é

      maj_nb_bouchon(p);

   è

è

