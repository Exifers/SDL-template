#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

char *map_file(const char *file_name, size_t *len)
{
  int f = open(file_name, O_RDONLY);
  if (f == -1)
    perror(NULL);

  struct stat buf;
  fstat(f, &buf);
  *len = buf.st_size;

  char *addr = mmap(NULL, *len, PROT_READ, MAP_PRIVATE, f, 0);
  if (addr == MAP_FAILED)
    perror(NULL);

  return addr;
}
