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
	struct stat st;

	path = get_env_val("PATH");
	if (!path || !(*path))
		return (NULL);
	dir = get_path(*path + 5);
	head = dir;

	while (dir)
	{
		temp = malloc(custom_strlen(dir->dir_path) + custom_strlen(cmd) + 2);
		if (!temp)
			return (NULL);
		custom_strcpy(temp, dir->dir_path);
		custom_strcat(temp, "/");
		custom_strcat(temp, cmd);
		if (stat(temp, &st) == 0)
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

	pwd = *(get_env_val("PWD")) + 4;
	for (j = 0; path[j]; j++)
	{
		if (path[j] == ':')
		{
			if (path[j + 1] == ':' || j == 0 || path[j + 1] == '\0')
				len += custom_strlen(pwd) + 1;
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
				custom_strcat(path_, pwd);
				custom_strcat(path_, ":");
			}
			else if (path[j + 1] == ':' || path[j + 1] == '\0')
			{
				custom_strcat(path_, ":");
				custom_strcat(path_, pwd);
			}
			else
				custom_strcat(path_, ":");
		}
		else
		{
			custom_strncat(path_, &path[j], 1);
		}
	}
	return (path_);
}
