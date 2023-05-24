#include "shell.h"

/**
 * display_help_set_env - display info about set env command
 */
void display_help_set_env(void)
{
	char *message = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, message, custom_strlen(message));
	message = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, message, custom_strlen(message));
	message = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, message, custom_strlen(message));
}

/**
 * display_help_unset_env - display info about unset env command
 */
void display_help_unset_env(void)
{
	char *message = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, message, custom_strlen(message));
	message = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, message, custom_strlen(message));
	message = "message to stderr.\n";
	write(STDOUT_FILENO, message, custom_strlen(message));
}

/**
 * display_help_env - display info about env command
 */
void display_help_env(void)
{
	char *message = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, message, custom_strlen(message));
}
