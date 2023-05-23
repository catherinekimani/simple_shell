#include "shell.h"

/**
 * fork_execute - execute
 * @argv: arr of args
 * @env: arr ofenvironment variable
 */

void fork_execute(char **argv, char *env[])
{
	int state;
	pid_t child_pid;

	child_pid = fork();
	if (child_pid < 0)
	{
		perror("Error: Couldn't Fork\n ");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(argv[0], argv, env) == -1)
			fprintf(stderr, "%s: No such file or directory\n", argv[0]);
	}
	else
		wait(&state);
}
