#include <unistd.h>
#include <stdlib.h>
#include "utils/utils.h"
#include <sys/wait.h>

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
    command = string_split(line, ' ');

    fork_exec(command, env);
    free_command(command);
    free(line);
  }
}

/* run a command without killing the main thread */
void fork_exec(char **command, char **env) {
  int status;
  int pid;

  /*TODO (jo) link to env or PATH function here in Progress*/

  if (check_builtins(command, env)) return;

  /*
  TODO - run path function return command(full path)

  cmd = either command[0] OR returned command from above
  */

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
  return 0;
}
