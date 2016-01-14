£include <regex.h>
£include <stdio.h>
£include <stdlib.h>
£include <string.h>

£include "tokenzrh"

£define NB_MATCH_MAX    10
£define NB_REGEX_MAX    30

  /*---------------------------------------------------------------*/
  /* FTA1: modulariser le code : regex, communication avec REXX    */
  /*       reduction du string , creation de la liste des tokens   */
  /*---------------------------------------------------------------*/
  /* la reduction du string enleve le separteur de debut           */
  /* (espace, virgule mais pas ' pour string )                     */
  /*---------------------------------------------------------------*/
  /* L'ordre de check des REgex semblables est :                   */
  /* -Keyword avant identifier, c ce qui en fait des mots reserves */
  /* -Dernier regex est : Espace puis enfin Erreur.                */
  /* -hexa literal avant identifier                                */
  /* exemple : x'ff'=> hex literal                                 */
  /* exemple : A'ff'=> identifier + string literal                 */
  /* -Choisir le match le plus long                                */
  /* exemple : **   => exponent au lieu de multiply                */
  /*           2,2  => decimal au lieu de integer                  */
  /*           a-b  => identifier a au lieu de a - b               */
  /*           a+b  => a + b                                       */
  /*---------------------------------------------------------------*/


token tokenizer(char* ln_8_72)
È
    token _ret = È0,0,0,"ERROR","ERROR"Ë;

    static int reduction_len;
    /****/ int regcomp_type_done=0;
    /****/ int regcomp_attr_done=0;

    /* Regex for token type         */
    /****/ regex_t    pregIdent;
    /****/ regex_t    pregPicChars;
    /****/ regex_t    pregLiterNum;
    /****/ regex_t    pregLiterQuot;
    /****/ regex_t    pregKeywoAll;
    /****/ regex_t    pregSymbols;
    /****/ regex_t    pregEndLine;
    /****/ regex_t    pregSpace;

    /* Regex for token attributes   */
    /****/ regex_t    pregSpclReg;
    /****/ regex_t    pregFgrtvConst;
    /****/ regex_t    pregNumeric;
    /****/ regex_t    pregQuoted;
    /****/ regex_t    pregSQuoted;
    /****/ regex_t    pregDQuoted;
    /****/ regex_t    pregHex;
    /****/ regex_t    pregAlphanum;
    /****/ regex_t    pregIntgr;
    /****/ regex_t    pregDecim;
    /****/ regex_t    pregUnsigned;
    /****/ regex_t    pregPositive;
    /****/ regex_t    pregNegative;
    /****/ regex_t    pregLvlnum;
    /****/ regex_t    pregRelOp;
    /****/ regex_t    pregAritOp;

 /* regex_t    pregLiter1;
    regex_t    pregLiter2;
    regex_t    pregPerio;
    regex_t    pregLvl66;
    regex_t    pregLvl88;
    regex_t    pregHexL1;
    regex_t    pregHexL2;
    regex_t    pregLBrack;
    regex_t    pregRBrack;
    regex_t    pregPlus;
    regex_t    pregMinus;
    regex_t    pregExpon;
    regex_t    pregMultp;
    regex_t    pregDivid;
    regex_t    pregEqual;
    regex_t    pregColon;
    regex_t    pregDollar;
    regex_t    pregUintgr; */

  /*    _____________________________________________________
      _(                                                     )_
     =_                I D E N T I F I E R                    _=
       (_____________________________________________________)
                                                                  */

  /*----------------------------*/
  /* Pattern pour indentifier   */
  /*--------------------------------------------------------------*/
  /* - SÈparateur dÈbut: aucan ou plusieurs espaces ou virgules   */
  /* - Corps : Un mot cobol composÈ de lettres et chiffres        */
  /*   ainsi que tiret et undersoce qui doivent pas apparaitre    */
  /*   au debut ou ‡ a fin. doit contenir au moins une lettre     */
  /* - SÈparateur fin  : point, espace, virgule, fin, quote ou "  */
  /*--------------------------------------------------------------*/

    /****/ char *ptrnIdent = "^( !,)*"                                Á
   "((›0-9~+›-_~*)*›0-9~*›A-Za-z~›A-Za-z0-9~*(›-_~+›A-Za-z0-9~+)*)"Á
                          "(.*)";

  /*    _____________________________________________________
      _(                                                     )_
     =_            P I C T U R E  C H A R A C T E R           _=
       (_____________________________________________________)
                                                                  */

  /*-------------------------------------------*/
  /* FTA1: ponctuation                         */
  /* FTA2: CR et DB                            */
  /*--------------------------------------------------------------*/
  /* - picture-string =  currency? (picchar+ repeat?)+            */
  /*   currency       =  $                                        */
  /*   picchar        =  ›ABEGPSVXZabegpsvxz90Á+Á-Á*Á$~           */
  /*   repeat         =  "(" ›0-9~+ ")"                           */
  /*   mannque plus que CR et DB pour les pic string              */
  /*--------------------------------------------------------------*/

  /*char     *ptrnPicChars = "(^"                              Á
                   "(›ABEGPSVXZabegpsvxz90ÁÁ+ÁÁ-ÁÁ*ÁÁ$ÁÁ/ÁÁ,ÁÁ.~+))"Á
  */          /*   "(( !,)*!ÁÁ()(.*)"; */                  Á
              /*   "(( !,)+!ÁÁ.!ÁÁ()(.*)"; */              Á
  /*               "(( !,!$)+ÁÁ.!ÁÁ.!ÁÁ()(.*)";
  */
  /*char     *ptrnPicChars = "(^"                              Á */
  /* A*  */ /*     "(›ABEGPSVXZabegpsvxz90ÁÁ+ÁÁ-ÁÁ*ÁÁ$ÁÁ/ÁÁ,~*"Á */
  /* (A+ */ /*     "(›ABEGPSVXZabegpsvxz90ÁÁ+ÁÁ-ÁÁ*ÁÁ$ÁÁ/ÁÁ,~+"Á */
  /* b)  */ /*     "!ÁÁ.)"                                     Á */
  /* A*  */ /*     "›ABEGPSVXZabegpsvxz90ÁÁ+ÁÁ-ÁÁ*ÁÁ$ÁÁ/ÁÁ,~*))"Á */
              /*   "(( !,)*!ÁÁ()(.*)"; */
              /*   "(( !,)+›a-zA-Z~+!( !,)*ÁÁ.!ÁÁ()(.*)"; */
            /*     "(( !,!$)+!ÁÁ.!ÁÁ()(.*)"; */


    /****/ char *ptrnPicChars = "(^"                              Á
  /* A+  */  /*    "(›ABEGPSVXZabegpsvxz90ÁÁ+ÁÁ-ÁÁ*ÁÁ$ÁÁ/ÁÁ,~+))" */Á
                   "(›-+*$/,ABEGPSVXZabegpsvxz90~+))" Á
                   "(( !,!$)+!ÁÁ.!ÁÁ()(.*)";


  /*    _____________________________________________________
      _(                                                     )_
     =_             L I T E R A L  N U M E R I C              _=
       (_____________________________________________________)
                                                                  */

  /*--------------------------------------------------------------*/
  /* - SÈparateur dÈbut: Zero ou plusieurs : espaces ou virgules  */
  /* - Corps : Commence par le separateur de string quote ou "    */
  /*   puis zero ou une suite de caractËres sauf separateur de    */
  /*   string ou un double separateur de string et finit par le   */
  /*   meme separateur de string                                  */
  /* - SÈparateur fin  : point, espace, virgule, fin, quote ou "  */
  /*--------------------------------------------------------------*/
    /****/ char   *ptrnLiterNum = "^( !,)*("                      Á
                           "(›ÁÁ+ÁÁ-~?›0-9~*,›0-9~+)!"  /* -9,7 */Á
                           "(›ÁÁ+ÁÁ-~?›0-9~+)"         /* +987 */Á
                      /*    ")(›^'~!$)(.*)"; */                   Á
                           ")(.*)";                               Á
  /*    _____________________________________________________
      _(                                                     )_
     =_             L I T E R A L  Q U O T E                  _=
       (_____________________________________________________)
                                                                  */

    /****/ char *ptrnLiterQuot = "^( !,)*("                         Á
                           "('(›^'~!'')*')!"            /*  '.' */ Á
                           "(Á"(›^Á"~!Á"Á")*Á")!"       /*  "." */ Á
                           "(›Xx~›'~›0-9A-Fa-f~+›'~)!"  /* x'.' */ Á
                           "(›Xx~›Á"~›0-9A-Fa-f~+›Á"~)" /* x"." */ Á
                      /*    ")(›^'~!$)(.*)"; */                    Á
                           ")(.*)";                                Á
  /*    _____________________________________________________
      _(                                                     )_
     =_                   K E Y W O R D                       _=
       (_____________________________________________________)
                                                                  */

    /****/ char *ptrnKeywoAll = "^( !,)*("                          Á
    /*   A   */                                                    Á
    "ACCEPT!ALPHABETIC-LOWER!APPLY!"                               Á
    "ACCESS!ALPHABETIC-UPPER!ARE!"                                 Á
    "ADD!ALPHANUMERIC!AREA!"                                       Á
    "ALPHANUMERIC-EDITED!AREAS!ADDRESS!"                           Á
    "ADVANCING!ALSO!ASCENDING!"                                    Á
    "AFTER!ALTER!ASSIGN!"                                          Á
    "ALTERNATE!AT!ALL!"                                            Á
    "ALPHABET!AND!AUTHOR!"                                         Á
    "ALPHABETIC!ANY!"                                              Á
    /*   B   */                                                    Á
    "BASIS!BINARY!BOTTOM!"                                         Á
    "BEFORE!BLANK!BY!"                                             Á
    "BEGINNING!BLOCK!"                                             Á
    /*   C   */                                                    Á
    "CALL!COLUMN!COMPUTATIONAL-5!"                                 Á
    "CANCEL!COM-REG!COMPUTE!"                                      Á
    "CBL!COMMA!CONFIGURATION!"                                     Á
    "CD!COMMON!CONTAINS!"                                          Á
    "CF!COMMUNICATION!CONTENT!"                                    Á
    "CH!COMP!CONTINUE!"                                            Á
    "CHARACTER!COMP-1!CONTROL!"                                    Á
    "CHARACTERS!COMP-2!CONTROLS!"                                  Á
    "CLASS!COMP-3!CONVERTING!"                                     Á
    "CLASS-ID!COMP-4!COPY!"                                        Á
    "CLOCK-UNITS!COMP-5!CORR!"                                     Á
    "CLOSE!COMPUTATIONAL!CORRESPONDING!"                           Á
    "COBOL!COMPUTATIONAL-1!COUNT!"                                 Á
    "CODE!COMPUTATIONAL-2!CURRENCY!"                               Á
    "CODE-SET!COMPUTATIONAL-3!"                                    Á
    "COLLATING!COMPUTATIONAL-4!"                                   Á
    /*   D   */                                                    Á
    "DATA!DEBUG-SUB-1!DESTINATION!"                                Á
    "DATE-COMPILED!DEBUG-SUB-2!DETAIL!"                            Á
    "DATE-WRITTEN!DEBUG-SUB-3!DISPLAY!"                            Á
    "DAY!DEBUGGING!DISPLAY-1!"                                     Á
    "DAY-OF-WEEK!DECIMAL-POINT!DIVIDE!"                            Á
    "DBCS!DECLARATIVES!DIVISION!"                                  Á
    "DE!DELETE!DOWN!"                                              Á
    "DEBUG-CONTENTS!DELIMITED!DUPLICATES!"                         Á
    "DELIMITER!DYNAMIC!DEBUG-ITEM!"                                Á
    "DEPENDING!DEBUG-LINE!"                                        Á
    "DESCENDING!DEBUG-NAME!"                                       Á
    /*   E   */                                                    Á
    "EGCS!END-INVOKE!ENDING!"                                      Á
    "EGI!END-MULTIPLY!ENTER!"                                      Á
    "EJECT!END-OF-PAGE!ENTRY!"                                     Á
    "ELSE!END-PERFORM!ENVIRONMENT!"                                Á
    "EMI!END-READ!EOP!"                                            Á
    "ENABLE!END-RECEIVE!EQUAL!"                                    Á
    "END!END-RETURN!ERROR!"                                        Á
    "END-ADD!END-REWRITE!ESI!"                                     Á
    "END-CALL!END-SEARCH!EVALUATE!"                                Á
    "END-COMPUTE!END-START!EVERY!"                                 Á
    "END-DELETE!END-STRING!EXCEPTION!"                             Á
    "END-DIVIDE!END-SUBTRACT!EXIT!"                                Á
    "END-EVALUATE!END-UNSTRING!EXTEND!"                            Á
    "END-IF!END-WRITE!EXTERNAL!"                                   Á
    /*   F   */                                                    Á
    "FALSE!FILLER!FOR!"                                            Á
    "FD!FINAL!FROM!"                                               Á
    "FILE!FIRST!FUNCTION!"                                         Á
    "FILE-CONTROL!FOOTING!"                                        Á
    /*   G   */                                                    Á
                                                                   Á
    "GENERATE!GO!GROUP!"                                           Á
    "GIVING!GOBACK!"                                               Á
    "GLOBAL!GREATER!"                                              Á
    /*   H   */                                                    Á
                                                                   Á
    "HEADING!HIGH-VALUE!HIGH-VALUES!"                              Á
    /*   I   */                                                    Á
    "I-O!INDICATE!INSPECT!"                                        Á
    "I-O-CONTROL!INHERITS!INSTALLATION!"                           Á
    "ID!INITIAL!INTO!"                                             Á
    "IDENTIFICATION!INITIALIZE!INVALID!"                           Á
    "IF!INITIATE!INVOKE!"                                          Á
    "IN!INPUT!IS!"                                                 Á
    "INDEX!INPUT-OUTPUT!"                                          Á
    "INDEXED!INSERT!"                                              Á
    /*   J   */                                                    Á
    "JUST!JUSTIFIED!"                                              Á
    /*   K   */                                                    Á
    "KANJI!KEY!"                                                   Á
    /*   L   */                                                    Á
    "LABEL!LIMIT!LINES!"                                           Á
    "LAST!LIMITS!LINKAGE!"                                         Á
    "LEADING!LINAGE!LOCAL-STORAGE!"                                Á
    "LEFT!LINAGE-COUNTER!LOCK!"                                    Á
    "LINE!LENGTH!LOW-VALUE!"                                       Á
    "LESS!LINE-COUNTER!LOW-VALUES!"                                Á
    /*   M   */                                                    Á
    "MEMORY!METHOD!MORE-LABELS!"                                   Á
    "MERGE!METHOD-ID!MOVE!"                                        Á
    "MESSAGE!MODE!MULTIPLE!"                                       Á
    "METACLASS!MODULES!MULTIPLY!"                                  Á
    /*   N   */                                                    Á
    "NATIVE!NO!NUMBER!"                                            Á
    "NATIVE_BINARY!NOT!NUMERIC!"                                   Á
    "NEGATIVE!NULL!NUMERIC-EDITED!"                                Á
    "NEXT!NULLS!"                                                  Á
    /*   O   */                                                    Á
    "OBJECT!ON!OTHER!"                                             Á
    "OBJECT-COMPUTER!OPEN!OUTPUT!"                                 Á
    "OCCURS!OPTIONAL!OVERFLOW!"                                    Á
    "OF!OR!OVERRIDE!"                                              Á
    "OFF!ORDER!"                                                   Á
    "OMITTED!ORGANIZATION!"                                        Á
    /*   P   */                                                    Á
    "PACKED-DECIMAL!PIC!PROCEDURE-POINTER!"                        Á
    "PADDING!PICTURE!PROCEDURES!"                                  Á
    "PAGE!PLUS!PROCEED!"                                           Á
    "PAGE-COUNTER!POINTER!PROCESSING!"                             Á
    "PASSWORD!POSITION!PROGRAM!"                                   Á
    "PERFORM!POSITIVE!PROGRAM-ID!"                                 Á
    "PF!PRINTING!PURGE!"                                           Á
    "PH!PROCEDURE!"                                                Á
    /*   Q   */                                                    Á
    "QUEUE!QUOTE!QUOTES!"                                          Á
    /*   R   */                                                    Á
    "RANDOM!RELATIVE!RESERVE!"                                     Á
    "RD!RELEASE!RESET!"                                            Á
    "READ!RELOAD!RETURN!"                                          Á
    "READY!REMAINDER!RETURN-CODE!"                                 Á
    "RECEIVE!REMOVAL!RETURNING!"                                   Á
    "RECORD!RENAMES!REVERSED!"                                     Á
    "RECORDING!REPLACE!REWIND!"                                    Á
    "RECORDS!REPLACING!REWRITE!"                                   Á
    "RECURSIVE!REPORT!RF!"                                         Á
    "REDEFINES!REPORTING!RH!"                                      Á
    "REEL!REPORTS!RIGHT!"                                          Á
    "REFERENCE!REPOSITORY!ROUNDED!"                                Á
    "REFERENCES!RERUN!RUN!"                                        Á
    /*   S   */                                                    Á
    "SAME!SIGN!STANDARD!"                                          Á
    "SD!SIZE!STANDARD-1!"                                          Á
    "SEARCH!SKIP1!STANDARD-2!"                                     Á
    "SECTION!SKIP2!START!"                                         Á
    "SECURITY!SKIP3!STATUS!"                                       Á
    "SEGMENT!SORT!STOP!"                                           Á
    "SEGMENT-LIMIT!SORT-CONTROL!STRING!"                           Á
    "SELECT!SORT-CORE-SIZE!SUB-QUEUE-1!"                           Á
    "SELF!SORT-FILE-SIZE!SUB-QUEUE-2!"                             Á
    "SEND!SORT-MERGE!SUB-QUEUE-3!"                                 Á
    "SENTENCE!SORT-MESSAGE!SUBTRACT!"                              Á
    "SEPARATE!SORT-MODE-SIZE!SUM!"                                 Á
    "SEQUENCE!SUPER!SORT-RETURN!"                                  Á
    "SEQUENTIAL!SOURCE!SUPPRESS!"                                  Á
    "SERVICE!SOURCE-COMPUTER!SYMBOLIC!"                            Á
    "SET!SYNC!SPACE!"                                              Á
    "SHIFT-IN!SYNCHRONIZED!SPACES!"                                Á
    "SHIFT-OUT!SPECIAL-NAMES!"                                     Á
    /*   T   */                                                    Á
    "TABLE!TEXT!TITLE!"                                            Á
    "THAN!TO!TALLY!"                                               Á
    "TALLYING!THEN!TOP!"                                           Á
    "TAPE!THROUGH!TRACE!"                                          Á
    "TERMINAL!THRU!TRAILING!"                                      Á
    "TERMINATE!TIME!TRUE!"                                         Á
    "TEST!TIMES!TYPE!"                                             Á
    /*   U   */                                                    Á
    "UNIT!UP!USE!"                                                 Á
    "UNSTRING!UPON!USING!"                                         Á
    "UNTIL!USAGE!"                                                 Á
    /*   V   */                                                    Á
    "VALUE!VALUES!VARYING!"                                        Á
    /*   W   */                                                    Á
    "WHEN!WORDS!WRITE-ONLY!"                                       Á
    "WORKING-STORAGE!WHEN-COMPILED!"                               Á
    "WITH!WRITE!"                                                  Á
    /*   X   */                                                    Á
    /*   Y   */                                                    Á
    /*   Z   */                                                    Á
    "ZERO!ZEROES!ZEROS"                                            Á
    /*  END  */                                                    Á
    ")(ÁÁ.! !,!$!'!Á")(.*)";

  /*    _____________________________________________________
      _(                                                     )_
     =_                   S Y M B O L S                       _=
       (_____________________________________________________)
                                                                  */

    /****/ char *ptrnSymbols = "^( !,)*("                          Á
                            "ÁÁ.!"             /*  .        */    Á
                            "ÁÁ+!ÁÁ-!"         /*  +  -     */    Á
                            "ÁÁ(!ÁÁ)!"         /*  (  )     */    Á
                            "ÁÁ*ÁÁ*!ÁÁ*!ÁÁ/!"  /*  ** *  /  */    Á
                            "<=!>=!"           /*  <= >=    */    Á
                            "<!>!=!"           /*  <  >  =  */    Á
                            ":!ÁÁ$"            /*  :  $     */    Á
                            ")(.*)";

  /*    _____________________________________________________
      _(                                                     )_
     =_                   E N D  L I N E                     _=
       (_____________________________________________________)
                                                                  */

    /****/ char *ptrnEndLine = "^(( !,)*)$";

  /*    _____________________________________________________
      _(                                                     )_
     =_                     S P A C E                        _=
       (_____________________________________________________)
                                                                  */

    /****/ char  *ptrnSpace = "(^( !,)+)";


  /*    ______________________________
      _(                              )_
     =_    SPECIAL REGISTER KEYWORD    _=
       (______________________________)
                                                                  */

    /****/ char *ptrnSpclReg  = "^( !,)*"                           Á
                               "(ADDRESS!"                         Á
                               "DEBUG-ITEM!DEBUG-LINE!DEBUG-NAME!" Á
                               "LENGTH!RETURN-CODE!SORT-RETURN!"   Á
                               "WHEN-COMPILED!TALLY)"              Á
                               "(ÁÁ.! !,!$!'!Á")(.*)";

  /*    ______________________________
      _(                              )_
     =_  FIGURATIVE CONSTANTS KEYWORD  _=
       (______________________________)
                                                                  */

    /****/ char *ptrnFgrtvConst = "^( !,)*("                       Á
                                 "ALL!"                            Á
                                 "ZERO!ZEROS!ZEROES!"              Á
                                 "SPACE!SPACES!"                   Á
                                 "HIGH-VALUE!HIGH-VALUES!"         Á
                                 "LOW-VALUE!LOW-VALUES!"           Á
                                 "QUOTE!QUOTES"                    Á
                                 ")(ÁÁ.! !,!$!'!Á")(.*)";

  /*    _____________________________
      _(                             )_
     =_        NUMERIC LITERAL        _=
       (_____________________________)
                                                                  */

    /****/ char *ptrnNumeric = "^("                                  Á
                              "ZERO!ZEROS!ZEROES!"                  Á
                              "(›ÁÁ+ÁÁ-~?›0-9~+)!"       /* Intgr */Á
                              "(›ÁÁ+ÁÁ-~?›0-9~*,›0-9~+)" /* Decim */Á
                              ")$";

  /*    _____________________________
      _(                             )_
     =_        QUOTED LITERAL         _=
       (_____________________________)
                                                                  */

    /****/ char *ptrnQuoted = "^("                                    Á
                             "('(›^'~!'')*')!"            /*  '.' */ Á
                             "(Á"(›^Á"~!Á"Á")*Á")!"       /*  "." */ Á
                             "(›Xx~›'~›0-9A-Fa-f~+›'~)!"  /* x'.' */ Á
                             "(›Xx~›Á"~›0-9A-Fa-f~+›Á"~)" /* x"." */ Á
                              ")$";

  /*    _____________________________
      _(                             )_
     =_    SINGLE QUOTED LITERAL      _=
       (_____________________________)
                                                                  */

    /****/ char *ptrnSQuoted = "^("                                  Á
                             "('(›^'~!'')*')!"            /*  '.' */ Á
                             "(›Xx~›'~›0-9A-Fa-f~+›'~)"  /* x'.' */ Á
                              ")$";

  /*    _____________________________
      _(                             )_
     =_    DOUBLE QUOTED LITERAL      _=
       (_____________________________)
                                                                  */

    /****/ char *ptrnDQuoted = "^("                                   Á
                             "(Á"(›^Á"~!Á"Á")*Á")!"       /*  "." */ Á
                             "(›Xx~›Á"~›0-9A-Fa-f~+›Á"~)" /* x"." */ Á
                              ")$";

  /*    _____________________________
      _(                             )_
     =_      HEXADECIMAL LITERAL      _=
       (_____________________________)
                                                                  */

    /****/ char *ptrnHex     = "^("                                   Á
                             "(›Xx~›'~›0-9A-Fa-f~+›'~)!"  /* x'.' */ Á
                             "(›Xx~›Á"~›0-9A-Fa-f~+›Á"~)" /* x"." */ Á
                              ")$";

  /*    _____________________________
      _(                             )_
     =_      ALPHANUMERIC LITERAL     _=
       (_____________________________)
                                                                  */

    /****/ char *ptrnAlphanum = "^("                                  Á
                             "('(›^'~!'')*')!"            /*  '.' */ Á
                             "(Á"(›^Á"~!Á"Á")*Á")"       /*  "." */ Á
                              ")$";

  /*    _____________________________
      _(                             )_
     =_        INTEGER LITERAL        _=
       (_____________________________)
                                                                  */

    /****/ char *ptrnIntgr    = "^("                                 Á
                             "(›ÁÁ+ÁÁ-~?›0-9~+)"          /*  987 */ Á
                              ")$";

  /*    _____________________________
      _(                             )_
     =_        DECIMAL LITERAL        _=
       (_____________________________)
                                                                  */

    /****/ char *ptrnDecim    = "^("                                Á
                             "(›ÁÁ+ÁÁ-~?›0-9~*,›0-9~+)"             Á
                              ")$";

  /*    _____________________________
      _(                             )_
     =_      UNSIGNED NUMERIC         _=
       (_____________________________)
                                                                  */

    /****/ char *ptrnUnsigned = "^("                               Á
                             "(›0-9~+)!"                /* 987 */  Á
                             "(›0-9~*,›0-9~+)"          /* 9,7 */  Á
                              ")$";

  /*    _____________________________
      _(                             )_
     =_      POSITIVE NUMERIC         _=
       (_____________________________)
                                                                  */

    /****/ char *ptrnPositive = "^("                               Á
                             "(ÁÁ+›0-9~+)!"             /* +987 */ Á
                             "(ÁÁ+›0-9~*,›0-9~+)"       /* +9,7 */ Á
                              ")$";

  /*    _____________________________
      _(                             )_
     =_      NEGATIVE NUMERIC         _=
       (_____________________________)
                                                                  */

    /****/ char *ptrnNegative = "^("                                 Á
                             "(ÁÁ-›0-9~+)!"             /* -987 */ Á
                             "(ÁÁ-›0-9~*,›0-9~+)"       /* -9,7 */ Á
                              ")$";

  /*    _____________________________
      _(                             )_
     =_         LEVEL NUMBER          _=
       (_____________________________)
                                                                  */

    /****/ char *ptrnLvlNum = "^("                                   Á
                             "(›0~?›1-9~!›1-4~›0-9~!66!77!88)"     Á
                              ")$";

  /*    _____________________________
      _(                             )_
     =_      RELATIONAL OPERATOR      _=
       (_____________________________)
                                                                  */

    /****/ char *ptrnRelOp  = "^("                                   Á
                             "(<!>!<=!>=!=)"                       Á
                              ")$";

  /*    _____________________________
      _(                             )_
     =_      ARITHMITIC OPERATOR      _=
       (_____________________________)
                                                                  */

    /****/ char *ptrnAritOp  = "^("                                  Á
                              "ÁÁ+!ÁÁ-!"         /*  +  -     */   Á
                              "ÁÁ(!ÁÁ)!"         /*  (  )     */   Á
                              "ÁÁ*ÁÁ*!ÁÁ*!ÁÁ/"  /*  ** *  /  */   Á
                              ")$";

  /*
    char       *ptrnLiter2 = "^( !,)*"                              Á
                            "(Á"(›^Á"~!Á"Á")*Á")"                   Á
                            "(›^Á"~!$)(.*)";
  */
  /*-----------------------------------*/
  /* Pattern pour HEXA Literal X'FF'   */
  /*-----------------------------------*/
  /*char       *ptrnHexL1  = "^( !,)*"                              Á
                            "(›Xx~›Á"~›0-9A-Fa-f~+›Á"~)"            Á
                            "(›^Á"~!$)(.*)";

    char       *ptrnHexL2  = "^( !,)*"                              Á
                            "(›Xx~›'~›0-9A-Fa-f~+›'~)"              Á
                            "(›^'~!$)(.*)";
  */
  /*-----------------------------*/
  /* Pattern pour Integer        */
  /*-----------------------------*/
  /*char       *ptrnIntgr = "^( !,)*"                             Á
                            "(›ÁÁ+ÁÁ-~?›0-9~+)"                   Á
                            "(.)(.*)";
  */
  /*-----------------------------*/
  /* Pattern pour Level Number   */
  /*-----------------------------*/
  /*char       *ptrnLvlnum = "(›0~?›1-9~!›1-4~›0-9~!77)";

  */
  /*-----------------------------*/
  /* Pattern pour Level 66       */
  /*-----------------------------*/
  /*char       *ptrnLvl66  = "66";
  */
  /*-----------------------------*/
  /* Pattern pour Level 88       */
  /*-----------------------------*/
  /*char       *ptrnLvl88  = "88";
  */
  /*-----------------------------*/
  /* Pattern pour Decimal        */
  /*-----------------------------*/
  /*char       *ptrnDecim  = "^( !,)*"                             Á
                            "(›ÁÁ+ÁÁ-~?›0-9~*,›0-9~+)"             Á
                            "(.)(.*)";
  */
  /*-------------------------------*/
  /* Pattern pour Unsigned integer */
  /*-------------------------------*/
  /*char       *ptrnUintgr  = "^(›0-9~+)$";
  */

  /*---------------------------------------------------------------*/
  /*---------------------------------------------------------------*/
  /*---------------------------------------------------------------*/

    int         rc=0;
    int         i=0;
    int         j=0;
    size_t      nmatch = NB_MATCH_MAX;
    regmatch_t  pmatch›NB_MATCH_MAX~;
    char        buffer›100~;
    char        str›480~;

    static int  rets_len =0;
    static char rets_data›480~="";

    char        args›480~="";

    strcpy(args,ln_8_72);

  /*---------------------------------------------------------------*/
  /*---------------------------------------------------------------*/
  /*---------------------------------------------------------------*/

  /*---------------------------------------------------------------*/
  /* Ordre des REGEX                                               */
  /*---------------------------------------------------------------*/
  /* 1  - Keyword                                                  */
  /* 10 - Special registers                                        */
  /* 101- Figurative constants                                     */
  /* 11 - Hexa Literal1 & Hexa Literal2                            */
  /* 2  - Identifier                                               */
  /* 3  - Literal1 & Literal2                                      */
  /* 31 - Decimal                                                  */
  /* 32 - Integer                                                  */
  /* 4  - Period                                                   */
  /*      & plus minus equal expon divid multp Lbrack Rbrack colon */
  /* 5  - EndLine                                                  */
  /* 6  - Error                                                    */
  /*---------------------------------------------------------------*/
    /* Pointer Array for pregs order for type*/
    /****/ regex_npp   pregs ›NB_REGEX_MAX~;

    int nb_regex_for_type;

    /* Default pregs order (empty context) */

    pregs›j~.name ="KEYWORD";
    pregs›j~.ptrn =ptrnKeywoAll;
    pregs›j~.preg =&pregKeywoAll;
    j++;
    pregs›j~.name ="LITERAL";
    pregs›j~.ptrn =ptrnLiterQuot;
    pregs›j~.preg =&pregLiterQuot;
    j++;
    pregs›j~.name ="LITERAL";
    pregs›j~.ptrn =ptrnLiterNum;
    pregs›j~.preg =&pregLiterNum;
    j++;
    pregs›j~.name ="IDENTIFIER";
    pregs›j~.ptrn =ptrnIdent;
    pregs›j~.preg =&pregIdent;
    j++;
    pregs›j~.name ="SYMBOL";
    pregs›j~.ptrn =ptrnSymbols;
    pregs›j~.preg =&pregSymbols;
    j++;
    pregs›j~.name ="ENDLINE";
    pregs›j~.ptrn =ptrnEndLine;
    pregs›j~.preg =&pregEndLine;
    j++;

    /* Space ??
    pregs›j~.name ="SPACE";
    pregs›j~.ptrn =ptrnSpace;
    pregs›j~.preg =&pregSpace;
    j++; */

 /* pregs›j~.name ="KEYWORD";
    pregs›j~.ptrn =ptrnKeywoAll;
    pregs›j~.preg =&pregKeywoAll;
    j++;
    pregs›j~.name ="SPECIAL REGISTER";
    pregs›j~.ptrn =ptrnSpclReg;
    pregs›j~.preg =&pregSpclReg;
    j++;
    pregs›j~.name ="FIGURATIVE CONST";
    pregs›j~.ptrn =ptrnFgrtvConst;
    pregs›j~.preg =&pregFgrtvConst;
    j++;
    pregs›j~.name ="HEXLITERAL";
    pregs›j~.ptrn =ptrnHexL1;
    pregs›j~.preg =&pregHexL1;
    j++;
    pregs›j~.name ="HEXLITERAL";
    pregs›j~.ptrn =ptrnHexL2;
    pregs›j~.preg =&pregHexL2;
    j++;
    pregs›j~.name ="IDENTIFIER";
    pregs›j~.ptrn =ptrnIdent;
    pregs›j~.preg =&pregIdent;
    j++;
    pregs›j~.name ="LITERAL";
    pregs›j~.ptrn =ptrnLiter1;
    pregs›j~.preg =&pregLiter1;
    j++;
    pregs›j~.name ="LITERAL";
    pregs›j~.ptrn =ptrnLiter2;
    pregs›j~.preg =&pregLiter2;
    j++;
    pregs›j~.name ="DECIMAL";
    pregs›j~.ptrn =ptrnDecim;
    pregs›j~.preg =&pregDecim;
    j++;
    pregs›j~.name ="INTEGER";
    pregs›j~.ptrn =ptrnIntgr;
    pregs›j~.preg =&pregIntgr;
    j++;
    pregs›j~.name ="SYMBOL";
    pregs›j~.ptrn =ptrnSymbols;
    pregs›j~.preg =&pregSymbols;
    j++;
    pregs›j~.name="ENDLINE";
    pregs›j~.ptrn=ptrnEndLine;
    pregs›j~.preg=&pregEndLine;
    j++;
  */
    nb_regex_for_type = j;

  /*---------------------------------------------------------------*/
  /*-------------- ! Context Sensitive Lexer ! --------------------*/
  /*---------------------------------------------------------------*/
  /* If clause data_pic_chars => add PICCHARS as the first regex   */
  /*---------------------------------------------------------------*/
  /*                          => next is the pattern for space     */
  /*---------------------------------------------------------------*/

    if((strcmp(_context.clause,"data_pic_chars"))==0)È

       j = 0;

       pregs›j~.name ="PICCHARS";
       pregs›j~.ptrn =ptrnPicChars;
       pregs›j~.preg =&pregPicChars;
       j++;
       pregs›j~.name ="SPACE";
       pregs›j~.ptrn =ptrnSpace;
       pregs›j~.preg =&pregSpace;
       j++;
       pregs›j~.name ="SYMBOL"; /* ?? symbol ici */
       pregs›j~.ptrn =ptrnSymbols;
       pregs›j~.preg =&pregSymbols;
       j++;
       pregs›j~.name ="KEYWORD";
       pregs›j~.ptrn =ptrnKeywoAll;
       pregs›j~.preg =&pregKeywoAll;
       j++;
       pregs›j~.name ="LITERAL";
       pregs›j~.ptrn =ptrnLiterQuot;
       pregs›j~.preg =&pregLiterQuot;
       j++;
       pregs›j~.name ="LITERAL";
       pregs›j~.ptrn =ptrnLiterNum;
       pregs›j~.preg =&pregLiterNum;
       j++;
       pregs›j~.name ="IDENTIFIER";
       pregs›j~.ptrn =ptrnIdent;
       pregs›j~.preg =&pregIdent;
       j++;
       pregs›j~.name ="ENDLINE";
       pregs›j~.ptrn =ptrnEndLine;
       pregs›j~.preg =&pregEndLine;
       j++;
