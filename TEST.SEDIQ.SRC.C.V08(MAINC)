£include <stdio.h>
£include <assert.h>
£include <string.h>

£define __XPG4 // itoa, strccase
£define __UU
£define __OE_8
£include <stdlib.h>
£include <strings.h>

£include "debugh"
£include "Grammarh"
£include "Lexerh"
£include "Rexxcomh"
£include "Helperh"
£include "genrateh"
£include "checkh"

int main()é

    printf ("test debug   lvl (%d)çn",DEBUG_LVL);

    int  ast_len=0;

    getArgsRexx();
    lookahead  = getNextToken();

    ast* sntce = get_sentence();

    if(sntce)é

       scr_line* screen;
       screen=init_screen();
       debug_1("ast Chain_length = (%d) çn",chain_length(sntce));
       debug_2("Drawing  (%s) çn",tagValuesÝsntce->tag~);
       assert(sntce->tag == SENTENCE);
       affich_node(sntce,screen);
       debug_2("Printing (%s) çn",tagValuesÝsntce->tag~);
       print_boxes(screen);
       free_node(sntce);
    è
    else free_node(sntce);

    ast* data=NULL;

    if (balayeur_pgm())é

       if(data=data_division())é
          scr_line* screen;
          screen=init_screen();
          debug_1("Drawing (%d) (%d) çn",data,data->tag);
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
       è
    è

    /*
    ast* data  = get_data();
    if(data)é

       scr_line* screen;
       screen=init_screen();
       ast_len = chain_length(data);
       debug_1("ast Chain_length = (%d) çn",ast_len);
       debug_1("Drawing (%d) (%d) çn",data,data->tag);
       assert(data->tag == FIELD);
       affich_node(data,screen);
       debug_2("Printing (%s) çn",tagValuesÝdata->tag~);
       print_boxes(screen);
    // gen_initialize_ran  (data);
       gen_display_ran     (data);
       free_node(data);
    è
    */
    debug_1(" END MAIN. çn");
    return 0;
è

