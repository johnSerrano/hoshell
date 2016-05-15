#include "utils.h"

/*
 * Function that updates the environment status value <?>.
 */
void update_status(int status) {
  char *status_str = int_to_string(status);
  set_env("?", status_str);
}
