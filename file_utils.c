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
	char *err, *history_str;
	int length;

	history_str = _itoa(hist);
	if (history_str)
		return (127);

	length = custom_strlen(name) + custom_strlen(f_path) +
		custom_strlen(f_path) + 16;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(history_str);
		return (127);
	}
	custom_strcpy(err, name);
	custom_strcat(err, ": ");
	custom_strcat(err, history_str);
	custom_strcat(err, ": cannot open");
	custom_strcat(err, f_path);
	custom_strcat(err, "\n");

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
	unsigned int old_size = 120;
	char *line, **args, **start;
	char buff[120];
	int res;
	ssize_t file, buff_read, j;

	hist = 0;

	file = open(f_path, O_RDONLY);
	if (file == -1)
	{
		*execute_res = _open(f_path);
		return (*execute_res);
	}
	line = malloc(sizeof(char) * old_size);
	if (line == NULL)
		return (-1);
	do {
		buff_read = read(file, buff, 119);
		if (buff_read == 0 && new_size == 0)
			return (*execute_res);
		buff[buff_read] = '\0';
		new_size += buff_read;
		line = custom_realloc(line, old_size, new_size);
		custom_strcat(line, buff);
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
	variable_replace(&line, execute_res);
	h_line(&line, new_size);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (check_arguments(args) != 0)
	{
		*execute_res = 2;
		free_argument(args, args);
		return (*execute_res);
	}
	start = args;
	for (j = 0; args[j]; j++)
	{
		if (custom_strncmp(args[j], ";", 1) == 0)
		{
			free(args[j]);
			args[j] = NULL;
			res = call_arguments(args, start, execute_res);
			args = &args[++j];
			j = 0;
		}
	}
	res = call_arguments(args, start, execute_res);
	free(start);
	return (res);
}
