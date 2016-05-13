#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"

void *ret_correct_path(char *cmd, __attribute__((unused)) char **env) {
  char *cmd_cpy = cmd;
  char **path;
  DIR *pDir;
  struct dirent *pDirent;
  int i;

  /*if cmd is a path, return it without changing it*/
  if (check_path(cmd_cpy) == 1) {
    free(cmd_cpy);
    return cmd;
  }

  /*splits the path env variable from env variables and splits it into paths*/
  /*for (i=0; env_cpy[i] != 0; i++){
    en_var = env_cpy[i];
    if (en_var[0] == 'P' && en_var[1] == 'A' && en_var[2] == 'T' && en_var[3] == 'H') {
      path = string_split(env_cpy[i], '=');
      str = malloc(str_len(path[1]));
      string_copy(str, path[1]);
      free_command(path);
      path = string_split(str, ':');
    }
  }*/
  path = string_split(get_env("PATH"), ':');

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
        }
      }
    }
    closedir(pDir);
  }
  free_command(path);
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
  malloc all the things!!!
  free all the things!!!

  ~~
  return char * thats abs path of program+programname

  in hoshell.c
    in fork_exec

*/
