#include <stdlib.h>

/*
 * Fucntion that frees a char **
 */
void free_command(char **command) {
  int counter = 0;
  while (command[counter] != 0) {
    free(command[counter]);
    counter++;
  }
  free(command);
}
