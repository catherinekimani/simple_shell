#include "shell.h"

/**
 * execAliasCmd - executes alias cmd
 * @args: args passed
 * @front_ptr: ptr to the front
 *
 * Return: Return value
 */
int execAliasCmd(char **args, char __attribute__((__unused__)) **front_ptr)
{
	alias_t *current_alias = alias;
	char *val;
	int return_value = 0, idx;

	if (!args[0])
	{
		while (current_alias)
		{
			display_alias(current_alias);
			current_alias = current_alias->next;
		}
		return (return_value);
	}
	for (idx = 0; args[idx]; idx++)
	{
		current_alias = alias;
		val = custom_strchr(args[idx], '=');
		if (!val)
		{
			while (current_alias)
			{
				if (custom_strcmp(args[idx], current_alias->name) == 0)
				{
					display_alias(current_alias);
					break;
				}
				current_alias = current_alias->next;
			}
			if (!current_alias)
				return_value = create_error(args + idx, 1);
		}
		else
			setAliasValue(args[idx], val);
	}
	return (return_value);
}

/**
 * setAliasValue - set value of an alias
 * @variable_name: name of alias variable
 * @new_value: New value to assign
 */
void setAliasValue(char *variable_name, char *new_value)
{
	alias_t *temp_alias = alias;
	char *fmtValue;
	int length, idx1, idx2;

	*new_value = '\0';
	new_value++;
	length = custom_strlen(new_value) - custom_strspn(new_value, "'\"");
	fmtValue = malloc(sizeof(char) * (length + 1));
	if (!fmtValue)
		return;
	for (idx1 = 0, idx2 = 0; new_value[idx1]; idx1++)
	{
		if (new_value[idx1] != '\'' && new_value[idx1] != '"')
			fmtValue[idx2++] = new_value[idx1];
	}
	fmtValue[idx2] = '\0';
	while (temp_alias)
	{
		if (custom_strcmp(variable_name, temp_alias->name) == 0)
		{
			free(temp_alias->val);
			temp_alias->val = fmtValue;
			break;
		}
		temp_alias = temp_alias->next;
	}
	if (!temp_alias)
		add_alias(&alias, variable_name, fmtValue);
}

/**
 * display_alias - displays formatted alias str
 * @alias: ptr to alias struct
 */
void display_alias(alias_t *alias)
{
	int length = custom_strlen(alias->name) + custom_strlen(alias->val) + 4;
	char *fmtAlias;

	fmtAlias = malloc(sizeof(char) * (length + 1));
	if (!fmtAlias)
		return;

	custom_strcpy(fmtAlias, alias->name);
	custom_strcat(fmtAlias, "='");
	custom_strcat(fmtAlias, alias->val);
	custom_strcat(fmtAlias, "'\n");

	write(STDOUT_FILENO, fmtAlias, length);
	free(fmtAlias);
}
