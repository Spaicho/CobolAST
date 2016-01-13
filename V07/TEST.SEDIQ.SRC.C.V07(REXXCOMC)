£include <stdio.h>
£include <stdlib.h>
£include <string.h>

£include "Rexxcomh"

       int    argc;                 /* nombre d'arguments  */
       int    cursl;                /* position ligne   de cursor */
       int    cursc;                /* position colonne de cursor */
       char   rawcode›25000~›81~;   /* code Cobol brute           */
       int    lnumlast;             /* numero de la derniËre ligne*/
       char*  mainret;              /* zone retour                */

       int    curr_ln_num;          /* current line being parsed  */

/* bug connu : rawcode depasse le code reel par 14 car ‡ la fin */
int getArgsRexx() È

       int    i=0;
       int    rawCode_length=0;
       int    rawCode_mod_80=0;
       int    rawCode_div_80=0;

       debug_3("first arg        : %s Án",        __osplist›0~) ;
       debug_3("strcmp           : %d Án", strcmp(__osplist›0~,""));
       debug_3("first arg to int : %d Án",   atoi(__osplist›0~));

       if ((strcmp(__osplist›0~,"")) && (atoi(__osplist›0~) > 0)) È
          argc = atoi(__osplist›0~);
          debug_2("argc          : (%d) Án", argc);
       Ë
       else È
          printf("getArgsRexx() : ");
          printf("Required argument argc not found or not numeric Án");
          exit(EXIT_FAILURE);
       Ë

       if ((strcmp(__osplist›1~,"")) && (atoi(__osplist›1~) > 0)) È
          cursc = atoi(__osplist›1~);
          debug_2("cursc         : (%d) Án", cursc);
       Ë
       else È
          printf("getArgsRexx() : ");
          printf("Required argument cursc not found or not numericÁn");
          exit(EXIT_FAILURE);
       Ë

       if ((strcmp(__osplist›2~,"")) && (atoi(__osplist›2~) > 0)) È
          cursl = atoi(__osplist›2~);
          debug_2("cursl         : (%d) Án", cursl);
          /* current line number to increment on each read */
          curr_ln_num = cursl;
       Ë
       else È
          printf("getArgsRexx() : ");
          printf("Required argument cursl not found or not numericÁn");
          exit(EXIT_FAILURE);
       Ë


       if ((strcmp(__osplist›4~,"")) && (atoi(__osplist›4~) > 0)) È
          lnumlast = atoi(__osplist›4~);
          debug_2("lnumlast      : (%d) Án", lnumlast);
       Ë
       else È
          printf("getArgsRexx() : ");
       printf("Required argument lnumlast not found or not numericÁn");
          exit(EXIT_FAILURE);
       Ë

       rawCode_length = strlen(__osplist›3~);
       rawCode_mod_80 = strlen(__osplist›3~)%80;
       rawCode_div_80 = strlen(__osplist›3~)/80;

       debug_2("rawcode length : (%d) Án", rawCode_length);
       debug_2("modulo 80      : (%d) Án", rawCode_mod_80);
       debug_2("divide by 80   : (%d) Án", rawCode_div_80);

       debug_3("<%.*s>Án",80 + rawCode_mod_80,
              __osplist›3~+(rawCode_length-(80+rawCode_mod_80)));

       if (rawCode_div_80 ß= lnumlast ) È

          printf("getArgsRexx() : ");
          printf("lnumlast is not equal to rawCode_div_80Án");
          exit(EXIT_FAILURE);
       Ë

       if ((rawCode_length       > 0 )
    /* && ((strlen(__osplist›3~) % 80) == 0) */
       && ((rawCode_div_80           ) <= 25000)) È

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

int
setCurrLnNum(int num)È

  curr_ln_num = num;

Ë
