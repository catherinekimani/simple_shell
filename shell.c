#include "shell.h"


/**
 * display_prompt - display prompt
*/
void display_prompt(void)
{
	const char *prompt_user = "Cisfun$  ";

	write(STDOUT_FILENO, prompt_user, strlen(prompt_user));
}
/**
 * main - entry point
 * @argc: No. of args
 * @av: Arr of args
 * @env: Environment var
 *
 * Return: 0 SUCCESS
*/
int main(int argc, char *av[], char *env[])
{
	char **user_input;
	char *f1, *ptr;
	size_t n = 20, pth = 5, check_builtin;
	ssize_t num_chars;

	if (argc > 1)
		av[1] = NULL;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			display_prompt();
		ptr = malloc(sizeof(char) * n);
		num_chars = getline(&ptr, &n, stdin);
		if (num_chars == -1)
		{
			free(ptr);
			exit(EXIT_FAILURE);
		}
		if (*ptr != '\n')
		{
			user_input = _strtok(ptr);
			if (_strcmp("exit", user_input[0]) == 0)
				break;
			check_builtin = check_builtins(user_input[0]);
			f1 = check_file(user_input[0]);
			if (check_builtin == 0 && f1 != NULL)
				user_input[0] = f1;
			pth = path_check(user_input[0]);
			if (pth == 1)
				fork_execute(user_input, env);
			if (f1 == NULL && pth == 0)
				printf("./hsh: No such file or directory\n");
			free(f1);
		}
		free(ptr);
		free(user_input);
	}
	exit(0);
}