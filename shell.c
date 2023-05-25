#include "shell.h"

void display_prompt(int sign);
int fork_execute(char **args, char **start);

/**
 *display_prompt - display prompt
 *@sign: the signal
 */
void display_prompt(int sign)
{
	char *prompt_user = "\n#cisfun$";

	(void)sign;
	signal(SIGINT, display_prompt);
	write(STDIN_FILENO, prompt_user, 10);
}
/**
 *fork_execute - execute
 *@args: arr of args
 *@start: Begining of argument array
 *Return: 0 success
 */

int fork_execute(char **args, char **start)
{
	pid_t child_pid;
	int state, flags = 0, res = 0;
	char *cmd = args[0];

	if (cmd[0] != '/' && cmd[0] != '.')
	{
		flags = 1;
		cmd = _location(cmd);
	}
	if (!cmd || (access(cmd, F_OK) == -1))
	{
		if (errno == EACCES)
			res = (generate_error(args, 126));
		else
			res = (generate_error(args, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flags)
				free(cmd);
			perror("Error in child process:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(cmd, args, environ);
			if (errno == EACCES)
				res = (generate_error(args, 126));
			free_env_vars();
			free_argument(args, start);
			free_alias(aliases);
			_exit(res);
		}
		else
		{
			wait(&state);
			res = WEXITSTATUS(state);
		}
	}
	if (flags)
		free(cmd);
	return (res);
}
/**
 * main - entry point
 * @argc: No. of args
 * @av: Arr of args
 *
 * Return: 0 SUCCESS
*/

int main(int argc, char *av[])
{
	int res = 0, resn;
	int *execute_res = &resn;
	char *user_input = "#cisfun$ ", *empty_line = "\n";

	name = av[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, display_prompt);

	execute_res = 0;
	environ = copy_env_var();
	if (environ == NULL)
		exit(-100);

	if (argc != 1)
	{
		res = file_commands(av[1], execute_res);
		free_env_vars();
		free_alias(aliases);
		return (*execute_res);
	}
	if (!isatty(STDIN_FILENO))
	{
		while (res != END_OF_FILE && res != EXIT)
			res = handle_arguments(execute_res);
		free_env_vars();
		free_alias(aliases);
		return (*execute_res);
	}
	while (1)
	{
		write(STDOUT_FILENO, user_input, 10);
		res = handle_arguments(execute_res);
		if (res == END_OF_FILE || res == EXIT)
		{
			if (res == END_OF_FILE)
				write(STDOUT_FILENO, empty_line, 2);
			free_env_vars();
			free_alias(aliases);
			exit(*execute_res);
		}
	}
	free_env_vars();
	free_alias(aliases);
	return (*execute_res);
}
