#include <stdlib.h>
#include "utils.h"

void cmd_exit(char **command) {
  int arg_val;
  if (len_command(command) <= 1)
    exit(0);

  /* try to parse argv[1] as an int.
   * if that fails, return 0. (default return of string_to_int)
   */
  arg_val = string_to_int(command[1]);
  free_command(command);
  exit(arg_val);
}
