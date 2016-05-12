#include <unistd.h>
#include "utils.h"

void cd(char *address) {
  if (strings_compare(address, "-") == 0) {
    address = get_env("OLDPWD");
  }
  if (chdir(address) == -1) {
    set_env
    write(2, "cd: no such directory\n", 22);
  }
}