/*
       pregs›j~.name ="PICCHARS";
       pregs›j~.ptrn =ptrnPicChars;
       pregs›j~.preg =&pregPicChars;
       j++;
*/   /*pregs›j~.name ="SYMBOL";
       pregs›j~.ptrn =ptrnPerio;
       pregs›j~.preg =&pregPerio;
       j++;*/
/*     pregs›j~.name ="SYMBOL";
       pregs›j~.ptrn =ptrnSymbols;
       pregs›j~.preg =&pregSymbols;
       j++;
       pregs›j~.name="SPACE";
       pregs›j~.ptrn=ptrnSpace;
       pregs›j~.preg=&pregSpace;
       j++;
       pregs›j~.name ="KEYWORD";
       pregs›j~.ptrn =ptrnKeywoAll;
       pregs›j~.preg =&pregKeywoAll;
       j++;
       pregs›j~.name ="SPECIAL REGISTER";
       pregs›j~.ptrn =ptrnSpclReg;
       pregs›j~.preg =&pregSpclReg;
       j++;
       pregs›j~.name ="FIGURATIVE CONST";
       pregs›j~.ptrn =ptrnFgrtvConst;
       pregs›j~.preg =&pregFgrtvConst;
       j++;
       pregs›j~.name ="HEXLITERAL";
       pregs›j~.ptrn =ptrnHexL1;
       pregs›j~.preg =&pregHexL1;
       j++;
       pregs›j~.name ="HEXLITERAL";
       pregs›j~.ptrn =ptrnHexL2;
       pregs›j~.preg =&pregHexL2;
       j++;
       pregs›j~.name ="IDENTIFIER";
       pregs›j~.ptrn =ptrnIdent;
       pregs›j~.preg =&pregIdent;
       j++;
       pregs›j~.name ="LITERAL";
       pregs›j~.ptrn =ptrnLiter1;
       pregs›j~.preg =&pregLiter1;
       j++;
       pregs›j~.name ="LITERAL";
       pregs›j~.ptrn =ptrnLiter2;
       pregs›j~.preg =&pregLiter2;
       j++;
       pregs›j~.name ="DECIMAL";
       pregs›j~.ptrn =ptrnDecim;
       pregs›j~.preg =&pregDecim;
       j++;
       pregs›j~.name ="INTEGER";
       pregs›j~.ptrn =ptrnIntgr;
       pregs›j~.preg =&pregIntgr;
       j++;
       pregs›j~.name="ENDLINE";
       pregs›j~.ptrn=ptrnEndLine;
       pregs›j~.preg=&pregEndLine;
       j++;
 */    nb_regex_for_type = j;
    Ë

  /* Additional Regex for token attributes   */
  /****/ regex_npp   pregs_attr ›NB_REGEX_MAX~;

  int nb_regex_for_attr;
  j =0;

  pregs_attr›j~.name ="SPECIAL REGISTER";
  pregs_attr›j~.ptrn =ptrnSpclReg;
  pregs_attr›j~.preg =&pregSpclReg;
  j++;
  pregs_attr›j~.name ="FIGURATIVE CONST";
  pregs_attr›j~.ptrn =ptrnFgrtvConst;
  pregs_attr›j~.preg =&pregFgrtvConst;
  j++;
  pregs_attr›j~.name ="NUMERIC";
  pregs_attr›j~.ptrn =ptrnNumeric;
  pregs_attr›j~.preg =&pregNumeric;
  j++;
  pregs_attr›j~.name ="QUOTED";
  pregs_attr›j~.ptrn =ptrnQuoted;
  pregs_attr›j~.preg =&pregQuoted;
  j++;
  pregs_attr›j~.name ="SINGLE QUOTE";
  pregs_attr›j~.ptrn =ptrnSQuoted;
  pregs_attr›j~.preg =&pregSQuoted;
  j++;
  pregs_attr›j~.name ="DOUBLE QUOTED";
  pregs_attr›j~.ptrn =ptrnDQuoted;
  pregs_attr›j~.preg =&pregDQuoted;
  j++;
  pregs_attr›j~.name ="HEX";
  pregs_attr›j~.ptrn =ptrnHex;
  pregs_attr›j~.preg =&pregHex;
  j++;
  pregs_attr›j~.name ="ALPHANUMERIC";
  pregs_attr›j~.ptrn =ptrnAlphanum;
  pregs_attr›j~.preg =&pregAlphanum;
  j++;
  pregs_attr›j~.name ="INTEGER";
  pregs_attr›j~.ptrn =ptrnIntgr;
  pregs_attr›j~.preg =&pregIntgr;
  j++;
  pregs_attr›j~.name ="DECIMAL";
  pregs_attr›j~.ptrn =ptrnDecim;
  pregs_attr›j~.preg =&pregDecim;
  j++;
  pregs_attr›j~.name ="UNSIGNED";
  pregs_attr›j~.ptrn =ptrnUnsigned;
  pregs_attr›j~.preg =&pregUnsigned;
  j++;
  pregs_attr›j~.name ="POSITIVE";
  pregs_attr›j~.ptrn =ptrnPositive;
  pregs_attr›j~.preg =&pregPositive;
  j++;
  pregs_attr›j~.name ="NEGATIVE";
  pregs_attr›j~.ptrn =ptrnNegative;
  pregs_attr›j~.preg =&pregNegative;
  j++;
  pregs_attr›j~.name ="LEVEL NUMBER";
  pregs_attr›j~.ptrn =ptrnLvlNum;
  pregs_attr›j~.preg =&pregLvlnum;
  j++;
  pregs_attr›j~.name ="RELATIONAL OP";
  pregs_attr›j~.ptrn =ptrnRelOp;
  pregs_attr›j~.preg =&pregRelOp;
  j++;
  pregs_attr›j~.name ="ARITHMITIC OP";
  pregs_attr›j~.ptrn =ptrnAritOp;
  pregs_attr›j~.preg =&pregAritOp;
  j++;

  nb_regex_for_attr = j;

  /*
  regex_npp   reg_lvlnum;
  regex_npp   reg_lvl66;
  regex_npp   reg_lvl88;
  regex_npp   reg_uintgr;

  reg_lvlnum.name="LVLNUM";
  reg_lvlnum.ptrn=ptrnLvlnum;
  reg_lvlnum.preg=&pregLvlnum;

  reg_lvl66.name="LVL66";
  reg_lvl66.ptrn=ptrnLvl66;
  reg_lvl66.preg=&pregLvl66;

  reg_lvl88.name="LVL88";
  reg_lvl88.ptrn=ptrnLvl88;
  reg_lvl88.preg=&pregLvl88;

  reg_uintgr.name="UINTEGER";
  reg_uintgr.ptrn=ptrnUintgr;
  reg_uintgr.preg=&pregUintgr;

  if(ß(compil_regexp(reg_lvlnum))) return _ret;
  if(ß(compil_regexp(reg_lvl66))) return _ret;
  if(ß(compil_regexp(reg_lvl88))) return _ret;
  if(ß(compil_regexp(reg_uintgr))) return _ret;
  */

  /*---------------------------------------------------------------*/
  /*-------------- ! Compilation des Regex  ! ---------------------*/
  /*---------------------------------------------------------------*/

     /* _______________________________
      _(                               )_
     =_  COMPILE REGEX FOR TOKEN TYPE   _=
       (_______________________________)*/


 /* debug_2("regcomp_type_done (%d) Án",regcomp_type_done);

    if(ß(regcomp_type_done)) È
 */
       i=0;
       while ((i < nb_regex_for_type) && (compil_regexp(pregs›i~)))
       È
        //debug_3("Compilation regex (%s) reussie Án",pregs›i~.name);
          i++;
       Ë

       /* Sortie prÈmature : erreur compilation */
       if (i < nb_regex_for_type) exit(EXIT_FAILURE);
       else regcomp_type_done = 1;
 /* Ë
 */
     /* ____________________________________
      _(                                    )_
     =_  COMPILE REGEX FOR TOKEN ATTRIBUTES  _=
       (____________________________________)*/


 /* debug_2("regcomp_attr_done (%d) Án",regcomp_attr_done);

    if(ß(regcomp_attr_done)) È
 */
       i=0;
       while ((i < nb_regex_for_attr) && (compil_regexp(pregs_attr›i~)))
       È
        //debug_3("Compilation regex (%s) reussie Án",
        //                                 pregs_attr›i~.name);
          i++;
       Ë


       /* Sortie prÈmature : erreur compilation */
       if (i < nb_regex_for_attr) exit(EXIT_FAILURE);
       else regcomp_attr_done = 1;
  /*
    Ë
  */
     /* _____________________________
      _(                             )_
     =_  MATCH REGEX FOR TOKEN TYPE   _=
       (_____________________________)*/

    i =0;
    while ((i < nb_regex_for_type) &&
          /* patch horrible dans condition while */
         (((rc =regexec(pregs›i~.preg, args, nmatch, pmatch, 0)) ß= 0)
          /* continuer la recherche si on trouve picchar et   */
          /* son dernier caractere est le point et le prochain*/
          /* caractere nest pas le point piouf .. */
        /*
        !!(((rc =regexec(pregs›i~.preg, args, nmatch, pmatch, 0)) == 0)
        && (strcmp(pregs›i~.name,"PICCHARS")==0)    picchar
        && (*(args+pmatch›2~.rm_eo-1)=='.')    dernier char est '.'
        && ((pmatch›2~.rm_eo)<=strlen(args))    pas fin de args
        && (*(args+(pmatch›2~.rm_eo))ß='.'))
        */
          )) È
        /*
        if(strcmp(pregs›i~.name,"PICCHARS")==0) È

        debug_2("this line should not be printed, otherwise it's bug");
        debug_2("rc (%d)Án",rc);
        debug_2("Ánpregs.name            (%s)Án",pregs›i~.name);
        debug_2("args+pmatch2.rm_eo-1  (%d)Án",args+pmatch›2~.rm_eo-1);
        debug_2("*args+pmatch2.rm_eo-1 (%c)Án",
                                          *(args+pmatch›2~.rm_eo-1));
        debug_2("strlen(args)          (%d)Án",strlen(args));
        debug_2("pmatch2.rm_eo         (%d)Án",(pmatch›2~.rm_eo));
        debug_2("*(args+(pmatch2.rm_eo)(%c)Án",
                                          *(args+(pmatch›2~.rm_eo)));
        */
        /* Display matched sub-expression */
        /* affich_subexpr(pmatch,args); */
     /* Ë */
    // affich_fail_match(rc,args,pregs›i~.name,pregs›i~.preg);
       i++;
    Ë

    /* match found */
    if (i < nb_regex_for_type) È

        if(strcmp(pregs›i~.name,"PICCHARS")==0) È
        /*
        debug_2("pregs.name            (%s)Án",pregs›i~.name);
        debug_2("args+pmatch2.rm_eo-1  (%d)Án",args+pmatch›2~.rm_eo-1);
        debug_2("*args+pmatch2.rm_eo-1 (%c)Án",
                                          *(args+pmatch›2~.rm_eo-1));
        debug_2("strlen(args)          (%d)Án",strlen(args));
        debug_2("pmatch2.rm_eo         (%d)Án",(pmatch›2~.rm_eo));
        debug_2("*(args+(pmatch2.rm_eo)(%c)Án",
                                          *(args+(pmatch›2~.rm_eo)));
        */
        /* Display matched sub-expression */
        /* affich_subexpr(pmatch,args);
        */
        /* Patch pour annulation context une fois picchar lu */
        erase_context();
       Ë


        /* extraire token vers var tmp : str */
        sprintf(str,"%.*s",pmatch›2~.rm_eo - pmatch›2~.rm_so,
                  args+pmatch›2~.rm_so);

        /* reduire args */
        /*
        sprintf(args,"%.*s",pmatch›3~.rm_eo - pmatch›3~.rm_so,
                  args+pmatch›3~.rm_so); */

        reduction_len  = 65 - strlen(args);

        sprintf(args,"%.*s",((strlen(args))-(pmatch›2~.rm_eo))
                 ,args+(pmatch›2~.rm_eo));

        _ret.tkn_colnum = pmatch›2~.rm_so + 1 + reduction_len;
        _ret.tkn_len    = pmatch›2~.rm_eo - pmatch›2~.rm_so;

      /*printf("tokenizer     :strlen(args) (%d) reduction_len (%d)" Á
        " tkn_colnum (%d) pmatch›2~.rm_so (%d) tkn_len (%d) Án",
        strlen(args),reduction_len,_ret.tkn_colnum,pmatch›2~.rm_so,
        _ret.tkn_len);
      */
        /* concat str avec rets */
        strcat(rets_data,pregs›i~.name);
        strcat(rets_data,";;");
        strcat(rets_data,str);
        strcat(rets_data,";;");
        char* temp="Á0";
        sprintf(temp, "%d", _ret.tkn_colnum);
        strcat(rets_data,temp);
        strcat(rets_data,";;");

        _ret.tkn_type   = pregs›i~.name;
        _ret.tkn_val    = str;


        /*
        if ((rc =regexec(reg_lvlnum.preg,str,nmatch,pmatch,0)) == 0)È
            _ret.tkn_attr›0~ = "LVLNUM";
            printf ("LVLNUM found Án");
        Ë
        if ((rc =regexec(reg_lvl66.preg,str,nmatch,pmatch,0)) == 0)È
            _ret.tkn_attr›0~= "LVL66";
            printf ("LVL66  found Án");
        Ë
        if ((rc =regexec(reg_lvl88.preg,str,nmatch,pmatch,0)) == 0)È
            _ret.tkn_attr›0~= "LVL88";
            printf ("LVL88  found Án");
        Ë
        if ((rc =regexec(reg_uintgr.preg,str,nmatch,pmatch,0)) == 0)È
            _ret.tkn_attr›1~= "UINTEGER";
            printf ("UINTEGER  found Án");
        Ë */
    Ë

    /* no match found */
    else È

       strcpy(rets_data,"ERROR;;");
       _ret.tkn_type = "ERROR";
       _ret.tkn_val = "ERROR";

       printf("ERROR, args :%s",args);
    Ë

     /* ____________________________________
      _(                                    )_
     =_  COMPILE REGEX FOR TOKEN ATTRIBUTES  _=
       (____________________________________)*/

    i =0;
    j =0;
    _ret.tkn_attr_len =0;
    while ((i < nb_regex_for_attr) &&
           (rc=strcmp(_ret.tkn_val,"ERROR"))ß=0)
    È
       if((rc =regexec(pregs_attr›i~.preg,str,nmatch,pmatch,0)) == 0)
       È
          /* Display matched sub-expression */
        /*affich_subexpr(pmatch,str); */
          _ret.tkn_attr›j~=pregs_attr›i~.name;
          j++;
       Ë
       else
       È
        /*affich_fail_match(rc,args,pregs›i~.name,pregs›i~.preg);*/
       Ë

       i++;
    Ë
    _ret.tkn_attr_len=j;

    rets_len = strlen(rets_data);
    /*
    printf("Án");
    printf("*----------------------------------------------*Án");
    printf("*--------------  END LEXERCOB  ----------------*Án");
    printf("*----------------------------------------------*Án");
    printf("*   Rets length : %d Án", rets_len);
    printf("*   Rets data   :'%s'Án", rets_data);
    printf("*----------------------------------------------*Án");
    */

    debug_2("*----------------------------------------------*Án");
    debug_2("*--------------   TOKENIZER    ----------------*Án");
    debug_2("*----------------------------------------------*Án");
    debug_2("*   Token Value : %s Án", _ret.tkn_val);
    debug_2("*   Token Type  : %s Án", _ret.tkn_type);
    debug_2("*   Token Line  : %d Án", _ret.tkn_lnnum);
    debug_2("*   Token Coln  : %d Án", _ret.tkn_colnum);
    debug_2("*   Token Length: %d Án", _ret.tkn_len);
    debug_2("*   Token attrs : %d Án", _ret.tkn_attr_len);
    debug_2("*----------------------------------------------*Án");

    i =0;
    while (i < _ret.tkn_attr_len) È
       debug_2("*   Token Attr  : %s Án", _ret.tkn_attr›i~);
       i++;
    Ë
    debug_2("*----------------------------------------------*Án");


    for(i=0;i<nb_regex_for_type;i++)
        regfree(pregs›i~.preg);

    for(i=0;i<nb_regex_for_attr;i++)
        regfree(pregs_attr›i~.preg);

    /*
    regfree(&pregKeywo);
    regfree(&pregIdent);
    regfree(&pregPerio);
    regfree(&pregLiter1);
    regfree(&pregLiter2);
    regfree(&pregHexL1);
    regfree(&pregHexL2);
    regfree(&pregKeywoAll);
    regfree(&pregLBrack);
    regfree(&pregRBrack);
    regfree(&pregPlus);
    regfree(&pregMinus);
    regfree(&pregMultp);
    regfree(&pregDivid);
    regfree(&pregExpon);
    regfree(&pregEqual);
    regfree(&pregColon);
    regfree(&pregIntgr);
    regfree(&pregDecim);

    printf("tokenizer()   : ");
    printf("Token Value <%s> Token Type   <%s> Án",
            _ret.tkn_val,_ret.tkn_type);
    */
    /*
    printf("tokenizer()   : ");
    printf("args        : <%s>Án",args);
    printf("len args    : <%d>Án",strlen(args));
    */
    strcpy(ln_8_72,args);

    /*
    printf("tokenizer()   : ");
    printf("ln_8_72     : <%s>Án",ln_8_72);
    printf("len ln_8_72 : <%d>Án",strlen(ln_8_72));
    */
    return _ret;

