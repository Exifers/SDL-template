#include "../llist/llist.h"

struct llist *load_maps(void)
{
  return llist_init();
}

static void map_free(void *map)
{
  map = map;
  return;
}

static void free_map(void *map, int type)
{
  type = type;
  map_free(map);
}

void free_maps(struct llist *m)
{
  llist_free(m, free_map);
}
