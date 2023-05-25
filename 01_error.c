#include "shell.h"

char *err_126(char **args);
char *err_127(char **args);

/**
 *err_126 - Permission denied
 *@args: An array of args
 *
 *Return: The error
 */
char *err_126(char **args)
{
	int length;
	char *err, *history_str;

	history_str = _itoa(hist);
	if (!history_str)
		return (NULL);
	length = custom_strlen(name) + custom_strlen(history_str) +
		custom_strlen(args[0]) + 24;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(history_str);
		return (NULL);
	}
	custom_strcpy(err, name);
	custom_strcat(err, ": ");
	custom_strcat(err, history_str);
	custom_strcat(err, ": ");
	custom_strcat(err, args[0]);
	custom_strcat(err, "Permission denied\n");
	free(history_str);
	return (err);
}
/**
 *err_127 - Create error msg for cmd not found
 *@args: An arr args
 *
 *Return: The error
 */
char *err_127(char **args)
{
	char *err, *history_str;
	int length;

	history_str = _itoa(hist);
	if (!history_str)
		return (NULL);
	length = custom_strlen(name) + custom_strlen(history_str) +
		custom_strlen(args[0]) + 16;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(history_str);
		return (NULL);
	}
	custom_strcpy(err, name);
	custom_strcat(err, ": ");
	custom_strcat(err, history_str);
	custom_strcat(err, ": ");
	custom_strcat(err, args[0]);
	custom_strcat(err, ": cmd not found\n");
	free(history_str);
	return (err);
}
