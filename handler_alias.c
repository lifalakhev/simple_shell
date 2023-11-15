#include "shell.h"

/**
 * set_alias - Sets an alias in the info structure
 * @info: Pointer to the info structure
 * @alias_str: String containing the alias to be set
 *
 * Return: Returns 1 upon failure, 0 otherwise
 */

int set_alias(info_t *info, char *alias_str)
{
	char *equal_pointer;

	equal_pointer = strchar(alias_str, '=');
	if (!equal_pointer)
		return (1);
	if (!*++equal_pointer)
		return (unset_alias(info, alias_str));

	unset_alias(info, alias_str);
	return (add_node_end(&(info->alias), alias_str, 0) == NULL);
}

/**
 * unset_alias - Removes an alias from the info structure
 * @info: Pointer to the info structure
 * @alias_str: String containing the alias to be unset
 *
 * Return: Returns 1 upon failure to find the alias or deletion, 0 otherwise
 */

int unset_alias(info_t *info, char *alias_str)
{
	char *equal_pointer, temp_char;
	int ret;

	equal_pointer = strchar(alias_str, '=');
	if (!equal_pointer)
		return (1);
	temp_char = *equal_pointer;
	*equal_pointer = 0;
	ret = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, alias_str, -1)));
	*equal_pointer = temp_char;
	return (ret);
}

/**
 * print_alias - Prints an alias from a linked list.
 * @alias_node: Pointer to a node in the alias linked list.
 *
 * Return: 0 if node exists and prints successfully, 1 otherwise.
 */

int print_alias(list_t *alias_node)
{
	char *equal_pointer = NULL, *a = NULL;

	if (alias_node)
	{
		equal_pointer = strchar(alias_node->alias_str, '=');
		for (a = alias_node->alias_str; a <= equal_pointer; a++)
			_putchar(*a);
		_putchar('\'');
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
	list_t *alias_node = NULL;

	if (info->argc == 1)
	{
		alias_node = info->alias;
		while (alias_node)
		{
			print_alias(alias_node);
			alias_node = alias_node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		equal_pointer = strchar(info->argv[i], '=');
		if (equal_pointer)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias,
						info->argv[i], '='));
	}

	return (0);
}
