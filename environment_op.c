#include "shell.h"

/**
 * get_env_var - Retrieves the value of specific environment variable.
 * @info: Pointer to the structure containing environment variables.
 * @name: Name of the environment variable to search for.
 *
 * Return: The value of the specified environment variable 'name' if found,
 * otherwise, returns NULL.
 */

char *get_env_var(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *value;

	while (node)
	{
		value = starts_with(node->str, name);
		if (value && *value)
			return (value);
		node = node->next;
	}
	return (NULL);
}

/**
 * initial_env_list - Initializes the environment variables list.
 * @info: Pointer to the structure containing environment variables.
 *
 * Return: Always returns 0 to indicate successful initialization.
 */

int initial_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

/**
 * print_environ_info - Prints the list of environment variables.
 * @info: Pointer to the structure containing environment variables
 *
 * Return: Always returns 0 to indicate successful execution.
 */

int print_environ_info(info_t *info)
{
	print_string_list(info->env);
	return (0);
}

/**
 * set_env_var - Sets a custom environment variable.
 * @info: Pointer to structure containing info about environment variables.
 *
 * Return: 0 on successful setting of the custom environment variable. Return 1
 * in case of an incorrect number of arguments or failure to set the variable.
 */

int set_env_var(info_t *info)
{
	if (info->argc != 3)
	{
		_ltputs("Incorrect Number Of Arguments\n");
		return (1);
	}
	if (set_custom_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * unset_env_var - Unsets custom environment variables.
 * @info: Pointer to the structure containing environment variable information.
 *
 * Return: 0 upon successfully unsetting the custom environment variables, and
 * 1 in case of insufficient num of arguments or failure to unset variables.
 */

int unset_env_var(info_t *info)
{
	int i;

	if (info->argc <= 1)
	{
		_ltputs("Insufficient Number Of Arguments.\n");
		return (1);
	}
	for (i = 1; i < info->argc; i++)
		unset_custom_env(info, info->argv[i]);
	return (0);
}
