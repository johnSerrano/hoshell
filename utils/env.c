#include <unistd.h>
#include "utils.h"

int print_env(char** envp) {
  char** env;
  for (env = envp; *env != 0; env++)
  {
    char* thisEnv = *env;
    write(1, thisEnv, str_len(thisEnv));
    write(1, "\n", 1);
  }
  return(0);
}
