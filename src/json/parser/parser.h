#ifndef PARSER_H
# define PARSER_H

#include <stddef.h>

enum data_type
{
  DICT,
  LIST,
  STRING,
  NUMBER,
  TRUE,
  FALSE,
  NUL,
  EMPTY
};

void eat(char *addr, char c);
void *parse_json(char *addr, size_t len, enum data_type *type);

#endif /* !PARSER_H */
