#include <stdlib.h>
#include "utils.h"

void *ret_correct_path(char *cmd, char **env) {
  char *cmd_cpy = *cmd;
  char **env_cpy = **env;
  char **path, char **path_cpy;
  DIR *pDir;
  struct dirent *pDirent;
  int cmd_len;

  /*if cmd is a path, return it without changing it*/
  if (check_path(*cmd_cpy) == 1) {
    return cmd;
  }

  /*splits the path env variable from env variables and splits it into paths*/
  while (**env_cpy != 0){
    if (*env_cpy[0] == 'P' && *env_cpy[1] == 'A' && *env_cpy[2] == 'T' && *env_cpy[3] == 'H') {
      path = string_split(*env_cpy, '=');
      path = string_split(path[1], ';');
      break;
    }
  }
  path_cpy = path;

  /*search thru path for cmd */
  while (**path_cpy != 0) {
    /* -> open path find file return cmd after str cat*/
    pDir = openddir(*path_cpy);
    if (pDir == NULL) {
      continue;
    }
    else {
      while ((pDirent = readdir(pDirr)) != NULL) {
        if (pDirent->d_name == cmd) {
          cmd_cpy = str_cat(*path_cpy, *cmd);
          return cmd_cpy;
        }
      }
    }
  }
}

  /*more to do*/
}

/*if cmd is a path, return it without changing it*/
int check_path(char *cmd_cpy) {
  while (*cmd_cpy != 0) {
    if (*cmd_cpy == '/') {
      return 1;
    }
    cmd_cpy++;
  }
  return 0;
}


/*

TODO:
  open folders and paths
  replace strncat with your own strncat
  malloc all the things!!!
  free all the things!!!

  ~~
  return char * thats abs path of program+programname

  in hoshell.c
    in fork_exec

*/
