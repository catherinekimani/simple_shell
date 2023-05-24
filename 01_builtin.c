#include "shell.h"

/**
 * find_builtin - matches a command.
 * @cmd: command to match.
 *
 * Return: func pointer.
 */
int (*find_builtin(char *cmd))(char **args, char **front_ptr)
{
	builtin_t functions[] = {
		{"exit", shell_custom_exit},
		{"env", display_env_vars},
		{"setenv", set_shell_env},
		{"unsetenv", unset_shell_env},
		{"cd", shell_change_dir},
		{"alias", execAliasCmd},
		{"help", disp_shell_help},
		{NULL, NULL}};
	int idx;

	for (idx = 0; functions[idx].name; idx++)
	{
		if (custom_strcmp(functions[idx].name, cmd) == 0)
			break;
	}
	return (functions[idx].f);
}

/**
 * disp_shell_help - display help info for shell commands
 * @args: args
 * @front_ptr: double ptr
 *
 * Return: 0
 */
int disp_shell_help(char **args, char __attribute__((__unused__)) **front_ptr)
{
	if (!args[0])
		display_help_all();
	else if (custom_strcmp(args[0], "alias") == 0)
		display_help_alias();
	else if (custom_strcmp(args[0], "cd") == 0)
		display_help_cd();
	else if (custom_strcmp(args[0], "exit") == 0)
		display_help_exit();
	else if (custom_strcmp(args[0], "env") == 0)
		display_help_env();
	else if (custom_strcmp(args[0], "setenv") == 0)
		display_help_set_env();
	else if (custom_strcmp(args[0], "unsetenv") == 0)
		display_help_unset_env();
	else if (custom_strcmp(args[0], "help") == 0)
		help_builtin();
	else
		write(STDERR_FILENO, name, custom_strlen(name));
	return (0);
}

/**
 * shell_custom_exit - handles the exit command
 * @args: args passed
 * @front_ptr: double ptr
 *
 * Return: if successful function does not return
 */
int shell_custom_exit(char **args, char **front_ptr)
{
	unsigned int number = 0, max = 1 << (sizeof(int) * 8 - 1);
	int idx = 0, intLen = 10;

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			idx = 1;
			intLen++;
		}
		for (; args[0][idx]; idx++)
		{
			if (idx <= intLen && args[0][idx] >= '0' && args[0][idx] <= '9')
				number = (number * 10) + (args[0][idx] - '0');
			else
				return (generate_error(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (number > max - 1)
		return (generate_error(--args, 2));
	args -= 1;
	free_argument(args, front_ptr);
	free_env_vars();
	free_alias(alias);
	exit(number);
}

/**
 * shell_change_dir - changes the current dir of the shell.
 * @args: args arr.
 * @front_ptr: double pointer.
 *
 * Return: If the given str is not a dir - 2.
 */
int shell_change_dir(char **args, char __attribute__((__unused__)) **front_ptr)
{
	char **info_dir, *newLine = "\n";
	char *oldPwd = NULL, *pwd = NULL;
	struct stat directory;

	oldPwd = getcwd(oldPwd, 0);
	if (!oldPwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || custom_strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
				args[0][1] == '\0')
			{
				if (get_env_val("OLDPWD") != NULL)
					(chdir(*get_env_val("OLDPWD") + 7));
			}
			else
			{
				free(oldPwd);
				return (generate_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &directory) == 0 && S_ISDIR(directory.st_mode) &&
				((directory.st_mode & S_IXUSR) != 0))

				chdir(args[0]);
			else
			{
				free(oldPwd);
				return (generate_error(args, 2));
			}
		}
	}
	else
	{
		if (get_env_val("HOME") != NULL)
			chdir(*(get_env_val("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	info_dir = malloc(sizeof(char *) * 2);
	if (!info_dir)
		return (-1);

	info_dir[0] = "OLDPWD";
	info_dir[1] = oldPwd;
	if (set_shell_env(info_dir, info_dir) == -1)
		return (-1);

	info_dir[0] = "PWD";
	info_dir[1] = pwd;
	if (set_shell_env(info_dir, info_dir) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, custom_strlen(pwd));
		write(STDOUT_FILENO, newLine, 1);
	}
	free(oldPwd);
	free(pwd);
	free(info_dir);
	return (0);
}

