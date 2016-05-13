#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

void *ret_correct_path(char *cmd, char **env) {
  char *cmd_cpy = cmd;
  char **env_cpy = env;
  char **path;
  char *en_var;
  DIR *pDir;
  struct dirent *pDirent;
  int i;

  /*if cmd is a path, return it without changing it*/
  if (check_path(cmd_cpy) == 1) {
    return cmd;
  }

  /*splits the path env variable from env variables and splits it into paths*/
  for (i=0; env_cpy[i] != 0; i++){
    en_var = env_cpy[i];
    if (en_var[0] == 'P' && en_var[1] == 'A' && en_var[2] == 'T' && en_var[3] == 'H') {
      path = string_split(env_cpy[i], '=');
      path = string_split(path[1], ':');
    }
  }

  /*search thru path for cmd */
  for (i=0; path[i] != 0; i++) {
    /* -> open path find file return cmd after str cat*/
    pDir = opendir(path[i]);
    if (pDir == NULL) {
      continue;
    }
    else {
      while ((pDirent = readdir(pDir)) != NULL) {
        if (strings_compare(cmd, pDirent->d_name) == 0) {
          cmd_cpy = path[i];
          str_cat(cmd_cpy, "/");
          str_cat(cmd_cpy, cmd);
          return cmd_cpy;
        }
      }
    }
  }
  /* Command not found, return NULL */
  return NULL;
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
