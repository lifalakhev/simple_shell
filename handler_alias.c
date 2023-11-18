#include "shell.h"

/**
 * set_alias - Sets an alias in the info structure
 * @info: Pointer to the info structure
 * @alias_str: String containing the alias to be set
 *
 * Return: Returns 1 upon failure, 0 otherwise
 */

int set_alias(info_t *info, char *str)
{
	char *equal_pointer;

	equal_pointer = strchar(str, '=');
	if (!equal_pointer)
		return (1);
	if (!*++equal_pointer)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * unset_alias - Removes an alias from the info structure
 * @info: Pointer to the info structure
 * @alias_str: String containing the alias to be unset
 *
 * Return: Returns 1 upon failure to find the alias or deletion, 0 otherwise
 */

int unset_alias(info_t *info, char *str)
{
	char *equal_pointer, temp_char;
	int ret;

	equal_pointer = strchar(str, '=');
	if (!equal_pointer)
		return (1);
	temp_char = *equal_pointer;
	*equal_pointer = 0;
	ret = delete_node_index(&(info->alias),
			get_node_index(info->alias, node_starts_here(info->alias, str, -1)));
	*equal_pointer = temp_char;
	return (ret);
}

/**
 * print_alias - Prints an alias from a linked list.
 * @alias_node: Pointer to a node in the alias linked list.
 *
 * Return: 0 if node exists and prints successfully, 1 otherwise.
 */

int print_alias(list_t *node)
{
	char *equal_pointer = NULL, *a = NULL;

	if (node)
	{
		equal_pointer = strchar(node->str, '=');
		for (a = node->str; a <= equal_pointer; a++)
			_put_char(*a);
		_put_char('\'');
		_lvprint(equal_pointer + 1);
		_lvprint("'\n");
		return (0);
	}
	return (1);
}

/**
 * handle_alias - Handles the alias commands in the shell.
 * @info: Pointer to the info structure containing command arguments.
 *
 * Return: Always returns 0 to indicate successful execution.
 */

int handle_alias(info_t *info)
{
	int i = 0;
	char *equal_pointer = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		equal_pointer = strchar(info->argv[i], '=');
		if (equal_pointer)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_here(info->alias,
						info->argv[i], '='));
	}

	return (0);
}
