#include "shell.h"

int generate_error(char **args, int error);
int number_length(int number);
char *_itoa(int number);

/**
 *generate_error - Generate a custom error
 *@args: An array of args
 *@error: The error
 *
 *Return: The error
 */
int generate_error(char **args, int error)
{
	char *err;

	switch (error)
	{
		case -1:
			err = error_envp(args);
			break;
		case 1:
			err = error_one(args);
			break;
		case 2:
			if (*(args[0]) == 'e')
				err = error_exit(++args);
			else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
				err = error_syntax(args);
			else
				err = error_cd(args);
			break;
		case 126:
			err = err_126(args);
			break;
		case 127:
			err = err_127(args);
			break;
	}
	write(STDERR_FILENO, err, custom_strlen(err));
	if (err)
		free(err);
	return (error);
}
/**
 *_itoa - Converts an int to a str
 *@number: The int
 *
 *Return: The converted str
 */
char *_itoa(int number)
{
	int length = number_length(number);
	char *buff;
	unsigned int n1;

	buff = malloc(sizeof(char) * (length + 1));
	if (!buff)
		return (NULL);
	buff[length] = '\0';
	if (number < 0)
	{
		n1 = number * -1;
		buff[0] = '-';
	}
	else
	{
		n1 = number;
	}
	length--;
	do {
		buff[length] = (n1 % 10) + '0';
		n1 /= 10;
		length--;
	} while (n1 > 0);
	return (buff);
}
/**
 *number_length - Find len of a number
 *@number: The number.
 *
 *Return:length.
 */

int number_length(int number)
{
	unsigned int n1;
	int length = 1;

	if (number < 0)
	{
		length++;
		n1 = number * -1;
	}
	else
	{
		n1 = number;
	}
	while (n1 > 9)
	{
		length++;
		n1 /= 10;
	}
	return (length);
}
