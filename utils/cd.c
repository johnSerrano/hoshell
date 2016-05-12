#include <unistd.h>

void cd(char *address) {
  if (chdir(address) == -1) {
    /*error*/ ;
  }
}
