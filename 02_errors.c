#include "shell.h"

char *error_exit(char **args);
char *error_envp(char **args);
char *error_syntax(char **args);
char *error_one(char **args);
char *error_cd(char **args);

/**
 *error_envp - Creates an error messag for envp
 *@args: An array of args.
 *
 *Return: The error
 */

char *error_envp(char **args)
{
	char *err, *history_str;
	int length;

	history_str = _itoa(hist);
	if (!history_str)
		return (NULL);
	args--;
	length = custom_strlen(name) + custom_strlen(history_str) +
		custom_strlen(args[0]) + 45;
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
	custom_strcat(err, ": Unable to add or remove from environ\n");
	free(history_str);
	return (err);
}
/**
 *error_exit - Creates an error message for exit
 *@args: An array of arg
 *
 *Return: The error
 */

char *error_exit(char **args)
{
	char *err, *history_str;
	int length;

	history_str = _itoa(hist);

	if (!history_str)
		return (NULL);
	length = custom_strlen(name) + custom_strlen(history_str) +
		custom_strlen(args[0]) + 27;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(history_str);
		return (NULL);
	}
	custom_strcpy(err, name);
	custom_strcat(err, ": ");
	custom_strcat(err, history_str);
	custom_strcat(err, ": exit: not found number: ");
	custom_strcat(err, args[0]);
	custom_strcat(err, "\n");
	free(history_str);
	return (err);
}
/**
 *error_one - Creates an error message for alias
 *@args: An array of args
 *
 *Return: The error
 */
char *error_one(char **args)
{
	int length;
	char *err;

	length = custom_strlen(name) + custom_strlen(args[0]) + 13;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
		return (NULL);
	custom_strcpy(err, "alias: ");
	custom_strcat(err, args[0]);
	custom_strcat(err, " could not be found\n");
	return (err);
}
/**
 *error_cd - Creates an error msg for cd
 *@args: An array of args
 *Return: The error
 */
char *error_cd(char **args)
{
	char *err, *history_str;
	int length;

	history_str = _itoa(hist);
	if (!history_str)
		return (NULL);
	if (args[0][0] == '-')
		args[0][2] = '\0';
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
	if (args[0][0] == '-')
		custom_strcat(err, ":cd: not allowed option ");
	else
		custom_strcat(err, ":cd: can't change dir to ");
	custom_strcat(err, args[0]);
	custom_strcat(err, "\n");
	free(history_str);
	return (err);
}
/**
 *error_syntax - Error msg for syntax.
 *@args: An array of args
 *
 *Return: The error
 */

char *error_syntax(char **args)
{
	int length;
	char *err, *history_str;

	history_str = _itoa(hist);
	if (!history_str)
		return (NULL);
	length = custom_strlen(name) + custom_strlen(history_str) +
		custom_strlen(args[0]) + 33;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(history_str);
		return (NULL);
	}
	custom_strcpy(err, name);
	custom_strcat(err, ": ");
	custom_strcat(err, history_str);
	custom_strcat(err, ":syntax error: \"");
	custom_strcat(err, args[0]);
	custom_strcat(err, "\" not expected\n");
	free(history_str);
	return (err);
}
