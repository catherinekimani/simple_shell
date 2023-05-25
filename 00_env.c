#include "shell.h"

/**
 * display_env_vars - display environment vars
 * @args: cmd args
 * @start: double ptr
 *
 * Return: 0 SUCCESS
 */
int display_env_vars(char **args, char
__attribute__((__unused__)) **start)
{
	char new_line = '\n';
	int idx;

	if (!environ)
		return (-1);
	for (idx = 0; environ[idx]; idx++)
	{
		write(STDOUT_FILENO, environ[idx], custom_strlen(environ[idx]));
		write(STDOUT_FILENO, &new_line, 1);
	}
	(void)args;
	return (0);
}

/**
 * set_shell_env - changes or adds env vars to the PATH
 * @args: cmd args
 * @start: double ptr
 *
 * Return: 0 SUCCESS
 */
int set_shell_env(char **args, char __attribute__((__unused__)) **start)
{
	char **envVariable = NULL, **newEnv, *newVal;
	size_t size;
	int idx;

	if (!args[0] || !args[1])
		return (generate_error(args, -1));

	newVal = malloc(custom_strlen(args[0]) + 1 + custom_strlen(args[1]) + 1);
	if (!newVal)
		return (generate_error(args, -1));
	custom_strcat(newVal, args[0]);
	custom_strcat(newVal, "=");
	custom_strcat(newVal, args[1]);

	envVariable = get_env_val(args[0]);
	if (envVariable)
	{
		free(*envVariable);
		*envVariable = newVal;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;
	newEnv = malloc(sizeof(char *) * (size + 2));
	if (!newEnv)
	{
		free(newVal);
		return (generate_error(args, -1));
	}

	for (idx = 0; environ[idx]; idx++)
		newEnv[idx] = environ[idx];

	free(environ);
	environ = newEnv;
	environ[idx] = newVal;
	environ[idx + 1] = NULL;

	return (0);
}

/**
 * unset_shell_env - remove an env var to the shell
 * @args: cmd args
 * @start: double ptr
 *
 * Return: 0 SUCCESS
 */
int unset_shell_env(char **args, char __attribute__((__unused__)) **start)
{
	char **envVariable, **newEnv;
	size_t size;
	int idx1, idx2;

	if (!args[0])
		return (generate_error(args, -1));
	envVariable = get_env_val(args[0]);
	if (!envVariable)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	newEnv = malloc(sizeof(char *) * size);
	if (!newEnv)
		return (generate_error(args, -1));

	for (idx1 = 0, idx2 = 0; environ[idx1]; idx1++)
	{
		if (*envVariable == environ[idx1])
		{
			free(*envVariable);
			continue;
		}
		newEnv[idx2] = environ[idx1];
		idx2++;
	}
	free(environ);
	environ = newEnv;
	environ[size - 1] = NULL;

	return (0);
}
