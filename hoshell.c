#include <unistd.h>
#include <stdlib.h>
#include "utils/utils.h"
#include <sys/wait.h>
#include <stdio.h> /*TODO remove after testing?*/

void fork_exec(char **command, char **env);
int check_builtins(char **command, __attribute__((unused)) char **env);

int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv, char **env) {
  char **command;
  char *line;

  /* moves environment variables to the heap */
  init_env();

  /* read from stdin */
  while (1) {
    write(1, "HOS :: ", 7);
    line = read_line(0);

    /*ignore comments*/
    command = string_split(line, '#');
    if (command[0] == NULL) continue;
    string_copy(line, command[0]);
    free_command(command);

    command = string_split(line, ' ');
    if (command[0] == NULL) continue;

    fork_exec(command, env);
    free_command(command);
    free(line);
  }
}

/* run a command without killing the main thread */
void fork_exec(char **command, char **env) {
  int status;
  int pid;
  char *cmd = command[0];

  if (check_builtins(command, env)) return;
  cmd = ret_correct_path(cmd, env);

  if (cmd == NULL) {
    write(2, "Command not found\n", 18);
    return;
  }

  pid = fork();
  if (pid == -1) {
    write(2, "Fork failed", 11);
  } else if (pid == 0) {
    execve(cmd, command, env);
  } else {
    wait(&status);
    update_status(status);
  }
  free(cmd);
  return;
}

/* check builtin commands before searching path.
 * returns 1 if found, 0 otherwise
 */
int check_builtins(char **command, char **env) {
  if (strings_compare(command[0], "exit") == 0) {
    cmd_exit(command);
    /* shouldn't run except if there is an error exiting */
    return 1;
  }
  if (strings_compare(command[0], "env") == 0) {
    print_env(env);
    return 1;
  }
  if (strings_compare(command[0], "cd") == 0) {
    if (len_command(command) <= 1) {
      /* error */
      return 1;
    }
    cd(command[1]);
    return 1;
  }
  if (strings_compare(command[0], "pwd") == 0) {
    pwd();
    return 1;
  }
  if (strings_compare(command[0], "$?") == 0) {
    print_status();
    return 1;
  }
  return 0;
}
