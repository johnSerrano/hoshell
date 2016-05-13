#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"

void *ret_correct_path(char *cmd, __attribute__((unused)) char **env) {
  char *cmd_cpy;
  char **path;
  char *str;
  DIR *pDir;
  struct dirent *pDirent;
  int i;

  cmd_cpy = malloc(sizeof(char) * str_len(cmd) + 1);
  cmd_cpy = string_copy(cmd_cpy, cmd);

  /*if cmd is a path, return it without changing it*/
  if (check_path(cmd_cpy) == 1) {
    free(cmd_cpy);
    return cmd;
  }

  str = get_env("PATH");
  path = string_split(str, ':');

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
          cmd_cpy = malloc(sizeof(char)*(str_len(path[i]) + str_len(cmd) + 2));
          cmd_cpy = string_copy(cmd_cpy, path[i]);
          str_cat(cmd_cpy, "/");
          str_cat(cmd_cpy, cmd);
        }
      }
    }
    closedir(pDir);
  }
  free_command(path);
  free(str);
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
