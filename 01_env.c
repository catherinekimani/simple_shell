#include "shell.h"

/**
 * get_env_val - gets value of an env var
 * @variable: name of env variable
 *
 * Return: ptr to the value of an env variable
 */
char **get_env_val(const char *variable)
{
	int idx, length;

	length = custom_strlen(variable);
	for (idx = 0; environ[idx]; idx++)
	{
		if (custom_strncmp(variable, environ[idx], length) == 0)
			return (&environ[idx]);
	}
	return (NULL);
}

/**
 * copy_env_var - copies env variable
 * Return: ptr to new env
 */
char **copy_env_var(void)
{
	char **newEnv;
	int idx;
	size_t size;

	for (size = 0; environ[size]; size++)
		;
	newEnv = malloc(sizeof(char *) * (size + 1));
	if (!newEnv)
		return (NULL);
	for (idx = 0; environ[idx]; idx++)
	{
		newEnv[idx] = malloc(custom_strlen(environ[idx]) + 1);
		if (!newEnv[idx])
		{
			for (idx--; idx >= 0; idx--)
				free(newEnv[idx]);
			free(newEnv);
			return (NULL);
		}
		custom_strcpy(newEnv[idx], environ[idx]);
	}
	newEnv[idx] = NULL;
	return (newEnv);
}

/**
 * free_env_vars - func to free env vars
 */
void free_env_vars(void)
{
	int idx;

	for (idx = 0; environ[idx]; idx++)
		free(environ[idx]);
	free(environ);
}
