#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "llist.h"

struct llist *llist_init(void)
{
  struct llist *res = malloc(sizeof(struct llist));
  if (!res)
    perror(NULL);

  res->size = 0;
  res->head = NULL;

  return res;
}

void llist_append(struct llist *l, void * data, int type)
{
  if (!l)
    errx(1, "linked list is NULL");

  struct llist_elt *new = malloc(sizeof(struct llist_elt));
  if (!new)
    perror(NULL);
  new->data = data;
  new->next = NULL;
  new->type = type;


  struct llist_elt *cur = l->head;
  if (!cur)
  {
    l->head = new;
    l->size++;
    return;
  }
  while (cur->next)
    cur = cur->next;
  cur->next = new;
  l->size++;
}

void llist_pop(struct llist *l, void (*free_data)(void * data, int type))
{
  if (!l)
    errx(1, "linked list is NULL");

  struct llist_elt *cur = l->head;

  if (!cur)
    return;

  if (!cur->next)
  {
    free_data(cur->data, cur->type);
    free(cur);
    l->head = NULL;
    l->size--;
    return;
  }

  while(cur->next->next)
    cur = cur->next;

  free_data(cur->next->data, cur->next->type);
  free(cur->next);
  cur->next = NULL;
  l->size--;
}

void * llist_get_item(struct llist *l, size_t index)
{
  if (!l)
    errx(1, "linked list is NULL");

  if (index >= l->size)
    errx(1, "list index out of range");

  struct llist_elt *cur = l->head;
  for (size_t i = 0; i < index; i++)
    cur = cur->next;

  return cur->data;
}

size_t llist_get_size(struct llist *l)
{
  if (!l)
    errx(1, "linked list is NULL");

  return l->size;
}


void llist_free(struct llist *l, void (*free_data)(void * data, int type))
{
  if (!l)
    errx(1, "linked list is NULL");

  size_t size = l->size;
  for (size_t i = 0; i < size; i++)
    llist_pop(l, free_data);
  free(l);
}

static void print_offset(int offset)
{
  for (int i = 0; i < offset; i++)
    printf(" ");
}

void llist_print(struct llist *l, int offset, int inc,
                 void (*print_fun)(void * data, int type, int offset, int inc))
{
  if (!l)
    errx(1, "linked list is NULL");

  struct llist_elt *cur = l->head;
  printf("[\n");
  for (size_t i = 0; i < l->size; i++)
  {
    print_offset(offset + inc);
    print_fun(cur->data, cur->type, offset + inc, inc);
    if (i != l->size - 1)
      printf(",");
    printf("\n");
    cur = cur->next;
  }
  print_offset(offset);
  printf("]");
}
