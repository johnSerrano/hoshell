#include <stdlib.h>
#include "utils.h"

char * str_ncat(char *dest, char *src, int len) {
  char *ret = dest;
  while (*dest) {
    dest++;
  }
  while (len--) {
    if (!(*dest++ = *src++)) {
      return ret;
    }
  }
  *dest = 0;
  return ret;
}
