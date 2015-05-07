#include <stdio.h>
#include <stdlib.h>

int main(void)
{

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
  char buff[81];

  if(stream=fopen(file_path,"r")){

     printf("Successful opening of file (%s)\n",file_path);

  } else {

     perror("Error opening file ");

  }

  ret = fread(buff,1,80,stream);
  perror("Error opening file ");
  printf("ret  for fread (%d)\n",ret);
  printf("buff for fread (%s)\n",buff);



  /*
  h_line = line;
  h_text = text;

  for(nChar=0;inChar!=EOF;nChar++){

     inChar = getc(stream);
     *(line++)=inChar;
     *(text++)=inChar;

     if (inChar=='\n') {
        nLine++;
        *(line++)='\0';
        printf("%s",h_line);
        h_line=line;
     }
  }
  *(text++)='\0';
  printf("%s",h_text);
  */
  return 0;
}
