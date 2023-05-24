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
  *@nam2: cmd name
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

char **_strtok(char *str);
int _strcmp(char *s1, char *s2);
char *_strcat(char *s1, char *s2);
/*built in */

/*int check_builtins(char *str);*/

/* list */

alias_t *add_alias(alias_t **head, char *name, char *val);
void free_alias(alias_t *head);
list_t *add_head_node(list_t **head, char *dir);
void free_linkedlist(list_t *head);

#endif /*SHELL_H*/
