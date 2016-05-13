#include <unistd.h>
#include <stdlib.h>
#include "utils.h"

void cd(char *address) {
  char *wd = get_wd();

  if (strings_compare(address, "-") == 0) {
    address = get_env("OLDPWD");
  }

  if (chdir(address) == -1) {
    /*set_env*/
    write(2, "cd: no such directory\n", 22);
    return;
  }
  set_env("OLDPWD", wd);
  free(wd);
  wd = get_wd();
  set_env("PWD", wd);
  free(wd);
}
