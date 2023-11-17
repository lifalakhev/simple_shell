#include "shell.h"

/**
 * strchar - Locates the first occurrence of the character 'c' in string 's'.
 * @s: Pointer to the string in which to search for the character.
 * @c: Character to be located in the string.
 *
 * Return: Pointer to the first occurrence of 'c' in 's', or NULL if not found
 */
char *strchar(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

/**
 * get_environment - Retrieves environment variables from info structure.
 * @info: Pointer to the info structure.
 *
 * Return: Always 0
 */

char **get_environment(info_t *info)
{
	if (!info->environ || info->new_env)
	{
		info->environ = list_strings(info->env);
		info->new_env = 0;
	}

	return (info->environ);
}

/**
 * set_custom_env - Sets or updates a custom environment var in info structure.
 * @info: Pointer to the info structure.
 * @var: Variable name.
 * @value: Value of the variable.
 *
 * Return: 0 on success, 1 on failure.
 */

int set_custom_env(info_t *info, char *var, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buffer = malloc(_str_len(var) + _str_len(value) + 2);
	if (!buffer)
		return (1);
	_str_cpy(buffer, var);
	_str_cat(buffer, "=");
	_str_cat(buffer, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buffer;
			info->new_env = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->new_env = 1;
	return (0);
}

/**
 * unset_custom_env - Removes a custom environment variable from info structure
 * @info: Pointer to the info structure
 * @var: Variable name to be removed.
 *
 * Return: 1 if removed, 0 otherwise
 */

int unset_custom_env(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->new_env = delete_node_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->new_env);
}
