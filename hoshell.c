#include <unistd.h>

int main(int argc, char **argv, char **env) {

  /* read from stdin */
  while (true) {

  }

}

char **listen() {
  char **command;
  char ch;

  while(read(0, &ch, 1) > 0)
  {
    write(1, &ch, 1);
    if (ch == '\n') {
      return command;
    }
  }
}
