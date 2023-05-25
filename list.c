#include "shell.h"

alias_t *add_alias(alias_t **head, char *name, char *val);
void free_alias(alias_t *head);
list_t *add_head_node(list_t **head, char *dir);
void free_linkedlist(list_t *head);

/**
  *add_alias - add alias
  *@head: head node pointer
  *@val: value
  *@name: name
  *Return: Null or a pointer to new node
  */
alias_t *add_alias(alias_t **head, char *name, char *val)
{
	alias_t *newNode = malloc(sizeof(alias_t));
	alias_t *endNode;

	if (!newNode)
		return (NULL);
	newNode->next = NULL;
	newNode->name = malloc(sizeof(char) * (custom_strlen(name) + 1));

	if (!newNode->name)
	{
		free(newNode);
		return (NULL);
	}
	newNode->val = val;
	custom_strcpy(newNode->name, name);

	if (*head)
	{
		endNode = *head;
		while (endNode->next != NULL)
			endNode = endNode->next;
		endNode->next = newNode;
	}
	else
		*head = newNode;
	return (newNode);
}

/**
 *add_head_node - Adds a node to the end of a linked list.
 *@head: A pointer to the head node
 *@dir: The directory path
 *
 *Return: NULL,Otherwise - a pointer to the new node.
 */
list_t *add_head_node(list_t **head, char *dir)
{
	list_t *newNode = malloc(sizeof(list_t));
	list_t *endNode;

	if (!newNode)
		return (NULL);
	newNode->dir_path = dir;
	newNode->next = NULL;

	if (*head)
	{
		endNode = *head;
		while (endNode->next != NULL)
			endNode = endNode->next;
		endNode->next = newNode;
	}
	else
		*head = newNode;
	return (newNode);
}

/**
 *free_alias - Frees a alias linked list
 *@head: THe head of the list.
 *Return: Nothing
 */
void free_alias(alias_t *head)
{
	alias_t *next;

	while  (head)
	{
		next = head->next;
		free(head->name);
		free(head->val);
		free(head);
		head = next;
	}

}

/**
 *free_linkedlist - Frees a linked list.
 *@head: The head of the list.
 */

void free_linkedlist(list_t *head)
{
	list_t *next;

	while (head)
	{
		next = head->next;
		free(head->dir_path);
		free(head);
		head = next;
	}
}
