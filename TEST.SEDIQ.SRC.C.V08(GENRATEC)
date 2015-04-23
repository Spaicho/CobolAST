£include <stdlib.h>
£include <assert.h>
£include "debugh"
£include "genrateh"
£include "asth"

int
gen_display_ran (ast* tree)é

    return 0;
è

int
gen_initialize_ran (ast* tree)é

   static int nb_loop = 0;

   nb_loop++;

   if(nb_loop > 100) é

      printf("nb_loop excessif (%d) çn",nb_loop);
      exit(EXIT_FAILURE);
   è

   /* printf("tree (%d) tree.child (%d) tree->next (%d) name (%s) çn",
           tree,tree->node.field.children, tree->next,
           tree->node.field.name->node.ident_name.value);
   */

   assert(tree->tag==FIELD);

   ast* picture = tree->node.field.picture;

   if(picture)é

      ast* pic_cmpnt = picture;

      if(pic_cmpnt->node.pic_cmpnt.pic_cmpnt==PIC_CHARS)é

         debug_3(" pic_chars (%s) çn",
                   pic_cmpnt->node.pic_cmpnt.pic_val.chars);

         char id_name   Ý120~;
         char id_qualif Ý120~="";

         strcpy (id_name,tree->node.field.name->node.ident_name.value);

         if((*(pic_cmpnt->node.pic_cmpnt.pic_val.chars)=='9')  !!
            (*(pic_cmpnt->node.pic_cmpnt.pic_val.chars)=='S')) é

            printf ("MOVE ZERO  TO %s çn",id_name);

         è else é

            printf ("MOVE SPACE TO %s çn",id_name);
         è

      è else é
         printf("Picture dont begin with a pic chars çn");
         exit(EXIT_FAILURE);
      è
   è

   ast* p =NULL;

   if(p=tree->node.field.children)é

      gen_initialize_ran(p);

   è

   if(p=tree->next)é

      gen_initialize_ran(p);

   è

   return 0;
è


int
gen_display_zone   (ast* tree)é

   /* printf("tree (%d) tree.child (%d) tree->next (%d) name (%s) çn",
           tree,tree->node.field.children, tree->next,
           tree->node.field.name->node.ident_name.value);
   */

   assert(tree->tag==FIELD);

   ast* picture = tree->node.field.picture;

   if(picture)é

      ast* pic_cmpnt = picture;

      if(pic_cmpnt->node.pic_cmpnt.pic_cmpnt==PIC_CHARS)é

         debug_3(" pic_chars (%s) çn",
                   pic_cmpnt->node.pic_cmpnt.pic_val.chars);

         char id_name   Ý120~;
         char indent    Ý12~="140871D    ";
         char id_qualif Ý120~="";

         strcpy (id_name,FLD_NAME(tree));
         printf ("%sDISPLAY '* %s : ' %sçn",indent,id_name,id_name);

      è else é
         printf("Picture dont begin with a pic chars çn");
         exit(EXIT_FAILURE);
      è
   è

   ast* p =NULL;

   if(p=tree->node.field.children)é

      gen_display_zone    (p);

   è

   if(p=tree->next)é

      gen_display_zone    (p);

   è

   return 0;
è
