#include <stdio.h>
#include <assert.h>
#include <string.h>

#define __XPG4 // itoa, strccase
#define __UU
#define __OE_8
#include <stdlib.h>
#include <strings.h>

#include "debug.h"
#include "Grammar.h"
#include "Lexer.h"
#include "Rexxcom.h"
#include "Helper.h"
#include "generate.h"
#include "check.h"

int main(){

    printf ("test debug   lvl (%d)\n",DEBUG_LVL);

    int  ast_len=0;

    getArgsRexx();
    lookahead  = getNextToken();

    ast* sntce = get_sentence();

    if(sntce){

       scr_line* screen;
       screen=init_screen();
       debug_1("ast Chain_length = (%d) \n",chain_length(sntce));
       debug_2("Drawing  (%s) \n",tagValues[sntce->tag]);
       assert(sntce->tag == SENTENCE);
       affich_node(sntce,screen);
       debug_2("Printing (%s) \n",tagValues[sntce->tag]);
       print_boxes(screen);
       free_node(sntce);
    }
    else free_node(sntce);

    ast* data=NULL;

    if (balayeur_pgm()){

       if(data=data_division()){
          scr_line* screen;
          screen=init_screen();
          debug_1("Drawing (%d) (%d) \n",data,data->tag);
          assert(data->tag == DATA_DIV);
      //  affich_node(data,screen);
          affich_node(data->node.data_div.ws_sect,screen);
          print_boxes(screen);
          screen=init_screen();
          affich_node(data->node.data_div.file_sect,screen);
          print_boxes(screen);
          screen=init_screen();
          affich_node(data->node.data_div.link_sect,screen);
          print_boxes(screen);
          free_node(data);
       }
    }

    /*
    ast* data  = get_data();
    if(data){

       scr_line* screen;
       screen=init_screen();
       ast_len = chain_length(data);
       debug_1("ast Chain_length = (%d) \n",ast_len);
       debug_1("Drawing (%d) (%d) \n",data,data->tag);
       assert(data->tag == FIELD);
       affich_node(data,screen);
       debug_2("Printing (%s) \n",tagValues[data->tag]);
       print_boxes(screen);
    // gen_initialize_ran  (data);
       gen_display_ran     (data);
       free_node(data);
    }
    */
    debug_1(" END MAIN. \n");
    return 0;
}

