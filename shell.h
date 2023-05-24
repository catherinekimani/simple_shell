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
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <fcntl.h>

#define EXIT -3
#define END_OF_FILE -2

/**
  *struct lists_s - struct
  *@dir_path: A directory path.
  *@next: pointer
  */

typedef struct list_s
{
	char *dir_path;
	struct list_s *next;
} list_t;

/**
  *struct alias_s - structure for aliases
  *@name: alias name
  *@val: value of alias
  *@next: pointer
  */
typedef struct alias_s
{
	char *name;
	char *val;
	struct alias_s *next;
} alias_t;

/**
  *struct builtin_s - structure
  *@name: cmd name
  *@f: function pointer
  */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **av, char **start);
} builtin_t;

/*global variable */

char *name;
int history;
extern char **environ;
alias_t *alias;

/*macros*/

#define MAX_COMMAND_SIZE 20

/*prototypes*/

int fork_execute(char **args, char **start);
void display_prompt(int signal);
char *fill_path(char *path);
char *_location(char *cmd);
int file_commands(char *f_path, int *execute_res);

/*path prototypes*/

int path_check(char *str);
char *check_file(char *str);
/*string_utils*/
char *custom_strncat(char *dest, char *src, int n);
int custom_strlen(const char *str);
char *custom_strcat(char *dest, char *src);
char *custom_strcpy(char *dest, char *src);
int custom_strcmp(char *s1, char *s2);
int custom_strncmp(const char *s1, const char *s2, size_t n);
unsigned int custom_strspn(char *s, char *accept);
char *custom_strchr(char *s, char c);
/*custom_getline function*/
ssize_t custom_getline(char **custom_line_ptr,
			size_t *custom_n,
			FILE *custom_stream);
void *custom_realloc(void *ptr,
			unsigned int old_size_bytes,
			unsigned int new_size_bytes);
void update_line_ptr(char **line_ptr,
			size_t *size,
			char *buff,
			size_t buffer_size);
/*shell environments*/
int display_env_vars(char **args,
		     char __attribute__((__unused__)) **front_ptr);
int set_shell_env(char **args,
		  char __attribute__((__unused__)) **front_ptr);
int unset_shell_env(char **args,
			char __attribute__((__unused__)) **front_ptr);
char **get_env_val(const char *variable);
char **copy_env_var(void);
void free_env_vars(void);

/*alias prototypes*/
int execAliasCmd(char **args, char __attribute__((__unused__)) **front_ptr);
void setAliasValue(char *variable_name, char *new_value);
void display_alias(alias_t *alias);

/*helpers*/
void display_help_alias(void);
void help_builtin(void);
void display_help_exit(void);
void display_help_all(void);
void display_help_cd(void);
void display_help_set_env(void);
void display_help_env(void);
void display_help_unset_env(void);

/*built in */
int shell_change_dir(char **args,
		     char __attribute__((__unused__)) **front_ptr);
int shell_custom_exit(char **args, char **front_ptr);
int disp_shell_help(char **args,
		    char __attribute__((__unused__)) **front_ptr);
int (*find_builtin(char *cmd))(char **args, char **front_ptr);


/* list */

alias_t *add_alias(alias_t **head, char *name, char *val);
void free_alias(alias_t *head);
list_t *add_head_node(list_t **head, char *dir);
void free_linkedlist(list_t *head);



#endif /*SHELL_H*/
