#include "shell.h"

int check_arguments(char **args);
int run_arguments(char **args, char **start, int *execute_res);
char *get_arguments(char *line, int *execute_res);
int call_arguments(char **args, char **start, int *execute_res);
int handle_arguments(int *execute_res);

/**
 *get_arguments - Gets a command from STDIN.
 *@line: A buffer
 *@execute_res: The return value
 *
 *Return: NULL,Otherwise - a pointer to the stored cmd
 */

char *get_arguments(char *line, int *execute_res)
{
	size_t i = 0;
	ssize_t len;
	char *prompt = "$ ";

	if (line)
		free(line);
	len = custom_getline(&line, &i, STDIN_FILENO);
	if (len == -1)
		return (NULL);
	if (len == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_arguments(line, execute_res));
	}
	line[len - 1] = '\0';
	variable_replace(&line, execute_res);
	h_line(&line, len);
	return (line);
}
/**
 *call_arguments - Partitions operators and calls them.
 *@args: An array of args
 *@start: Pointer to the beginning of args.
 *@execute_res: The return value of the parent process
 *
 *Return: Value of the last executed cmd.
 */
int call_arguments(char **args, char **start, int *execute_res)
{
	int res, idx;

	if (!args[0])
		return (*execute_res);
	for (idx = 0; args[idx]; idx++)
	{
		if (custom_strncmp(args[idx], "||", 2) == 0)
		{
			free(args[idx]);
			args[idx] = NULL;
			args = replace_alias(args);
			res = run_arguments(args, start, execute_res);
			if (*execute_res != 0)
			{
				args = &args[++idx];
				idx = 0;
			}
			else
			{
				for (idx++; args[idx]; idx++)
					free(args[idx]);
				return (res);
			}
		}
		else if (custom_strncmp(args[idx], "&&", 2) == 0)
		{
			free(args[idx]);
			args[idx] = NULL;
			args = replace_alias(args);
			res = run_arguments(args, start, execute_res);
			if (*execute_res == 0)
			{
				args = &args[++idx];
				idx = 0;
			}
			else
			{
				for (idx++; args[idx]; idx++)
					free(args[idx]);
				return (res);
			}
		}
	}
	args = replace_alias(args);
	res = run_arguments(args, start, execute_res);
	return (res);
}

/**
 *run_arguments- Calls the execution of a cmd
 *@args: Array of args
 *@start: A double pointer to the beginning of args.
 *@execute_res: Return value
 *
 * Return: The return value of the last executed cmd
 */
int run_arguments(char **args, char **start, int *execute_res)
{
	int res, x;
	int (*built_in)(char **args, char **start);

	built_in = find_builtin(args[0]);

	if (built_in)
	{
		res = built_in(args + 1, start);
		if (res != EXIT)
			*execute_res = res;
	}
	else
	{
		*execute_res = fork_execute(args, start);
		res = *execute_res;
	}
	hist++;
	for (x = 0; args[x]; x++)
		free(args[x]);
	return (res);
}
/**
 *handle_arguments- Handle arguments
 *
 *@execute_res: Ececute results
 *Return: EOF
 */
int handle_arguments(int *execute_res)
{
	int res = 0, idx;
	char **args, *line = NULL, **start;

	line = get_arguments(line, execute_res);
	if (!line)
		return (END_OF_FILE);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (res);
	if (check_arguments(args) != 0)
	{
		*execute_res = 2;
		free_argument(args, args);
		return (*execute_res);
	}
	start = args;

	for (idx = 0; args[idx]; idx++)
	{
		if (custom_strncmp(args[idx], ";", 1) == 0)
		{
			free(args[idx]);
			args[idx] = NULL;
			res = call_arguments(args, start, execute_res);
			args = &args[++idx];
			idx = 0;
		}
	}
	if (args)
		res = call_arguments(args, start, execute_res);
	free(start);
	return (res);
}
/**
 *check_arguments - check argement
 *@args: Arr of argumets
 *
 *Return: Success otherwise 0;
 */
int check_arguments(char **args)
{
	size_t x;
	char *curr, *_next;

	for (x = 0; args[x]; x++)
	{
		curr = args[x];
		if (curr[0] == ';' || curr[0] == '&' || curr[0] == '|')
		{
			if (x == 0 || curr[1] == ';')
				return (generate_error(&args[x], 2));
			_next = args[x + 1];
			if (_next && (_next[0] == ';' || _next[0] == '&' || _next[0] == '|'))
				return (generate_error(&args[x + 1], 2));
		}
	}
	return (0);
}
