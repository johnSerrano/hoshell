#include "utils.h"
#include <unistd.h>

void print_status(void) {
  char *status = get_env("?");
  write(1, status, str_len(status));
  write(1, "\n", 1);
}
