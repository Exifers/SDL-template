#ifndef MAPS_H
# define MAPS_H

#include "../llist/llist.h"

struct llist *load_maps(void);
void free_maps(struct llist *m);

#endif /* !MAPS_H */
