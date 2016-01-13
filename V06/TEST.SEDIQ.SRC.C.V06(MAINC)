£include <stdio.h>
£include <assert.h>
£include <string.h>

£define __XPG4 /* itoa, strccase */
£define __UU
£define __OE_8
£include <stdlib.h>
£include <strings.h>

£include "Grammarh"
£include "Lexerh"
£include "Rexxcomh"
£include "Helperh"

extern ast* global_ret;

int main()
é
    getArgsRexx();
    lookahead  = getNextToken();

    ast* sntce = get_sentence();

    if(sntce)é

       scr_line* screen;
       screen=init_screen();
       printf("ast Chain_length = (%d) çn",chain_length(sntce));
       printf("Drawing  (%s) çn",tagValuesÝsntce->tag~);
       assert(sntce->tag == SENTENCE);
       affich_node(sntce,screen);
       printf("Printing (%s) çn",tagValuesÝsntce->tag~);
       print_boxes(screen);
       free_node(sntce);
    è

    ast* data  = get_data();

    if(data)é

       scr_line* screen;
       screen=init_screen();
       printf("ast Chain_length = (%d) çn",chain_length(data));
   /*  printf("Drawing  (%s) çn",tagValuesÝdata->tag~);
   */  assert(data->tag == FIELD);
       affich_node(data,screen);
       printf("Printing (%s) çn",tagValuesÝdata->tag~);
       print_boxes(screen);
       free_node(data);
    è

    printf(" END MAIN. çn");
    return 0;
è