Ë


int affich_subexpr(regmatch_t pmatch›~,char args›~)È

   int i =0;

   printf("Whole expression :<");
   printf("%s",args);
   printf(">Án");

   for (i=1;i<NB_MATCH_MAX;i++)È

      printf("ÁnSub-expression %d, a matched sub-string " Á
             "Á"%.*sÁ" found at position %d to %d.Án ",
      i, pmatch›i~.rm_eo - pmatch›i~.rm_so,
      args+pmatch›i~.rm_so,pmatch›i~.rm_so,
      pmatch›i~.rm_eo - 1);

   Ë
   printf("Án");

   return 1;
Ë

int affich_fail_match(int rc,char args›~,char* ptrn,regex_t* preg)È

   char buffer›100~;

   regerror(rc, preg, buffer, 100);

   printf("failed to matchÁn'%s'withÁn'%s',ÁnRC :%d, '%s'Án"
             ,args, ptrn, rc, buffer);

   return 1;
Ë

int compil_regexp(regex_npp _regex_npp)È

    int  rc =0;
    char buffer›100~;

    /* Compiler la REGEXP pour ptrn dans preg */

    if ((rc = regcomp(_regex_npp.preg, _regex_npp.ptrn,
         REG_ICASE!REG_EXTENDED)) ß= 0)
    È
       regerror(rc, _regex_npp.preg, buffer, 100);
       printf("regcomp(%s) fail RC (%d : '%s')Án",_regex_npp.name,
              rc, buffer);
       return 0;
    Ë
    /* printf("regcomp for (%s) succesful Án",_regex_npp.name);*/

    return 1;
Ë

int
erase_context()È

    debug_2("Erasing Context ... OKÁn");
    _context.division ="";
    _context.section  ="";
    _context.clause   ="";
    _context.keyword  ="";
    _context.other    ="";

    return  1;

Ë
