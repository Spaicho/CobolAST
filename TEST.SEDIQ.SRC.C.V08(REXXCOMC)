£include <stdio.h>
£define __XPG4 // itoa, strccase
£define __UU
£define __OE_8
£include <stdlib.h>
£include <string.h>
£include <ctype.h>
£include <assert.h>
£include "debugh"
£include "Rexxcomh"

int        argc;
int        cursl;
int        cursc;
char       src_fileÝDS_NAME_LEN~;
char       inc_pdsÝNB_INC_PDS~ÝDS_NAME_LEN~;
char       optionsÝNB_OPTIONS~ÝDS_NAME_LEN~;
int        main_ret;
_editLine  resultÝNB_RESULTS~;

//int        curr_ln_num;
_srcLine   *src_list;
_srcLine   *curr_src_line;

/* bug connu : rawcode depasse le code reel par 14 car à la fin */
int getArgsRexx() é

       int    i=0;
       int    rawCode_length=0;
       int    rawCode_mod_80=0;
       int    rawCode_div_80=0;

       debug_3("osplist 0 : %s çn",        __osplistÝ0~) ;

       if ((strcmp(__osplistÝ0~,"")) && (atoi(__osplistÝ0~) > 0)) é
          argc = atoi(__osplistÝ0~);
          debug_3("argc          : (%d) çn", argc);
       è
       else é
          printf("getArgsRexx() : ");
          printf("Required argument argc not found or not numeric çn");
          exit(EXIT_FAILURE);
       è

       debug_3("osplist 1 : %s çn",        __osplistÝ1~) ;
       if ((strcmp(__osplistÝ1~,"")) && (atoi(__osplistÝ1~) > 0)) é
          cursc = atoi(__osplistÝ1~);
          debug_3("cursc         : (%d) çn", cursc);
       è
       else é
          printf("getArgsRexx() : ");
          printf("Required argument cursc not found or not numericçn");
          exit(EXIT_FAILURE);
       è

       debug_3("osplist 2 : %s çn",        __osplistÝ2~) ;
       if ((strcmp(__osplistÝ2~,"")) && (atoi(__osplistÝ2~) > 0)) é
          cursl = atoi(__osplistÝ2~);
          debug_3("cursl         : (%d) çn", cursl);
          /* current line number to increment on each read */
          //curr_ln_num = cursl;
       è
       else é
          printf("getArgsRexx() : ");
          printf("Required argument cursl not found or not numericçn");
          exit(EXIT_FAILURE);
       è

       debug_3("osplist 3 : %s çn",        __osplistÝ3~) ;
       if ((strcmp(__osplistÝ3~,""))) é
          strcpy(src_file,__osplistÝ3~);
          debug_3("src_file      : (%s) çn", src_file);
       è
       else é
          printf("getArgsRexx() : ");
          printf("Required argument src_file not found çn");
          exit(EXIT_FAILURE);
       è

       debug_3("osplist 4 : %s çn",        __osplistÝ4~) ;
       if ((strcmp(__osplistÝ4~,""))) é
          break_str_space(__osplistÝ4~,inc_pds,NB_INC_PDS);
          debug_3("inc_pds(0)    : (%s) çn", inc_pdsÝ0~);
       è
       else é
          printf("getArgsRexx() : ");
          printf("Required argument inc_pds  not found çn");
          exit(EXIT_FAILURE);
       è

       debug_3("osplist 5 : %s çn",        __osplistÝ5~) ;
       if ((strcmp(__osplistÝ5~,""))) é
          break_str_space(__osplistÝ5~,options,NB_OPTIONS);
          debug_3("options(0)    : (%s) çn", optionsÝ0~);
       è
       else é
          printf("getArgsRexx() : ");
          printf("Required argument options  not found çn");
          exit(EXIT_FAILURE);
       è

       src_list = getSource(src_file,0);

       curr_src_line = getCurrSrcLine(src_list,cursl,cursc);

è

void
setCurrLnStrart()é

    curr_src_line= src_list;

è

int
break_str_space(char *line, char wordsÝ~ÝDS_NAME_LEN~,int maxWords)é

   char *p          = line;
   char *buffÝDS_NAME_LEN~;
   int   nbWords       = 0;
   int   i;

   while(1)
   é
      while(isspace(*p))
        p++;


      if(*p == 'ç0')
        break;

      buffÝnbWords++~ = p;

      while(§isspace(*p) && *p §= 'ç0')
        p++;

      if(*p == 'ç0')
        break;

      *p++ = 'ç0';

      if(nbWords >= maxWords)
        break;
   è

   for(i=0;i<=nbWords;i++)é
      strcpy(wordsÝi~,buffÝi~);
   è

   return nbWords;
è

_srcLine*
getSource(char* srcFile,int currLine)é

  FILE      *stream;
  _srcLine  *p;
  _srcLine  *l;
  char      buffÝ85~;
  int       i;
  int       ret=0;

  printf("sizeof(_srcLine) (%d)çn",sizeof(_srcLine));

  if(stream=fopen(srcFile,
//"r,lrecl=80,blksize=240,recfm=fb,type=record"))é
//"rb,lrecl=80,blksize=8000,recfm=fb,type=record"))é
  "rb,lrecl=80,recfm=fb,type=record"))é
//"r"))é

     debug_2("Successful opening of file (%s)çn",srcFile);

  è else é

     perror("Error opening file ");
     exit(EXIT_FAILURE);
  è

  p = NULL;
  l = NULL;

  for(i=1;;i++)é

     ret=fread(buff,1,80,stream);
     if(ferror(stream))é

        perror("Error reading file ");
        exit(EXIT_FAILURE);

     è else if (feof(stream)) é

        debug_2("EOF çn");
        if (fclose(stream) §= 0) perror("fclose error");

        break;

     è

     if(§p)é
        p = malloc(sizeof(_srcLine));
        l = p;
     è else é
        p->next = malloc(sizeof(_srcLine));
        p = p->next;
     è

     strncpy(p->value,buff,80);
  // printf("i (%d) ret (%d)çn",i,ret);
  // printf("p->value(%s)çn",p->value);

     p->num_file = i;
     p->num_all  = i + currLine;
     strcat(p->file,srcFile);
     p->next = NULL;

  è
  debug_3("nb lignes lues (%d)çn",i-1);
  debug_3("src_list l     (%d)çn",l);

  return l;

è

_srcLine*
getCurrSrcLine(_srcLine* srcList,int cursl,int cursc)é

  _srcLine  *l;
  int        i;

  debug_3 ("srcList (%d)çn",srcList);
  debug_3 ("cursl   (%d)çn",cursl);
  assert(srcList);

  l = srcList;

  for(i=1;l;i++)é
 //  printf("l (%s)çn",l->value);
     if(i==cursl)
        break;
     l = l->next;

  è

  if(§l) é

     printf("current srcLine cant be found from cursorçn");
     exit(EXIT_FAILURE);
  è

  debug_3 ("l       (%d)çn",l);
  return l;

è
