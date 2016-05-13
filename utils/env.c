#include <unistd.h>
#include "utils.h"

extern char **environ;

int print_env() {
  char** env = environ;
  for ( ; *env!=0 ; env++)
  {
    char* thisEnv = *env;
    write(1, thisEnv, str_len(thisEnv));
    write(1, "\n", 1);
  }
  return(0);
}
