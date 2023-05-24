#include "shell.h"

/**
 * custom_strncat -  function that concatenates two strings.
 * @dest: append string
 * @src: string from which ‘n’ characters are going to append
 * @n: number of characters to be appended
 * Return: a pointer
 */
char *custom_strncat(char *dest, char *src, int n)
{
	int i, src_idx;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (src_idx = 0; src[src_idx] != '\0' && n > 0; src_idx++, n--, i++)
	{
		dest[i] = src[src_idx];
	}
	return (dest);
}

/**
 *  custom_strlen -  function that returns the len of a str
 *  @str: Character to be checked
 *  Return: 0;
 */
int custom_strlen(const char *str)
{
	int len = 0;

	if (!str)
		return (len);
	for (len = 0; str[len]; len++)
		;
	return (len);
}

/**
 * custom_strcmp - function that compares two strings
 * @s1: first string to be comparedd
 * @s2: second string to be compared
 * Return: 0;
 */
int custom_strcmp(char *s1, char *s2)
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
 * custom_strcat - function appends the src string to the dest string
 * @dest: pointer to character
 * @src: pointer to charcter
 * Return: a pointer
 */
char *custom_strcat(char *dest, char *src)
{
	int i, src_index;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (src_index = 0; src[src_index] != '\0'; src_index++)
	{
		dest[i] = src[src_index];
		i++;
	}

	dest[i] = '\0';
	return (dest);
}

/**
 * custom_strcpy - function that copies the string pointed to by src,
 * including the terminating null byte (\0),
 * to the buffer pointed to by dest.
 * @dest: point to character
 * @src: pointer to character
 * Return: the pointer to dest
 */
char *custom_strcpy(char *dest, char *src)
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

