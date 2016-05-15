#include <unistd.h>
#include <stdlib.h>
#include "utils.h"

/*
 * Function that will change directories
 */
void cd(char *address) {
  char *wd = get_wd();

  /*getting the old directory when '-' is the option*/
  if (strings_compare(address, "-") == 0) {
    address = get_env("OLDPWD");
  }

  /*error checking if path to dir doesn't exist*/
  if (chdir(address) == -1) {
    /*set_env*/
    write(2, "cd: no such directory\n", 22);
    return;
  }
  /*making sure to set the current dir as OLDPWD before changing dir*/
  set_env("OLDPWD", wd);
  free(wd);
  wd = get_wd();
  set_env("PWD", wd);
  free(wd);
}
