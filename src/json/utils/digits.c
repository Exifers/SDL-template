#include <stddef.h>

size_t int_width(int num)
{
  if (num == 0)
    return 1;
  int neg = 0;
  if (num < 0)
  {
    neg = 1;
    num *= -1;
  }
  size_t res = 0;
  while (num > 0)
  {
    num /= 10;
    res++;
  }
  return res + neg;
}
