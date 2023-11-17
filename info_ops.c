#include "shell.h"

/**
 * set_info - Sets information in the info_t structure based on arguments
 * @info: Pointer to the info_t structure
 * @argv: Argument vector containing command and arguments
 */

void set_info(info_t *info, char **argv)
{
	int i = 0;

	info->fileName = argv[0];
	if (info->arg)
	{
		info->argv = str_tow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _str_dup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_cmd_alias(info);
		replace_varsa(info);
	}
}

/**
 * reset_info - Resets values in the info structure to default.
 * @info: Pointer to the info structure to be cleared.
 */

void reset_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * free_info - Frees memory allocated in the info_t structure.
 * @info: Pointer to the info_t structure
 * @all: Integer flag indicating whether to free all memory.
 */

void free_info(info_t *info, int all)
{
	free_array_pointers(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buffer)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		free_array_pointers(info->environ);
		info->environ = NULL;
		free_pointer((void **)info->cmd_buffer);
		if (info->read_file_des > 2)
			close(info->read_file_des);
		_put_char(BUF_FLUSH);
	}
}
