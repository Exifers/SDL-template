#include <stdio.h>

#include "../../llist/llist.h"
#include "../../dict/dict.h"
#include "display.h"
#include "../parser/parser.h"

static void print_data_recur(void *data, int type, int offset, int inc)
{
  switch ((int) type)
  {
    case DICT:
      dict_print(data, offset, inc, print_data_recur);
      break;
    case LIST:  
      llist_print(data, offset, inc, print_data_recur);
      break;
    case STRING:
      printf("\"%s\"", (char *) data);
      break;
    case NUMBER:
      printf("%d", *((int *) data));
      break;
    case TRUE:
      printf("true");
      break;
    case FALSE:
      printf("false");
      break;
    case NUL:
      printf("null");
      break;  
    case EMPTY:
      printf("empty");
      break;
  }
}

void print_data(void *data, enum data_type type)
{
  print_data_recur(data, type, 0, 2);
  printf("\n");  
}
