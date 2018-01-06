#include <stdlib.h>

#include "../../dict/dict.h"
#include "../../llist/llist.h"
#include "../parser/parser.h"
#include "free.h"

void free_data(void *data, int type)
{
  switch (type)
  {
    case DICT:
      dict_free(data, free_data);
      break;
    case LIST:
      llist_free(data, free_data);
      break;
    case STRING:
      free(data);
      break;
    case NUMBER:
      free(data);
      break;
  }
}
