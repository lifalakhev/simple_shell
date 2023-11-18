#include "shell.h"

/**
 * is_file - a function that Checks if the given path corresponds to a regular file.
 * @info: Unused pointer to information data (info_t structure).
 * @path: Pointer to a string representing the file path to check.
 *
 * Return: 1 if the file at the specified path is a regular file, 0 otherwise.
 */

int is_file(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * find_path - a function that Finds a command within a colon-separated list of paths.
 * @info: Pointer to information data (info_t structure).
 * @str_path: Pointer to a string containing colon-separated paths.
 * @cmd: Pointer to the command to find within the paths.
 *
 * Return: A pointer to the full path of the command if found, otherwise NULL.
 */

char *find_path(info_t *info, char *str_path, char *cmd)
{
	int i = 0, current_position = 0;
	char *path;

	if (!str_path)
		return (NULL);
	if ((_str_len(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_file(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!str_path[i] || str_path[i] == ':')
		{
			path = duplicate_chars(str_path, current_position, i);
			if (!*path)
				_str_cat(path, cmd);
			else
			{
				_str_cat(path, "/");
				_str_cat(path, cmd);
			}
			if (is_file(info, path))
				return (path);
			if (!str_path[i])
				break;
			current_position = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * duplicate_chars - a Function that Copies characters from specified range in string to buffer
 * @str_path: Pointer to the string containing the characters.
 * @start: Starting index in the string to begin copying characters.
 * @stop: Stopping index in the string to stop copying characters (exclusive).
 *
 * Return: A pointer to the static buffer containing the copied characters.
 */

char *duplicate_chars(char *str_path, int start, int stop)
{
	static char buffer[1024];
	int i = 0, b = 0;

	for (b = 0, i = start; i < stop; i++)
		if (str_path[i] != ':')
			buffer[b++] = str_path[i];
	buffer[b] = 0;
	return (buffer);
}
