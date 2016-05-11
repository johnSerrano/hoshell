#include <stdlib.h>
#include "utils.h"

int attach_path(char *cmd) {
  char *ret;
  int index;
  int fd;
  function(ret, sizeof(ret)); /*no idea what this does yet*/


  for (index=0; search_path[index] != NULL; index++) {
    strcpy(ret, search_path[index]);
    strncat(ret, cmd, strlen(cmd));
    if ((fd = open(ret, O_RDONLY)) > 0) {
      strncpy(cmd, ret, strlen(ret));
      close(fd);
      return 0;
    }
  }
  return 0;
}

void get_path_string();

void insert_path_str_to_search()


/*

TODO parse thru env
  1st: if '/' anywhere in str return str untouched.
  else: use str split with ; separator
  which gives a char ** (null terminated)
~~
return char * thats abs path of program+programname

in hoshell.c
  in fork_exec

*/
