£include <stdio.h>
£include <stdlib.h>

int main(void)
È

  FILE   *stream;
//char   *file_path = "'TEST.SEDIQ.PGM(MTDTMS01)'";
//char   *file_path = "'CTR.L880872.RAN.D14283.T74614(member)'";
//char   *file_path = "'CTR.L880872.JCL(BCPTFBL1)'";
  char   *file_path = "'CTR.L880872.JCL(member)'";
  int    nChar=0;
  int    nLine=0;
  int    inChar=0;
  char*  line;
  char*  h_line;
  char*  text;
  char*  h_text;
  int ret=0;
  char buff›81~;

  if(stream=fopen(file_path,"r"))È

     printf("Successful opening of file (%s)Án",file_path);

  Ë else È

     perror("Error opening file ");

  Ë

  ret = fread(buff,1,80,stream);
  perror("Error opening file ");
  printf("ret  for fread (%d)Án",ret);
  printf("buff for fread (%s)Án",buff);



  /*
  h_line = line;
  h_text = text;

  for(nChar=0;inCharß=EOF;nChar++)È

     inChar = getc(stream);
     *(line++)=inChar;
     *(text++)=inChar;

     if (inChar=='Án') È
        nLine++;
        *(line++)='Á0';
        printf("%s",h_line);
        h_line=line;
     Ë
  Ë
  *(text++)='Á0';
  printf("%s",h_text);
  */
  return 0;
Ë
