£ifndef REXXCOM_H_INCLUDED
£define REXXCOM_H_INCLUDED

£pragma runopts(PLIST(OS))

£define DS_NAME_LEN 45    // inclut car pour Á0
£define NB_INC_PDS  20
£define NB_OPTIONS  20
£define NB_RESULTS  500


int getArgsRexx();
int setCurrLnNum(int);
struct _srcLine* getSource(char* src_file,int current_line);
struct _srcLine* getCurrSrcLine(struct _srcLine* src_list,int cursl,
                                                          int cursc);
int break_str_space(char *line,char words›~›DS_NAME_LEN~,int maxWords);
void setCurrLnStrart();

typedef struct _editLine È

  char   funct;     // 1  char
  char*  line_num;  // 6  char
  char*  coln_num;  // 6  char
  char*  line_nbr;  // 6  char
  char*  src_line;  // 81 char

Ë _editLine;

typedef struct _srcLine È
  char   value›81~;
  int    num_file;
  int    num_all;
  char   file›DS_NAME_LEN~;
  struct _srcLine *next;
Ë _srcLine;

extern int        argc;                /* nombre d'arguments  */
extern int        cursl;               /* position ligne   de cursor */
extern int        cursc;               /* position colonne de cursor */
extern char       src_file›DS_NAME_LEN~;
extern char       inc_pds›NB_INC_PDS~›DS_NAME_LEN~;
extern char       options›NB_OPTIONS~›DS_NAME_LEN~;
extern int        main_ret;            /* zone retour                */
extern _editLine  result›NB_RESULTS~;  /* zone retour                */

//extern int     curr_ln_num;         /* current line being parsed  */
extern _srcLine   *src_list;           /* source                     */
extern _srcLine   *curr_src_line;      /* source                     */
£endif
/* REXXCOM_H_INCLUDED */
