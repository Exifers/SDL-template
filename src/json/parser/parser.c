#include <ctype.h>
#include <err.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../dict/dict.h"
#include "../../llist/llist.h"
#include "../utils/digits.h"
#include "parser.h"

static void *parse_value(char *addr, size_t len, enum data_type *type);
static char *parse_string(char *addr, size_t len);
static int *parse_number(char *addr, size_t len);
static struct dict *parse_dict(char *addr, size_t len);
static struct llist *parse_list(char *addr, size_t len);
static void *parse_token(char *addr, size_t len, char *token);

size_t index;

void eat(char *addr, char c)
{
  if (addr[index] != c)
    errx(1, "Incorrect character at index %zu, \
 expected '%c' but found '%c'", index, c, addr[index]);
  index++;
}

static void skip_blanks(char *addr, size_t len)
{
  while (addr[index] == ' '  ||
         addr[index] == '\t' ||
         addr[index] == '\n')
  {
    index++;
    if (index >= len)
      break;
  }
}

static void *parse_token(char *addr, size_t len, char *token)
{
  size_t token_len = strlen(token);
  if (index + token_len > len)
    errx(1, "Unterminated tokenen");
  if (strncmp(addr + index, token, token_len) == 0)
  {
    index += token_len;
    return NULL;
  }
  errx(1, "Incorrect token");
}

static struct llist *parse_list(char *addr, size_t len)
{
  eat(addr, '[');
  skip_blanks(addr, len);

  struct llist *res = llist_init();

  while (addr[index] != ']')
  {
    skip_blanks(addr, len);
    enum data_type type;
    void *value = parse_value(addr, len, &type);
    llist_append(res, value, type);

    skip_blanks(addr, len);
    if (addr[index] == ',')
      eat(addr, ',');
    skip_blanks(addr, len);
  }

  eat(addr, ']');

  return res;
}

static struct dict *parse_dict(char *addr, size_t len)
{
  eat(addr, '{');
  skip_blanks(addr, len);

  struct dict *res = dict_init();

  while (addr[index] != '}')
  {
    skip_blanks(addr, len);
    char *key = parse_string(addr, len);
    skip_blanks(addr, len);
    eat(addr, ':');
    skip_blanks(addr, len);

    enum data_type type;
    void *value = parse_value(addr, len, &type);
    dict_append(res, value, type, key);

    skip_blanks(addr, len);
    if (addr[index] == ',')
      eat(addr, ',');
    skip_blanks(addr, len);
  }

  eat(addr, '}');

  return res;
}

static int *parse_number(char *addr, size_t len)
{
  int *res = malloc(sizeof(int));
  if (!res)
    perror(NULL);

  len = len;

  // handles only integers
  sscanf(addr + index, "%d", res);

  index += int_width(*res);

  return res;
}

static char *parse_string(char *addr, size_t len)
{
  eat(addr, '"');
  if (index >= len)
    errx(1, "Incorrect format: unterminated string");

  char *data = addr + index;
  size_t str_len = 0;
  while (data[str_len] != '"')
    str_len++;

  char *str = malloc(sizeof(char) * (str_len + 1));
  if (!str)
    perror(NULL);
  
  for (size_t i = 0; i < str_len; i++)
  {
    str[i] = data[i];
    index++;
    if (index >= len)
      errx(1, "Incorrect format: unterminated string");
  }
  str[str_len] = '\0';

  eat(addr, '"');

  return str;
}

static void *parse_value(char *addr, size_t len, enum data_type *type)
{
  skip_blanks(addr, len);
  if (index >= len)
  {
    *type = EMPTY;
    return NULL;
  }
  else if (addr[index] == '"')
  {
    *type = STRING;
    return parse_string(addr, len);
  }
  else if (isdigit(addr[index]))
  {
    *type = NUMBER;
    return parse_number(addr, len);
  }
  else if (addr[index] == '{')
  {
    *type = DICT;
    return parse_dict(addr, len);
  }
  else if (addr[index] == '[')
  {
    *type = LIST;
    return parse_list(addr, len);
  }
  else if (addr[index] == 't')
  {
    *type = TRUE;
    return parse_token(addr, len, "true");
  }
  else if (addr[index] == 'f')
  {
    *type = FALSE;
    return parse_token(addr, len, "false");
  }
  else if (addr[index] == 'n')
  {
    *type = NUL;
    return parse_token(addr, len, "null");
  }
  errx(1, "Incorrect format: first character '%c' is incorrect", addr[index]);
  return NULL;
}

void *parse_json(char *addr, size_t len, enum data_type *type)
{
  index = 0;
  void *ret = parse_value(addr, len, type);
  skip_blanks(addr, len);
  if (index != len)
    errx(1, "Unexpected element after json data, at %zu", index);
  return ret;
}
