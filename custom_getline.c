#include "shell.h"

/**
 * custom_realloc - func to resize a memory block
 * @ptr: pointer to the previously allocated mem block
 * @old_size_bytes: size in bytes of the current mem block
 * @new_size_bytes: new size in bytes for the memory block
 *
 * Return: Pointer to the resized mem block
 */
void *custom_realloc(void *ptr,
			unsigned int old_size_bytes,
			unsigned int new_size_bytes)
{
	char *src, *dest;
	unsigned int idx;
	void *new_ptr;

	if (new_size_bytes == old_size_bytes)
		return (ptr); /*checks if old size is equal*/

	if (ptr == NULL)
	{
		new_ptr = malloc(new_size_bytes);
		if (new_ptr == NULL)
			return (NULL);
		return (new_ptr);
	}
	if (new_size_bytes == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	src = ptr;
	new_ptr = malloc(sizeof(*src) * new_size_bytes);
	if (new_ptr == NULL)
	{
		free(ptr);
		return (NULL);
	}
	dest = new_ptr;
	for (idx = 0; idx < old_size_bytes && idx < new_size_bytes; idx++)
		dest[idx] = *src++;
	free(ptr);
	return (new_ptr);
}

/**
 * update_line_ptr - updates
 * @line_ptr: pointer line_ptr variable
 * @size: szie of the line_ptr
 * @buff:string
 * @buffer_size: size of buffer
*/
void update_line_ptr(char **line_ptr,
			size_t *size,
			char *buff,
			size_t buffer_size
			)
{
	if (*line_ptr == NULL)
	{
		if (buffer_size > 120)
			*size = buffer_size;
		else
			*size = 120;
		*line_ptr = buff;
	}
	else if (*size < buffer_size)
	{
		if (buffer_size > 120)
			*size = buffer_size;
		else
			*size = 120;
		*line_ptr = buff;
	}
	else
	{
		custom_strcpy(*line_ptr, buff);
		free(buff);
	}
}

/**
 * custom_getline - custom implementation of getline func
 * @custom_line_ptr: pointer to buffer storing the read line
 * @custom_n: pointer to the size of the buffer
 * @custom_stream: FILE stream to read from
 *
 * Return: number of characters read else -1
 */
ssize_t custom_getline(char **custom_line_ptr,
			size_t *custom_n,
			FILE *custom_stream)
{
	static ssize_t custom_input;
	ssize_t custom_result;
	int custom_read;
	char custom_c = 'x', *custom_buffer;

	if (custom_input == 0)
		fflush(custom_stream);
	else
		return (-1);
	custom_input = 0;
	custom_buffer = malloc(sizeof(char) * 120);
	if (!custom_buffer)
		return (-1);
	while (custom_c != '\n')
	{
		custom_read = read(STDIN_FILENO, &custom_c, 1);
		if (custom_read == -1 || (custom_read == 0 && custom_input == 0))
		{
			free(custom_buffer);
			return (-1);
		}
		if (custom_read == 0 && custom_input != 0)
		{
			custom_input++;
			break;
		}
		if (custom_input >= 120)
			custom_buffer = custom_realloc(custom_buffer,
							custom_input,
							custom_input + 1
							);
		custom_buffer[custom_input] = custom_c;
		custom_input++;
	}
	custom_buffer[custom_input] = '\0';
	update_line_ptr(custom_line_ptr, custom_n, custom_buffer, custom_input);
	custom_result = custom_input;
	if (custom_read != 0)
		custom_input = 0;
	return (custom_result);
}
