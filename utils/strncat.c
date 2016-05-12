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

char * str_cat(char *dest, char *src) {
  char *ret = dest;
  while (*dest) {
    dest++;
  }
  while (1) {
    if (!(*dest++ = *src++)) {
      return ret;
    }
  }
  return ret;
}
