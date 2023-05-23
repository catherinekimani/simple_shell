#include "shell.h"

/**
 * _strtok - tokenize string
 * @str: string to tokenize
 *
 * Return: Pointer
 */

char **_strtok(char *str)
{
	char **token = NULL, *parse = NULL;
	int idx = 0, p = 0;

	token = malloc(8 * sizeof(char *));
	if (token == NULL)
	{
		perror("Can't allocate memory");
		exit(EXIT_FAILURE);
	}
	parse = strtok(str, " ");
	while (parse != NULL)
	{
		while (parse[p])
		{
			if (parse[p] == '\n')
				parse[p] = '\0';
			p++;
		}
		token[idx] = parse;
		idx++;
		p = 0;
		parse = strtok(NULL, " ");
	}
	token[idx] = NULL;
	return (token);
}

/**
 * _strcmp - function that compares two strings
 * @s1: first string to be comparedd
 * @s2: second string to be compared
 * Return: 0;
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0')
		{
			return (0);
		}
		i++;
	}
	return (s1[i] - s2[i]);
}

/**
 * _strcat - concatenates two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: pointer to the concatenated string, or NULL on failure
 */
char *_strcat(char *s1, char *s2)
{
	char *concat = NULL;
	int len1 = 0, len2 = 0, i, j = 0;

	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";

	while (s1[len1])
		len1++;

	while (s2[len2])
		len2++;

	concat = malloc(sizeof(char) * (len1 + len2 + 1));
	if (concat == NULL)
		return (NULL);

	for (i = 0; i < len1; i++)
		concat[i] = s1[i];

	for (j = 0; j < len2; j++)
		concat[i + j] = s2[j];

	concat[i + j] = '\0';
	return (concat);
}

/**
 * _strcpy - function that copies the string pointed to by src,
 * including the terminating null byte (\0),
 * to the buffer pointed to by dest.
 * @dest: point to character
 * @src: pointer to character
 * Return: the pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int length, i;

	length = 0;

	while (src[length] != '\0')
	{
		length++;
	}

	for (i = 0; i < length; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';

	return (dest);
}

/**
 *  _strlen -  function that returns the length of a string
 *  @s: Character to be checked
 *  Return: 0;
 */
int _strlen(char *s)
{
	int length;

	length = strlen(s);
	return (length);
}
