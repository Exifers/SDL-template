#ifndef BESTIARY_H
# define BESTIARY_H

#include "../llist/llist.h"

struct llist *load_bestiary(void);
void free_bestiary(struct llist *b);

#endif /* !BESTIARY_H */
