#include <stdlib.h>

char **string_split(char *str, char seperator) {
  char **ret;
  char *ret_ptr;
  char *ptr;
  char *fast;
  int count = 0;
  int word_count = 0;

  ptr = str;
  while (*ptr != 0) {
    if (*ptr == seperator) {
      count++;
      while (*ptr == seperator && *(ptr+1) != 0) ptr++;
    }
    ptr++;
  }

  ret = malloc(sizeof(char *) * (count+2));
  ptr = str;

  while (*ptr != 0) {
    count = 0;
    fast = ptr;

    while (*fast != seperator && *fast != 0) {
      count++;
      fast++;
    }

    ret[word_count] = malloc(sizeof(char) * (count + 1));
    ret_ptr = ret[word_count];

    while (*ptr != seperator && *ptr != 0) {
      *ret_ptr = *ptr;
      ret_ptr++;
      ptr++;
    }

    while (*ptr == seperator) ptr++;
    *ret_ptr = 0;
    word_count++;
  }
  ret[word_count] = 0;

  return ret;
}
