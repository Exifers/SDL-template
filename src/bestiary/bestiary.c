#include <err.h>
#include <sys/mman.h>

#include "../json/free/free.h"
#include "../json/parser/parser.h"
#include "../llist/llist.h"
#include "../utils/files.h"

struct llist *load_bestiary(void)
{
  size_t len = 0;
  char *addr = map_file("data/bestiary/bestiary.json", &len);

  enum data_type type;
  void *res = parse_json(addr, len, &type);
  munmap(addr, len);
  
  if (type != LIST)
    errx(1, "Expected an array as base type in bestiary.json");

  return res;
}

void free_bestiary(struct llist *b)
{
  free_data(b, LIST);
}
