//L880872C JOB (9,9,2,0040),'902696NSYSPI97658',MSGCLASS=Y,             J0036720
//        MSGLEVEL=(1,1),CLASS=Y,NOTIFY=L880872                         00020099
//*----------------------------------------------------------------
//COMPRESS EXEC PGM=IEBCOPY
//*----------------------------------------------------------------
//SYSPRINT DD SYSOUT=*
//SYSUT1   DD DSN=TEST.SEDIQ.LOAD,
//            DISP=SHR
//SYSIN    DD *
   COPY INDD=SYSUT1,OUTDD=SYSUT1
//****************************************************************
//* THIS JOB COMPILES, LINKS, WITHOUT EXECUTING                  *
//* "MAINC, GRAMMARC AND LEXERC".                                *
//* NOTE : FOR LONGNAME USE  "EDCCPLG"                           *
//****************************************************************
//DOC         EXEC   PROC=EDCCL,
//            CPARM='LSEARCH(''''TEST.SEDIQ.SRC.C.V07.+''''),LONGNAME'
//COMPILE.SYSIN    DD DSN=TEST.SEDIQ.SRC.C.V07(MAINC),DISP=SHR
//                 DD DSN=TEST.SEDIQ.SRC.C.V07(GRAMMARC),DISP=SHR
//                 DD DSN=TEST.SEDIQ.SRC.C.V07(LEXERC),DISP=SHR
//                 DD DSN=TEST.SEDIQ.SRC.C.V07(REXXCOMC),DISP=SHR
//                 DD DSN=TEST.SEDIQ.SRC.C.V07(TOKENZRC),DISP=SHR
//                 DD DSN=TEST.SEDIQ.SRC.C.V07(ASTC),DISP=SHR
//                 DD DSN=TEST.SEDIQ.SRC.C.V07(HELPERC),DISP=SHR
//LKED.SYSLMOD     DD DSN=TEST.SEDIQ.LOAD(MAINC),DISP=SHR
//*
//*
