#include <unistd.h>
#include <stdlib.h>
#include "utils.h"

extern char **environ;

/* Move environ to the heap so we can add new variables. Run this in main */
void init_env() {
  char **environ_local = environ;
  char *var;
  int size;
  int i;
  size = len_command(environ_local);

  environ_local = malloc ((size+1) * sizeof(char*));

  for (i=0 ; i<size ; i++)
  {
    var = (char*) malloc ((str_len(environ[i])+1)*sizeof(char));
    string_copy(var, environ[i]);
    environ_local[i] = var;
  }
  environ_local[size] = 0;
  environ = environ_local;
}

/* get index of check in env */
int get_env_index(char **env, char *check) {
  int i = 0;
  char **env_var;
  while (env[i] != NULL) {
    env_var = string_split(env[i], '=');
    if (strings_compare(env_var[0], check) == 0) {
      /* found variable */
      free_command(env_var);
      return i;
    }
    free_command(env_var);
    i++;
  }
  return -1;
}

/* create an environ variable string from a name and a value. copies into dest*/
void concat_to_env(char *name, char *value, char *dest) {
  while (*name != 0) {
    *dest = *name;
    dest++;
    name++;
  }
  *dest='=';
  dest++;
  while (*value != 0) {
    *dest = *value;
    dest++;
    value++;
  }
  *dest = 0;
}

/* sets an environ variable */
void set_env(char *name, char *value) {
  char **environ_local = environ;
  char *var;
  int var_index = get_env_index(environ_local, name);
  int size;

  var = malloc(sizeof(char) * (str_len(name) + str_len(value) + 2));
  concat_to_env(name, value, var);

  /* If variable exists in environ_local */
  if (var_index != -1) {
    /* replace variable */
    environ_local[var_index] = var;
    return;
  }

  /* Var not found in env. need to add it. */
  size = len_command(environ_local);
  environ_local = realloc(environ_local, (size + 2) * sizeof(char *));
  environ_local[size] = var;
  environ_local[size+1] = NULL;
  environ = environ_local;
}
