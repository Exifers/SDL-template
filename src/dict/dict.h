#ifndef DICT_H
# define DICT_H

#include <stddef.h>

struct dict_elt
{
  char *key;
  void *data;
  int type;

  struct dict_elt *next;
};

struct dict
{
  size_t size;
  struct dict_elt *head;
};

struct dict *dict_init(void);

void dict_append(struct dict *d, void *data, int type, char *key);

void dict_pop(struct dict *d, void (*free_data)(void * data, int type));

void *dict_get_item(struct dict *d, char *key);

size_t dict_get_size(struct dict *d);

void dict_free(struct dict *d, void (*free_data)(void *data, int type));

void dict_print(struct dict *d, int offset, int inc,
     void (*print_fun)(void *data, int type, int offset, int inc));

#endif /* !DICT_H */
