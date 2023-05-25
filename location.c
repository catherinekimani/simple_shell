#include "shell.h"

char *fill_path(char *path);
list_t *get_path(char *path);

/**
  *_location - Locates a cmd
  *@cmd: the command
  *
  *Return: 0 success
 */

char *_location(char *cmd)
{
	char **path, *temp;
	list_t *dir, *head;
	struct state st;

	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);
	dir = get_path(*path + 5);
	head = dir;

	while (dir)
	{
		temp = malloc(_strlen(dir->dir_path) + _strlen(cmd) + 2);
		if (!temp)
			return (NULL);
		_strcpy(temp, dir->dir_path);
		_strcat(temp, "/");
		_strcat(temp, cmd);
		if (state(temp, &st) == 0)
		{
			free_linkedlist(head);
			return (temp);
		}
		dir = dir->next;
		free(temp);
	}
	free_linkedlist(head);
	return (NULL);
}
/**
  * get_path - get path
  *@path: the path
  *Return: pointer
  */
list_t *get_path(char *path)
{
	int idx;
	char **dir, *path_;
	list_t *head = NULL;

	path_ = fill_path(path);
	if (!path_)
		return (NULL);
	dir = _strtok(path_, ":");
	free(path_);
	if (!dir)
		return (NULL);
	for (idx = 0; dir[idx]; idx++)
	{
		if (add_head_node(&head, dir[idx]) == NULL)
		{
			free_linkedlist(head);
			free(dir);
			return (NULL);
		}
	}
	free(dir);
	return (head);
}
/**
  *fill_path - copies path
  *@path: the path
  *
  *Return: Modified path
  */
char *fill_path(char *path)
{
	char *path_, *pwd;
	int j, len = 0;

	pwd = *(_getenv("PWD")) + 4;
	for (j = 0; path[j]; j++)
	{
		if (path[j] == ':')
		{
			if (path[j + 1] == ':' || j == 0 || path[j + 1] == '\0')
				len += _strlen(pwd) + 1;
			else
				len++;
		}
		else
			len++;
	}
	path_ = malloc(sizeof(char) * (len + 1));
	if (!path_)
		return (NULL);
	path_[0] = '\0';
	for (j = 0; path[j]; j++)
	{
		if (path[j] == ':')
		{
			if (j == 0)
			{
				_strcat(path_, pwd);
				_strcat(path_, ":");
			}
			else if (path[j + 1] == ':' || path[j + 1] == '\0')
			{
				_strcat(path_, ":");
				_strcat(path_, pwd);
			}
			else
				_strcat(path_, ":");
		}
		else
		{
			_strncat(path_, &path[j], 1);
		}
	}
	return (path_);
}
