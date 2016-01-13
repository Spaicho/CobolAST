£include <stdio.h>
£include <stdlib.h>
£include <string.h>

£include "helperh"

scr_line*
init_screen()È

   scr_line* scr=(scr_line*) malloc(sizeof(scr_line));
   scr->lvl       =0;
   scr->value›0~  ='Á0';
   scr->border    =0;
   scr->next      =NULL;

      debug_3("init_screen() succesfully.Án");
   return scr;

Ë

scr_line*
draw_box(scr_line* screen, char* value_1, char* value_2, int lvl)È

      debug_3("draw_box() start ... Án");


   scr_line* last_line=NULL;
   scr_line* temp     =NULL;
   scr_line* ret      =NULL;

   int shift          =0;
   int length         =0;

   ret = screen;

   /* get last line of screen */
   last_line =get_last_line(screen);
   /*
   if((lvl - last_line->lvl) > 1) È

      printf("Saut de plusieurs lvl non permis: lvl(%d)last(%d)Án",lvl,
                                                 last_line->lvl);
      exit(EXIT_FAILURE);
   Ë*/

   if(lvl < 0) È

      printf("Negative lvl not allowed : last lvl (%d) lvl (%d)Án",
                                 last_line->lvl,lvl);
      exit(EXIT_FAILURE);
   Ë

   /* calculate shift                          */
   shift = lvl * SHIFT_LEN;
   /* get max length of values                 */
   length= max_str_len(value_1,value_2);

   debug_3("draw_box():last_line->lvl (%d) Án",last_line->lvl);
   debug_3("draw_box():box to draw lvl (%d) Án",lvl);
   debug_3("draw_box():shift          (%d) Án",shift);
   debug_3("draw_box():max_str_len    (%d) Án",length);


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

   debug_3("draw_box() succesfully. Án");

   return ret   ;

Ë

scr_line*
get_last_line(scr_line* screen) È

   scr_line* temp=NULL;
   scr_line* ret =NULL;

   int i;

   temp = screen;
   ret  = temp;

      debug_3 ("start.Án");

   for(i=0;temp;i++)È

      debug_3 ("screen-%d : (%d):%sÁn",
                               i,temp,temp->value);
      ret=temp;
      temp=temp->next;
   Ë

      debug_3 ("last line is the (%d th) next.Án",i);

   return ret;

Ë

scr_line*
scr_append(scr_line* screen,scr_line* to_append) È

   scr_line* ret =NULL;

   ret =get_last_line(screen);
   ret ->next = to_append;

   debug_3("succesful        .Án");
   return screen;

Ë

int
max_str_len(char* val_a, char* val_b) È

   int a,b;
   a= strlen(val_a);
   b= strlen(val_b);
   debug_3("max_str_len(): a (%d) b (%d).Án",a,b);

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
   debug_3("draw_border()   : value=(%s)Án",ret->value);

   /* compute level */
   lvl = shift/SHIFT_LEN;
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
   debug_3("draw_border() : value=(%s)Án",ret->value);

   /* compute level */
   lvl         =shift/SHIFT_LEN;
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

   debug_3("printing screen boxes ... Án");

   int x   =1;
   int y   =1;
   int i;
   scr_line* temp;


   /* skip first node */
   for(temp=scr,i=1;temp=temp->next;i++)È

      printf("%.*sÁn",79,temp->value);

   /* if (ß(i%4))
       printf("Án");
   */
   Ë

   return 0;

Ë

char*
h_realloc(char* temp,int size)È

   debug_3("ÁnÁn");
   debug_3("h_realloc start. size (%d) Án",size);
   debug_3("h_realloc start. temp (%d) Án",temp);

   char* ret;

   debug_3("ret before (%d)Án",ret);
   ret=(char*) realloc(temp,(size) * sizeof(char));

   debug_3("ret after (%d)Án",ret);
   debug_3("Án");

   if((ret==NULL) && (size>0)) È
     printf("Realloc Failed ! Án");
     exit(EXIT_FAILURE);
   Ë
   return ret;

Ë

