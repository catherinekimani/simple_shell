#include "shell.h"

void h_line(char **line, ssize_t len);
ssize_t get_len(char *line);
void logic_ops(char *line, ssize_t *newer_len);

/**
 *h_line - Partitions a line
 *@line: Pointer to the line
 *@len: The length of line.
 *
 */

void h_line(char **line, ssize_t len)
{
	char *older_line, *newer_line;
	char prev, curr, next;
	size_t x, y;
	ssize_t newer_len;

	newer_len = get_len(*line);
	if (newer_len == len - 1)
		return;
	newer_line = malloc(newer_len + 1);
	if (!newer_line)
		return;
	y = 0;
	older_line = *line;
	for (x = 0; older_line[x]; x++)
	{
		curr = older_line[x];
		next = older_line[x + 1];
		if (x != 0)
		{
			prev = older_line[x - 1];
			if (curr == ';')
			{
				if (next == ';' && prev != ' ' && prev != ';')
				{
					newer_line[y++] = ' ';
					newer_line[y++] = ';';
					continue;
				}
				else if (prev == ';' && next != ' ')
				{
					newer_line[y++] = ';';
					newer_line[y++] = ' ';
					continue;
				}
				if (prev != ' ')
					newer_line[y++] = ' ';
				newer_line[y++] = ';';
				if (next != ' ')
					newer_line[y++] = ' ';
				continue;
			}
			else if (curr == '&')
			{
				if (next == '&' && prev != ' ')
					newer_line[y++] = ' ';
				else if (prev == '&' && next != ' ')
				{
					newer_line[y++] = '&';
					newer_line[y++] = ' ';
				}
			}
			else if (curr == '|')
			{
				if (next == '|' && prev != ' ')
					newer_line[y++]  = ' ';
				else if (prev == '|' && next != ' ')
				{
					newer_line[y++] = '|';
					newer_line[y++] = ' ';
					continue;
				}
			}
		}
		else if (curr == ';')
		{
			if (x != 0 && older_line[x - 1] != ' ')
				newer_line[y++] = ' ';
			newer_line[y++] = ';';
			if (next != ' ' && next != ';')
				newer_line[y++] = ' ';
			continue;
		}
		newer_line[y++] = older_line[x];
	}
	newer_line[y] = '\0';
	free(*line);
	*line = newer_line;
}
/**
 *get_len - Gets the new length of a line
 *@line: The line
 *
 *Return: The new length of the line.
 *
 */
ssize_t get_len(char *line)
{
	size_t x;
	ssize_t newer_len = 0;
	char curr, next;

	for (x = 0; line[x]; x++)
	{
		curr = line[x];
		next = line[x + 1];

		if (curr == '#')
		{
			if (x == 0 || line[x - 1] == ' ')
			{
				line[x] = '\0';
				break;
			}
		}
		else if (x != 0)
		{
			if (curr == ';')
			{
				if (next == ';' && line[x - 1] != ' ' && line[x - 1] != ';')
				{
					newer_len += 2;
					continue;
				}
				else if (line[x - 1] == ';' && next != ' ')
				{
					newer_len += 2;
					continue;
				}
				if (line[x - 1] != ' ')
					newer_len++;
				if (next != ' ')
					newer_len++;
			}
			else
				logic_ops(&line[x], &newer_len);
		}
		else if (curr == ';')
		{
			if (x != 0 && line[x - 1] != ' ')
				newer_len++;
			if (next != ' ' && next != ';')
				newer_len++;
		}
		newer_len++;
	}
	return (newer_len);
}
/**
 *logic_ops - Operators "||" or "&&"
 *@line: A pointer to the char
 *@newer_len: Pointer to new len
 */
void logic_ops(char *line, ssize_t *newer_len)
{
	char prev, curr, next;

	prev = *(line - 1);
	curr = *line;
	next = *(line + 1);

	if (curr == '&')
	{
		if (next == '&' && prev != ' ')
			(*newer_len)++;
		else if (prev == '&' && next != ' ')
			(*newer_len)++;
	}
	else if (curr == '|')
	{
		if (next == '|' && prev != ' ')
			(*newer_len)++;
		else if (prev == '|' && next != ' ')
			(*newer_len)++;

	}
}
