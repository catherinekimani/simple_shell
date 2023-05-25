#include "shell.h"

void free_argument(char **args, char **start);
char *get_pid(void);
char *get_env(char *begin, int length);
void variable_replace(char **args, int *execute_res);

/**
 *free_argument - Frees
 *@args: Arr of args
 *@start:  start of args
 */

void free_argument(char **args, char **start)
{
	size_t j;

	for (j = 0; args[j] || args[j + 1]; j++)
		free(args[j]);
	free(start);
}
/**
 *get_pid - Get current PID
 *Return: The current process ID or NULL on failure.
 */
char *get_pid(void)
{
	size_t j = 0;
	char *buff;
	ssize_t f;

	f = open("/proc/self/stat", O_RDONLY);
	if (f == -1)
	{
		perror("cannot read file");
		return (NULL);
	}
	buff = malloc(120);
	if (!buff)
	{
		close(f);
		return (NULL);
	}
	read(f, buff, 120);
	while (buff[j] != ' ')
		j++;
	buff[j] = '\0';
	close(f);
	return (buff);
}

/**
 *get_env - Gets the val of environmental variable
 *@begin: The variable.
 *@length: The length of the variable
 *
 *Return: Null or val of variable
 */
char *get_env(char *begin, int length)
{
	char **addr;
	char *replace = NULL, *temp, *variable;

	variable = malloc(length + 1);
	if (!variable)
		return (NULL);
	variable[0] = '\0';
	custom_strncat(variable, begin, length);
	addr = _getenv(variable);
	free(variable);
	if (addr)
	{
		temp = *addr;
		while (*temp != '=')
			temp++;
		temp++;
		replace = malloc(_strlen(temp) + 1);
		if (replace)
			_strcpy(replace, temp);
	}
	return (replace);
}
/**
 *variable_replace - Variable replacement.
 *@line: Pinter with the command and arguments
 *@execute_res: A pointer to the return value
 *
 */

void variable_replace(char **line, int *execute_res)
{
	int i, n = 0, length;
	char *replace = NULL, *older_line = NULL, *newer_line;

	older_line = *line;
	for (i = 0; older_line[i]; i++)
	{
		if (older_line[i] == '$' && older_line[i + 1] &&
				older_line[i + 1] != ' ')
		{
			if (older_line[i + 1] == '$')
			{
				replace = get_pid();
				n = i + 2;
			}
			else if (older_line[i + 1] == '?')
			{
				replace = _itoa(*execute_res);
				n = i + 2;
			}
			else if (older_line[i + 1])
			{
				for (n = i + 1; older_line[n] &&
						older_line[n] != '$' &&
						older_line[n] != ' '; n++)
					;
				length = n - (i + 1);
				replace = get_env_val(&older_line[i + 1], length);
			}
			newer_line = malloc(i + custom_strlen(replace)
					+ custom_strlen(&older_line[n]) + 1);
			if (!line)
				return;
			newer_line[0] = '\0';
			custom_strncat(newer_line, older_line, i);
			if (replace)
			{
				custom_strcat(newer_line, replace);
				free(replace);
				replace = NULL;
			}
			custom_strcat(newer_line, &older_line[n]);
			free(older_line);
			*line = newer_line;
			older_line = newer_line;
			i = -1;
		}
	}
}
