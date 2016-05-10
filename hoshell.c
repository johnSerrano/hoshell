#include <unistd.h>
#include <stdlib.h>
#include "libshell/libshell.h"

void fork_exec(char **command, char **env);
void free_command(char **command);

int main(int argc, char **argv, char **env) {
  char **command;
  char *line;
  /* read from stdin */
  while (1) {
    write(1, "HOS :: ", 7);
    line = read_line(0);
    command = string_split(line, ' ');

    fork_exec(command, env);
    free_command(command);
    free(line);
  }

}

/* frees a char ** */
void free_command(char **command) {
  int counter = 0;
  while (command[counter] != 0) {
    free(command[counter]);
    counter++;
  }
  free(command);
}

/* run a command without killing the main thread */
void fork_exec(char **command, char **env) {
  int status;
  int pid = fork();
  if (pid == -1) {
    write(2, "Fork failed", 11);
  } else if (pid == 0) {
    execve(command[0], command, env);
  } else {
    wait(&status);
  }
  return;
}
