#include "shell.h"

/**
 * retrieve_histfile - gets the history file.
 * @info: parameter struct.
 *
 * Return: allocated string containg history file.
 */

char *retrieve_histfile(info_t *info)
{
	char *buffer, *dir;

	dir = get_env_var(info, "HOME=");
	if (!dir)
		return (NULL);
	buffer = malloc(sizeof(char) * (_str_len(dir) +
				_str_len(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_str_cpy(buffer, dir);
	_str_cat(buffer, "/");
	_str_cat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_history - creates a file, or appends to an existing file.
 * @info: the parameter struct.
 *
 * Return: 1 on success, else -1.
 */

int write_history(info_t *info)
{
	ssize_t file_des;
	char *filename = retrieve_histfile(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	file_des = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (file_des == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		lvputs_fd(node->str, file_des);
		lvput_fd('\n', file_des);
	}
	lvput_fd(BUF_FLUSH, file_des);
	close(file_des);
	return (1);
}

/**
 * dev_hist_list - adds entry to a history linked list.
 * @info: Structure containing potential arguments.
 * @buffer: buffer
 * @line_count: the history line_count.
 *
 * Return: Always 0 success.
 */

int dev_hist_list(info_t *info, char *buffer, int line_count)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buffer, line_count);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * read_history - reads history from file.
 * @info: the parameter struct.
 *
 * Return: hist_count on success, 0 otherwise.
 */

int read_history(info_t *info)
{
	int i, last = 0, line_count = 0;
	ssize_t file_des, rlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *filename = retrieve_histfile(info);

	if (!filename)
		return (0);

	file_des = open(filename, O_RDONLY);
	free(filename);
	if (file_des == -1)
		return (0);
	if (!fstat(file_des, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rlen = read(file_des, buffer, fsize);
	buffer[fsize] = 0;
	if (rlen <= 0)
		return (free(buffer), 0);
	close(file_des);
	for (i = 0; i < fsize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			dev_hist_list(info, buffer + last, line_count++);
			last = i + 1;
		}
	if (last != i)
		dev_hist_list(info, buffer + last, line_count++);
	free(buffer);
	info->hist_count = line_count;
	while (info->hist_count-- >= HIST_MAX)
		delete_node_index(&(info->history), 0);
	renum_history(info);
	return (info->hist_count);
}

/**
 * renum_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */

int renum_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->hist_count = i);
}
