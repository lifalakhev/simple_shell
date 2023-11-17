#include "shell.h"

/**
 * config_handler - Handles the SIGINT signal, printing a prompt,
 *                  and flushing the output buffer.
 * @sig_num: The signal number (unused).
 */

void config_handler(__attribute__((unused))int sig_num)
{
	_lvprint("\n");
	_lvprint("$ ");
	_put_char(BUF_FLUSH);
}

/**
 * _get_input - Obtains input from the user for processing in the shell.
 * @info: Pointer to the info_t structure.
 *
 * Return: the length of the current command or -1 if EOF is reached.
 */

ssize_t _get_input(info_t *info)
{
	static char *buffer;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buffer_p = &(info->arg), *p;

	_put_char(BUF_FLUSH);
	r = input_buffer(info, &buffer, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)
	{
		j = i;
		p = buffer + i;

		c_control(info, buffer, &j, i, len);
		while (j < len)
		{
			if (cmd_chain(info, buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buffer_p = p;
		return (_str_len(p));
	}

	*buffer_p = buffer;
	return (r);
}

/**
 * _get_line - Reads input from a file descriptor into a string pointer
 * @info: Pointer to the info_t structure
 * @str_ptr: Pointer to the string pointer to store the read content
 * @str_len: Pointer to the length of the string
 *
 * Return: the size of the read content 's', -1 on failure.
 */

int _get_line(info_t *info, char **str_ptr, size_t *str_len)
{
	static char buffer[READ_BUF_SIZE];
	static size_t i, len;
	size_t b;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_ptr = NULL, *newline_ptr;

	p = *str_ptr;
	if (p && str_len)
		s = *str_len;
	if (i == len)
		i = len = 0;

	r = read_buffer(info, buffer, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	newline_ptr = strchar(buffer + i, '\n');
	b = newline_ptr ? 1 + (unsigned int)(newline_ptr - buffer) : len;
	new_ptr = realloc_mem(p, s, s ? s + b : b + 1);
	if (!new_ptr)
		return (p ? free(p), -1 : -1);

	if (s)
		_strn_cat(new_ptr, buffer + i, b - i);
	else
		_strn_cpy(new_ptr, buffer + i, b - i + 1);

	s += b - i;
	i = b;
	p = new_ptr;

	if (str_len)
		*str_len = s;
	*str_ptr = p;
	return (s);
}

/**
 * input_buffer - Reads input from standard input and handles buffer management
 * @info: Pointer to the info_t structure
 * @buffer: Pointer to a pointer representing the buffer
 * @len: Pointer to the size of the buffer
 *
 * Return: Returns the number of characters read on success, or -1 on failure.
 */

ssize_t input_buffer(info_t *info, char **buffer, size_t *len)
{
	ssize_t r = 0;
	size_t len_i = 0;

	if (!*len)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, config_handler);
#if USE_GETLINE
		r = getline(buffer, &len_i, stdin);
#else
		r = _get_line(info, buffer, &len_i);
#endif
		if (r > 0)
		{
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0';
				r--;
			}
			info->line_count_flag = 1;
			clear_comments(*buffer);
			dev_hist_list(info, *buffer, info->hist_count++);
			{
				*len = r;
				info->cmd_buffer = buffer;
			}
		}
	}
	return (r);
}

/**
 * read_buffer - Reads from a file descriptor into a buffer and manages index
 * @info: Pointer to the info_t structure
 * @buffer: Pointer to the buffer for reading
 * @i: Pointer to the current index of the buffer
 *
 * Return: the number of bytes read on success, or 0 if index is nonzero.
 */

ssize_t read_buffer(info_t *info, char *buffer, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->read_file_des, buffer, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}
