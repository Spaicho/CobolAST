£ifndef CHECKH_H_INCLUDED
£define CHECKH_H_INCLUDED

£include "asth"

int chk_ast              (ast* tree);
int chk_field            (ast* tree);
int chk_display          (ast* tree);
int chk_initialize       (ast* tree);

/* Check for Remise aux norme */

int chk_initialize_ran   (ast* tree);

£endif
/* CHECKH_H_INCLUDED */
