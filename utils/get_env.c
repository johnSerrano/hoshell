#include <unistd.h>
#include <stdlib.h>
#include "utils.h"

extern char **environ;

/* returns a malloc'd string containing the env value */
char *get_env(char *check) {
  char **env = environ;
  int i = 0;
  char **env_var;
  char *ret;
  char *ptr;
  while (env[i] != NULL) {
    env_var = string_split(env[i], '=');
    if (strings_compare(env_var[0], check) == 0) {
      /* found variable */
      ptr = env[i];
      while (*ptr != '=') {
        ptr++;
      }
      ptr++;
      ret = malloc(sizeof(char) * (str_len(ptr)+1));
      string_copy(ret, ptr);
      return ret;
      free_command(env_var);
    }
    free_command(env_var);
    i++;
  }
  return 0;
}
