#ifndef LLIST_H
# define LLIST_H

struct llist_elt
{
  void *data;
  int type;
  struct llist_elt *next;
};

struct llist
{
  size_t size;
  struct llist_elt *head;
};

struct llist *llist_init(void);

void llist_append(struct llist *l, void *data, int type);

void llist_pop(struct llist *l, void (*free_data)(void *data, int type));

void * llist_get_item(struct llist *l, size_t index);

size_t llist_get_size(struct llist *l);

void llist_free(struct llist *l, void (*free_data)(void * data, int type));

void llist_print(struct llist *l, int offset, int inc,
                void (*print_fun)(void * data, int type, int offset, int inc));

#endif /* !LLIST_H */
