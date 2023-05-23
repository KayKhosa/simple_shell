#include "shell.h"

/**
 * _getenv - gets the value of the environment variable
 * @name: name of the environment variable
 * Return: value of the environment variable
 */
char *_getenv(const char *name)
{
	int i;
	size_t len;

	if (name == NULL)
		return NULL;

	len = strlen(name);
	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(name, environ[i], len) == 0 && environ[i][len] == '=')
			return &(environ[i][len + 1]);
	}

	return NULL;
}

/**
 * add_node_end - adds a new node at the end of a list_path list
 * @head: pointer to pointer to the head of the list
 * @str: string to be stored in the new node
 * Return: address of the new element/node
 */
list_path *add_node_end(list_path **head, const char *str)
{
	list_path *new_node = malloc(sizeof(list_path));
	list_path *last;

	if (new_node == NULL || str == NULL)
		return NULL;

	new_node->dir = _strdup(str);
	new_node->p = NULL;

	if (*head == NULL)
	{
		*head = new_node;
		return new_node;
	}

	last = *head;
	while (last->p != NULL)
		last = last->p;

	last->p = new_node;
	return new_node;
}

/**
 * linkpath - creates a linked list of path directories
 * @path: string of path value
 * Return: pointer to the created linked list
 */
list_path *linkpath(const char *path)
{
	list_path *head = NULL;
	char *token, *cpath, *token_copy;

	if (path == NULL)
		return NULL;

	cpath = _strdup(path);
	if (cpath == NULL)
		return NULL;

	token = strtok_r(cpath, ":", &token_copy);
	while (token != NULL)
	{
		add_node_end(&head, token);
		token = strtok_r(NULL, ":", &token_copy);
	}

	free(cpath);
	return head;
}

/**
 * _which - finds the full pathname of a given file or command
 * @filename: name of the file or command
 * @head: pointer to the head of the linked list of path directories
 * Return: full pathname of the file or command, or NULL if not found
 */
char *_which(const char *filename, const list_path *head)
{
	struct stat st;
	char *pathname;
	const list_path *tmp;

	if (filename == NULL || head == NULL)
		return NULL;

	tmp = head;
	while (tmp != NULL)
	{
		pathname = concat_all(tmp->dir, "/", filename);
		if (pathname == NULL)
			return NULL;

		if (stat(pathname, &st) == 0)
			return pathname;

		free(pathname);
		tmp = tmp->p;
	}

	return NULL;
}

/**
 * free_list - frees a list_path
 * @head: pointer to the head of the list
 */
void free_list(list_path *head)
{
	list_path *current, *tmp;

	current = head;
	while (current != NULL)
	{
		tmp = current;
		current = current->p;
		free(tmp->dir);
		free(tmp);
	}
}
