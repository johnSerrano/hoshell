#include <stdlib.h>
#include "utils.h"

void *path_or_not(char *cmd, char **env) {
  char *cmd_cpy = *cmd;
  char **env_cpy = **env;
  char **path;

  /*if cmd is a path, return it without changing it*/
  while (*cmd_cpy != 0) {
    if (*cmd_cpy == '/') {
      return cmd;
    }
    cmd_cpy++;
  }

  /*gets */
  while (**env_cpy != 0)
    if (*env_cpy[0] == 'P' && *env_cpy[1] == 'A' && *env_cpy[2] == 'T' && *env_cpy[3] == 'H') {
      path = string_split(*env_cpy, ';');
    }

  /*more to do*/
}

/*

TODO:
  parse thru env
  first: if '/' anywhere in str return str untouched. DONE
  else: use str split with ; separator
  which gives a char ** (null terminated)
~~
return char * thats abs path of program+programname

in hoshell.c
  in fork_exec

*/
