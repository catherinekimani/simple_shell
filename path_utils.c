#include "shell.h"

/**
 * check_file - func to check file in bin
 * @str: string to check
 *
 * Return: Pointer to string, NULL if false
*/
char *check_file(char *str)
{
	DIR *dir = opendir("/bin/");
	char *f_name, *cat;
	struct dirent *element;

	if (dir == NULL)
		return (NULL);
	element = readdir(dir);
	while (element != NULL)
	{
		f_name = element->d_name;
		if (_strcmp(f_name, str) == 0)
		{
			cat = _strcat("/bin/", str);
			closedir(dir);
			return (cat);
		}
		element = readdir(dir);
	}
	closedir(dir);
	return (NULL);
}
/**
 * path_check - checks for path
 * @str: string to check
 *
 * Return: Pointer
*/
int path_check(char *str)
{
	char *get_path = "/bin/", *ptr = NULL, *f = NULL;
	int idx = 0, p = 0;

	ptr = malloc(sizeof(char) * 50);
	if (ptr == NULL)
		return (0);
	while (get_path[idx] != '\0')
	{
		if (get_path[idx] != str[idx])
		{
			free(ptr);
			return (0);
		}
		idx++;
	}
	while (str[idx] != '\0')
	{
		ptr[p] = str[idx];
		p++;
		idx++;
	}
	ptr[p] = '\0';
	f = check_file(ptr);
	free(ptr);
	if (f != NULL)
	{
		free(f);
		return (1);
	}
	return (0);
}
