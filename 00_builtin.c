#include "shell.h"

/**
 * execAliasCmd - executes alias cmd
 * @args: args passed
 * @start: ptr to the start
 *
 * Return: Return value
 */
int execAliasCmd(char **args, char __attribute__((__unused__)) **start)
{
	alias_t *current_alias = aliases;
	char *val;
	int ret_value = 0, idx;

	if (!args[0])
	{
		while (current_alias)
		{
			display_alias(current_alias);
			current_alias = current_alias->next;
		}
		return (ret_value);
	}
	for (idx = 0; args[idx]; idx++)
	{
		current_alias = aliases;
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
				ret_value = generate_error(args + idx, 1);
		}
		else
			setAliasValue(args[idx], val);
	}
	return (ret_value);
}

/**
 * setAliasValue - set value of an alias
 * @variable_name: name of alias variable
 * @val: New value to assign
 */
void setAliasValue(char *variable_name, char *val)
{
	alias_t *temp_alias = aliases;
	char *fmtValue;
	int length, idx1, idx2;

	*val = '\0';
	val++;
	length = custom_strlen(val) - custom_strspn(val, "'\"");
	fmtValue = malloc(sizeof(char) * (length + 1));
	if (!fmtValue)
		return;
	for (idx1 = 0, idx2 = 0; val[idx1]; idx1++)
	{
		if (val[idx1] != '\'' && val[idx1] != '"')
			fmtValue[idx2++] = val[idx1];
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
		add_alias(&aliases, variable_name, fmtValue);
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

/**
 * replace_alias - replace any matching alias
 * @args: args.
 *
 * Return: pointer.
 */
char **replace_alias(char **args)
{
	alias_t *tempAlias;
	int idx;
	char *newValue;

	if (custom_strcmp(args[0], "alias") == 0)
		return (args);
	for (idx = 0; args[idx]; idx++)
	{
		tempAlias = aliases;
		while (tempAlias)
		{
			if (custom_strcmp(args[idx], tempAlias->name) == 0)
			{
				newValue = malloc(sizeof(char) * (custom_strlen(tempAlias->val) + 1));
				if (!newValue)
				{
					free_argument(args, args);
					return (NULL);
				}
				custom_strcpy(newValue, tempAlias->val);
				free(args[idx]);
				args[idx] = newValue;
				idx--;
				break;
			}
			tempAlias = tempAlias->next;
		}
	}

	return (args);
}
