#include <unistd.h>
#include <stdlib.h>
#include "libshell/libshell.h"
#include "utils/utils.h"
#include <sys/wait.h>

void fork_exec(char **command, char **env);
void free_command(char **command);
void check_builtins(char **command, __attribute__((unused)) char **env);

int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv, char **env) {
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
  int pid;
  check_builtins(command, env);
  pid = fork();
  if (pid == -1) {
    write(2, "Fork failed", 11);
  } else if (pid == 0) {
    execve(command[0], command, env);
  } else {
    wait(&status);
  }
  return;
}

void check_builtins(char **command, __attribute__((unused)) char **env) {
  if (strings_compare(command[0], "exit") == 0) {
    cmd_exit(command);
  }
}
