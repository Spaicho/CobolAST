//IBMUSERC JOB (9,9,2,0040),'902696NSYSPI97658',MSGCLASS=Y,          
//        MSGLEVEL=(1,1),CLASS=A,NOTIFY=IBMUSER                      
//*---------------------------------------------------------------- 
//* JCL script for project building and cleaning on z/OS 
//*----------------------------------------------------------------   
//CBCPROC JCLLIB ORDER='CBC.SCCNPRC'                                 
//*----------------------------------------------------------------  
//COMPRESS EXEC PGM=IEBCOPY                                          
//*----------------------------------------------------------------  
//SYSPRINT DD SYSOUT=*                                               
//SYSUT1   DD DSN=PREF.USER.WKSPACE.CCC.LINKLIB,                     
//            DISP=SHR                                               
//SYSIN    DD *                                                      
   COPY INDD=SYSUT1,OUTDD=SYSUT1                                     
//****************************************************************   
//AST         EXEC   PROC=EDCC,                                      
//    CPARM='LSEARCH(''''PREF.USER.WKSPACE.CCC.+''''),OPTF(DD:OPTF)',
//   INFILE='PREF.USER.WKSPACE.CCC.C(AST)',                          
//  OUTFILE='PREF.USER.WKSPACE.CCC.O,DISP=SHR'                       
//COMPILE.OPTF  DD DSN=PREF.USER.WKSPACE.CCC.JCL(COMPOPTS),DISP=SHR  
//*----------------------------------------------------------------  
//CHECK       EXEC   PROC=EDCC,                                      
//    CPARM='LSEARCH(''''PREF.USER.WKSPACE.CCC.+''''),OPTF(DD:OPTF)',
//   INFILE='PREF.USER.WKSPACE.CCC.C(CHECK)',                        
//  OUTFILE='PREF.USER.WKSPACE.CCC.O,DISP=SHR'                       
//COMPILE.OPTF  DD DSN=PREF.USER.WKSPACE.CCC.JCL(COMPOPTS),DISP=SHR  
//*----------------------------------------------------------------  
//GENERATE    EXEC   PROC=EDCC,                                      
//    CPARM='LSEARCH(''''PREF.USER.WKSPACE.CCC.+''''),OPTF(DD:OPTF)',
//   INFILE='PREF.USER.WKSPACE.CCC.C(GENERATE)',                     
//  OUTFILE='PREF.USER.WKSPACE.CCC.O,DISP=SHR'                       
//COMPILE.OPTF  DD DSN=PREF.USER.WKSPACE.CCC.JCL(COMPOPTS),DISP=SHR  
//*----------------------------------------------------------------  
//GRAMMAR     EXEC   PROC=EDCC,                                      
//    CPARM='LSEARCH(''''PREF.USER.WKSPACE.CCC.+''''),OPTF(DD:OPTF)',
//   INFILE='PREF.USER.WKSPACE.CCC.C(GRAMMAR)',                      
//  OUTFILE='PREF.USER.WKSPACE.CCC.O,DISP=SHR'                       
//COMPILE.OPTF  DD DSN=PREF.USER.WKSPACE.CCC.JCL(COMPOPTS),DISP=SHR  
//*----------------------------------------------------------------  
//HELPER      EXEC   PROC=EDCC,                                      
//    CPARM='LSEARCH(''''PREF.USER.WKSPACE.CCC.+''''),OPTF(DD:OPTF)',
//   INFILE='PREF.USER.WKSPACE.CCC.C(HELPER)',                       
//  OUTFILE='PREF.USER.WKSPACE.CCC.O,DISP=SHR'                       
//COMPILE.OPTF  DD DSN=PREF.USER.WKSPACE.CCC.JCL(COMPOPTS),DISP=SHR  
//*----------------------------------------------------------------  
//LEXER       EXEC   PROC=EDCC,                                      
//    CPARM='LSEARCH(''''PREF.USER.WKSPACE.CCC.+''''),OPTF(DD:OPTF)',
//   INFILE='PREF.USER.WKSPACE.CCC.C(LEXER)',                        
//  OUTFILE='PREF.USER.WKSPACE.CCC.O,DISP=SHR'                       
//COMPILE.OPTF  DD DSN=PREF.USER.WKSPACE.CCC.JCL(COMPOPTS),DISP=SHR  
//*----------------------------------------------------------------  
//REXXCOM     EXEC   PROC=EDCC,                                      
//    CPARM='LSEARCH(''''PREF.USER.WKSPACE.CCC.+''''),OPTF(DD:OPTF)',
//   INFILE='PREF.USER.WKSPACE.CCC.C(REXXCOM)',                      
//  OUTFILE='PREF.USER.WKSPACE.CCC.O,DISP=SHR'                       
//COMPILE.OPTF  DD DSN=PREF.USER.WKSPACE.CCC.JCL(COMPOPTS),DISP=SHR  
//*----------------------------------------------------------------  
//TOKENIZE    EXEC   PROC=EDCC,                                      
//    CPARM='LSEARCH(''''PREF.USER.WKSPACE.CCC.+''''),OPTF(DD:OPTF)',
//   INFILE='PREF.USER.WKSPACE.CCC.C(TOKENIZE)',                     
//  OUTFILE='PREF.USER.WKSPACE.CCC.O,DISP=SHR'                       
//COMPILE.OPTF  DD DSN=PREF.USER.WKSPACE.CCC.JCL(COMPOPTS),DISP=SHR  
//*----------------------------------------------------------------  
//MAIN        EXEC   PROC=EDCCL,                                     
//    CPARM='LSEARCH(''''PREF.USER.WKSPACE.CCC.+''''),OPTF(DD:OPTF)',
//   INFILE='PREF.USER.WKSPACE.CCC.C(MAIN)',                         
//  OUTFILE='PREF.USER.LOADE,DISP=SHR'                               
//COMPILE.OPTF  DD DSN=PREF.USER.WKSPACE.CCC.JCL(COMPOPTS),DISP=SHR  
//LKED.OBJECT DD DSN=PREF.USER.WKSPACE.CCC.O,DISP=SHR                
//SYSIN     DD *                                                     
   INCLUDE OBJECT(AST)       
   INCLUDE OBJECT(CHECK)     
   INCLUDE OBJECT(GENERATE)  
   INCLUDE OBJECT(GRAMMAR)   
   INCLUDE OBJECT(LEXER)     
   INCLUDE OBJECT(HELPER)    
   INCLUDE OBJECT(REXXCOM)   
   INCLUDE OBJECT(TOKENIZE)  
   NAME CCC(R)               
//*                          
