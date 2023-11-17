#include "shell.h"

/**
 * c_control - Controls the execution flow based on command buffer status.
 * @info: Pointer to information data (info_t structure).
 * @buffer: Pointer to a character buffer.
 * @p: Pointer to a size_t value representing an index or position.
 * @i: Size_t value representing an index or position within buffer.
 * @len: Size_t value representing a length or size condition.
 *
 * Return: void
 */

void c_control(info_t *info, char *buffer, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buffer[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buffer[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * cmd_chain - Identifies and handles command chaining in the command buffer.
 * @info: Pointer to information data (info_t structure).
 * @buffer: Pointer to a character buffer containing commands.
 * @p: Pointer to a size_t value representing an index or position.
 *
 * Return: 1 if a command chaining character is found, 0 otherwise.
 */

int cmd_chain(info_t *info, char *buffer, size_t *p)
{
	size_t j = *p;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buffer[j] == ';')
	{
		buffer[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * replace_string - Replaces a pointer to a string with a new string.
 * @old: Pointer to a pointer holding the old string.
 * @new: Pointer to the new string to replace the old string.
 *
 * Return: 1 on successful replacement, 0 otherwise
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

/**
 * replace_varsa - Replaces variables in the info structure's arguments
 * @info: Pointer to information data (info_t structure).
 *
 * Return: 0 indicating successful replacement of variables in the arg strings.
 */

int replace_varsa(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_str_cmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				_str_dup(converts_num(info->status, 10, 0)));
			continue;
		}
		if (!_str_cmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				_str_dup(converts_num(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_here(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				_str_dup(strchar(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _str_dup(""));

	}
	return (0);
}

/**
 * replace_cmd_alias - Replaces command aliases in the info structure's args.
 * @info: Pointer to information data (info_t structure).
 * Return: 1 if a command alias is successfully replaced, 0 otherwise.
 */

int replace_cmd_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_here(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = strchar(node->str, '=');
		if (!p)
			return (0);
		p = _str_dup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}
