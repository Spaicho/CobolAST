//L880872C JOB (9,9,2,0040),'902696NSYSPI97658',MSGCLASS=Y,             J0045688
//        MSGLEVEL=(1,1),CLASS=Y,NOTIFY=L880872                         00020099
//*----------------------------------------------------------------
// JCLLIB ORDER=(CBC.SCCNPRC)
//*----------------------------------------------------------------
//COMPRESS EXEC PGM=IEBCOPY
//*----------------------------------------------------------------
//SYSPRINT DD SYSOUT=*
//SYSUT1   DD DSN=TEST.SEDIQ.LOAD,
//            DISP=SHR
//SYSIN    DD *
   COPY INDD=SYSUT1,OUTDD=SYSUT1
//****************************************************************
//* THIS JOB COMPILES, BIND
//****************************************************************
//DOC         EXEC   PROC=EDCCB,
//        CPARM='OPTF(DD:OPTF),LSEARCH(''''TEST.SEDIQ.SRC.C.V08.+'''')'
//COMPILE.SYSIN    DD DSN=TEST.SEDIQ.SRC.C.V08(MAINC),DISP=SHR
//                 DD DSN=TEST.SEDIQ.SRC.C.V08(GRAMMARC),DISP=SHR
//                 DD DSN=TEST.SEDIQ.SRC.C.V08(LEXERC),DISP=SHR
//                 DD DSN=TEST.SEDIQ.SRC.C.V08(REXXCOMC),DISP=SHR
//                 DD DSN=TEST.SEDIQ.SRC.C.V08(TOKENZRC),DISP=SHR
//                 DD DSN=TEST.SEDIQ.SRC.C.V08(ASTC),DISP=SHR
//                 DD DSN=TEST.SEDIQ.SRC.C.V08(HELPERC),DISP=SHR
//                 DD DSN=TEST.SEDIQ.SRC.C.V08(CHECKC),DISP=SHR
//                 DD DSN=TEST.SEDIQ.SRC.C.V08(GENRATEC),DISP=SHR
//BIND.SYSLMOD     DD DSN=TEST.SEDIQ.LOAD(MAINC),DISP=SHR
//COMPILE.OPTF     DD *
LONGNAME  GONUMBER SSCOMM AGGREGATE EXPMAC
RENT LIST SOURCE DEF(DEBUG_LVL=1)

//* LOCALE(EN_US.IBM-1140) CHECKOUT DEBUG OPTIMIZE HOT INLINE ASCII
//* NOMARGINS XREF TEST(ALL) INITAUTO SHOWMACROS SUPPRESS TERMINAL
//* EVENTSINFO
/*
