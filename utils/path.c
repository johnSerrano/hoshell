#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include "utils.h"

void *ret_correct_path(char *cmd, char **env) {
  char *cmd_cpy = cmd;
  char **env_cpy = env;
  char **path;
  DIR *pDir;
  struct dirent *pDirent;
  int i;

  printf("cmd: %s\n", cmd);
  printf("cmd_cpy: %s\n", cmd_cpy);

  /*if cmd is a path, return it without changing it*/
  if (check_path(cmd_cpy) == 1) {
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

  /*search thru path for cmd */
  for (i=0; path[i] != 0; i++) {
    /* -> open path find file return cmd after str cat*/
    pDir = opendir(*path);
    if (pDir == NULL) {
      continue;
    }
    else {
      while ((pDirent = readdir(pDir)) != NULL) {
        if (pDirent->d_name == cmd) {
          cmd_cpy = *path;
          str_cat(cmd_cpy, cmd);
          return cmd_cpy;
        }
      }
    }
  }
  return cmd_cpy;
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
