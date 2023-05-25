#include "shell.h"

int token_length(char *str, char *delims);
int count_token(char *str, char *delims);
char **_strtok(char *line, char *delims);

/**
 *token_length - Token length
 *@str: The string.
 *@delims: The delimiter char.
 *
 *Return: Delimeter index
 */

int token_length(char *str, char *delims)
{
	int idx = 0, length = 0;

	while (*(str + idx) && *(str + idx) != *delims)
	{
		length++;
		idx++;
	}
	return (length);
}

/**
 *count_token - Counts the number of delimited words
 *@str: The string
 *@delims: The delimiter char
 *
 *Return: The number of words in a str
 */

int count_token(char *str, char *delims)
{
	int idx, token = 0, length = 0;

	for (idx = 0; *(str + idx); idx++)
		length++;
	for (idx = 0; idx < length; idx++)
	{
		if (*(str + idx) != *delims)
		{
			token++;
			idx += token_length(str + idx, delims);
		}
	}
	return (token);
}

/**
 *_strtok - Custom string tokenizer
 *@line: The string
 *@delims: The delimiter char
 *
 *Return: pointer to an arr with the tokenized word.
 */

char **_strtok(char *line, char *delims)
{
	char **ptr;
	int idx = 0, token, i, let, j;

	token = count_token(line, delims);
	if (token == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (token + 2));
	if (!ptr)
		return (NULL);
	for (i = 0; i < token; i++)
	{
		while (line[idx] == *delims)
			idx++;
		let = token_length(line + idx, delims);

		ptr[i] = malloc(sizeof(char) * (let + 1));
		if (!ptr[i])
		{
			for (idx -= 1; idx >= 0; idx--)
				free(ptr[idx]);
			free(ptr);
			return (NULL);
		}
		for (j = 0; j < let; j++)
		{
			ptr[i][j] = line[idx];
			idx++;
		}
		ptr[i][1] = line[idx];
	}
	ptr[i] = NULL;
	ptr[i + 1] = NULL;
	return (ptr);
}
