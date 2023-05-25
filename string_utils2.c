#include "shell.h"

/**
 * custom_strncmp - compare two strs.
 * @s1: ptr to a string.
 * @s2: ptr to a string.
 * @n: first n bytes of the strs to compare.
 *
 * Return: Less than 0 if s1 is shorter than s2.
 *         0 if s1 and s2 match.
 */
int custom_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t j;

	for (j = 0; s1[j] && s2[j] && j < n; j++)
	{
		if (s1[j] > s2[j])
			return (s1[j] - s2[j]);
		else if (s1[j] < s2[j])
			return (s1[j] - s2[j]);
	}
	if (j == n)
		return (0);
	else
		return (-15);
}

/**
 * custom_strspn- function that gets the length of a prefix substring
 * @s: string to be checked
 * @accept: characters
 * Return:  number of bytes in the initial segment of s
 */
int custom_strspn(char *s, char *accept)
{
	int i = 0;
	int j;

	while (*s)
	{
		for (j = 0; accept[j]; j++)
		{
			if (*s == accept[j])
			{
				i++;
				break;
			}
		}
		s++;
	}
	return (i);
}

/**
 * custom_strchr - function that locates a character in astring
 * @s: string to be checked
 * @c: character to be searched
 * Return: pointer
 */
char *custom_strchr(char *s, char c)
{
	int idx;

	for (idx = 0; s[idx]; idx++)
	{
		if (s[idx] == c)
			return (s + idx);
	}
	return (NULL);
}
