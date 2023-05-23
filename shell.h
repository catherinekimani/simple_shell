#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
/*macros*/
#define MAX_COMMAND_SIZE 20

/*prototypes*/
void display_prompt(void);
void fork_execute(char **argv, char *env[]);
/*path prototypes*/
int path_check(char *str);
char *check_file(char *str);
/*string_utils*/
char **_strtok(char *str);
int _strcmp(char *s1, char *s2);
char *_strcat(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
int _strlen(char *s);
/*custom functions*/
ssize_t custom_getline(char **custom_line_ptr,
		      size_t *custom_n,
		      FILE *custom_stream);
void update_line_ptr(char **line_ptr,
		     size_t *size,
		     char *buffer, size_t buffer_size);
void *custom_realloc(void *ptr,
		unsigned int old_size_bytes,
		unsigned int new_size_bytes);
char **custom_strtok(char *str, char *delim);
int custom_token_len(char *str, char *delim);
int custom_count_tokens(char *str, char *delim);
#endif /*SHELL_H*/
