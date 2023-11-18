#include "shell.h"

/**
 * print_list - Prints the content of each node in a linked list.
 * @f: Pointer to the head of the linked list.
 *
 * Return: The number of nodes in the linked list.
 */

size_t print_list(const list_t *f)
{
	size_t i = 0;

	while (f)
	{
		_lvprint(converts_num(f->num, 10, 0));
		_put_char(':');
		_put_char(' ');
		_lvprint(f->str ? f->str : "(zero)");
		_lvprint("\n");
		f = f->next;
		i++;
	}
	return (i);
}

/**
 * list_l - Computes the length of a linked list.
 * @f: Pointer to the head of the linked list.
 *
 * Return: The number of nodes in the linked list.
 */

size_t list_l(const list_t *f)
{
	size_t i = 0;

	while (f)
	{
		f = f->next;
		i++;
	}
	return (i);
}

/**
 * get_node_index - gets index of a node.
 * @head: pointer to list head.
 * @node: pointer to the node.
 *
 * Return: index of node or -1
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

/**
 * node_starts_here - Returns node whose string starts with prefix.
 * @node: pointer to list head.
 * @prefix: string to match
 * @c: the next character after prefix to match.
 *
 * Return: NULL or match
 */

list_t *node_starts_here(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * list_strings - Creates an array of strings from a linked list of strings.
 * @head: Pointer to the head of the linked list.
 *
 * Return: Pointer to the array of strings on success.
 *   NULL if 'head' is NULL or if memory allocation fails.
 */

char **list_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_l(head), j;
	char **strings;
	char *str;

	if (!head || !i)
		return (NULL);
	strings = malloc(sizeof(char *) * (i + 1));
	if (!strings)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_str_len(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strings[j]);
			free(strings);
			return (NULL);
		}

		str = _str_cpy(str, node->str);
		strings[i] = str;
	}
	strings[i] = NULL;
	return (strings);
}
