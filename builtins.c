#include "shell.h"

/**
  *check_builtins - Checks built cmd
  *
  *@str: The string to check
  *
  *Return: 1 (success), 0 (failure)
  */

int check_builtins(char *str)
{

	char *array[] = {"cd", "exit"};
	int idx = 0;
	char **arr;

	arr = malloc(sizeof(char *) * 2);
	if (arr == NULL)
		return (0);
	array[0] = "cd";
	array[1] = "exit";

	for (idx = 0; idx < 2; idx++)
	{
		if (_strcmp(array[idx], str) == 0)
		{
			printf("Built in cmd found");
			break;
		}
		idx++;
	}
	switch (idx)
	{
		case 0:
			chdir(str);
			return (1);
		case 1:
			printf("See you bye");
			return (2);
		default:
			return (0);
	}
	return (0);
}
