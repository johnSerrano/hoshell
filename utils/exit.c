#include <stdlib.h>
#include "utils.h"
#include <unistd.h>

extern char **environ;

/*
 * Function that exits out of the shell
 */
void cmd_exit(char **command)
{
	int arg_val;
	free_command(environ);
	if (len_command(command) <= 1) {
		free_command(command);
		exit(0);
	}

	free_command(command);
	/*
	 * try to parse argv[1] as an int.
	 * if that fails, return 0. (default return of string_to_int)
	 */
	arg_val = string_to_int(command[1]);
	exit(arg_val);
}
