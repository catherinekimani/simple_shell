#include "shell.h"

int _open(char *f_path);
int file_commands(char *f_path, int *execute_res);

/**
  *_open- if the file cannot be oppend
  *@f_path: file path
  *Return: Error
  */

int _open(char *f_path)
{
	char *err, history_str;
	int length;

	history_str = _itoa(history);
	if (history_str)
		return (127);

	length = _strlen(name) + _strlen(history_str) +
		_strlen(f_path) + 16;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(history_str);
		return (127);
	}
	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, history_str);
	_strcat(err, ": cannot open");
	_strcat(err, f_path);
	_strcat(err, "\n");

	free(history_str);
	write(STDERR_FILENO, err, length);
	free(err);

	return (127);
}
/**
  *file_commands - reads commands from a file
i  *@f_path: file path
  *@execute_res: results of the last executed command
  *Return: error or results of last command executed
  */
int file_commands(char *f_path, int *execute_res)
{
	unsigned int new_size = 0;
	unsigned int old_size = 100;
	char *line, **args, **start;
	char buff[100];
	int res;
	ssize_t file, buff_read, j;

	history = 0;

	file = open(f_path, O_RDONLY);
	if (file == -1)
	{
		execute_res = _open(f_path);
		return (*execute_res);
	}
	line = malloc(sizeof(char) * old_size);
	if (line == NULL)
		return (-1);
	do {
		buff_read = read(file, buff, 99);
		if (buff_read == 0 && new_size == 0)
			return (execute_res);
		buff[buff_read] = '\0';
		new_size += buff_read;
		line = custom_realloc(line, old_size, new_size);
		_strcat(line, buff);
		old_size = new_size;
	} while (buff_read);
	for (j = 0; line[j] == '\n'; j++)
		line[j] = ' ';
	for (; j < new_size; j++)
	{
		if (line[j] == '\n')
		{
			line[j] = ';';
			for (j += 1; j < new_size &&
				line[j] == '\n'; j++)
				line[j] = ' ';
		}
	}
	variable_replacement(&line, execute_res);
	handle_line(&line, new_size);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (check_arguments(args) != 0)
	{
		*execute_res = 2;
		free_args(args, args);
		return (*execute_res);
	}
	start = args;
	for (j = 0; args[j]; j++)
	{
		if (_strncmp(args[j], ";", 1) == 0)
		{
			free(args[j]);
			args[j] = NULL;
			res = call_args(args, start, execute_res);
			args = &args[++j];
			j = 0;
		}
	}
	res = call_args(args, start, execute_res);
	free(start);
	return (res);
}
