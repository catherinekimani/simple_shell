#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>

#define EXIT -3
#define END_OF_FILE -2

/*global variable */
extern char **environ;

char *name;
int hist;

/**
  *struct list_s- struct
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


alias_t *aliases;

/*prototypes*/

int fork_execute(char **args, char **start);
void display_prompt(int signal);
char *fill_path(char *path);
char *_location(char *cmd);
int file_commands(char *f_path, int *execute_res);

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
/*Tokenization*/
char **_strtok(char *line, char *delims);
int count_token(char *str, char *delims);
char **_strtok(char *line, char *delims);
/*shell environments*/
int display_env_vars(char **args,
		     char __attribute__((__unused__)) **start);
int set_shell_env(char **args,
		  char __attribute__((__unused__)) **start);
int unset_shell_env(char **args,
			char __attribute__((__unused__)) **start);
char **get_env_val(const char *variable);
char **copy_env_var(void);
void free_env_vars(void);

/*alias prototypes*/
int execAliasCmd(char **args, char __attribute__((__unused__)) **start);
void setAliasValue(char *variable_name, char *new_value);
void display_alias(alias_t *alias);
char **replace_alias(char **args);
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
		     char __attribute__((__unused__)) **start);
int shell_custom_exit(char **args, char **front_ptr);
int disp_shell_help(char **args,
		    char __attribute__((__unused__)) **start);
int (*find_builtin(char *cmd))(char **args, char **start);


/* list */

alias_t *add_alias(alias_t **head, char *name, char *val);
void free_alias(alias_t *head);
list_t *add_head_node(list_t **head, char *dir);
void free_linkedlist(list_t *head);

/* Helpers funtion prototype */
void free_argument(char **args, char **start);
char *get_pid(void);
char *get_env(char *begin, int length);
void variable_replace(char **args, int *execute_res);
void h_line(char **line, ssize_t read);
ssize_t get_len(char *line);
void logic_ops(char *line, ssize_t *newer_len);
char *get_arguments(char *line, int *execute_res);
int call_arguments(char **args, char **start, int *execute_res);
int run_arguments(char **args, char **start, int *execute_res);
int handle_arguments(int *execute_res);
int check_arguments(char **args);

/* Error */
char *error_exit(char **args);
char *error_envp(char **args);
char *error_syntax(char **args);
char *error_one(char **args);
char *error_cd(char **args);
char *err_126(char **args);
char *err_127(char **args);
int generate_error(char **args, int error);
int number_lengt(int number);
char *_itoa(int number);

#endif /*SHELL_H*/
