#include "shell.h"

/**
 * add_node - adds a node to the start of the list.
 * @head: address of pointer to head node.
 * @str: str field of node.
 * @num: node index used by history.
 *
 * Return: size of list.
 */

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	memory_set_block((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _str_dup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list.
 * @head: address of pointer to head node.
 * @str: str field of node.
 * @num: node index used by history.
 *
 * Return: size of list.
 */

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	memory_set_block((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _str_dup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_string_list - prints only the str element of a list_t linked list.
 * @f: pointer to first node.
 *
 * Return: size of list.
 */

size_t print_string_list(const list_t *f)
{
	size_t i = 0;

	while (f)
	{
		_lvprint(f->str ? f->str : "(zero)");
		_lvprint("\n");
		f = f->next;
		i++;
	}
	return (i);
}

/**
 * free_list - frees all nodes of a list.
 * @head_pointer: address of pointer to head node.
 *
 * Return: void.
 */

void free_list(list_t **head_pointer)
{
	list_t *node, *next_node, *head;

	if (!head_pointer || !*head_pointer)
		return;
	head = *head_pointer;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_pointer = NULL;
}

/**
 * delete_node_index - deletes node at given index.
 * @head: address of pointer to first node.
 * @index: index of node to delete.
 *
 * Return: 1 on successful deletion, 0 on failure.
 */

int delete_node_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}
