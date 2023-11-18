#include "shell.h"

/**
 * _put_char - Writes a character to standard output (stdout) with buffering
 * @c: The character to be written.
 *
 * Return: 1 on successful character write, or when the buffer is flushed.
 */

int _put_char(char c)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buffer[i++] = c;
	return (1);
}

/**
 * _lvprint - Prints a string character by character.
 * @str: Pointer to the input string to be printed.
 *
 * Return: Nothing.
 */

void _lvprint(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_put_char(str[i]);
		i++;
	}
}

/**
 * _str_dup - Duplicates a string.
 * @str: Pointer to the input string to be duplicated.
 *
 * Return: On success pointer to the duplicated str,
 * On failure or if 'str' is NULL: NULL.
 */

char *_str_dup(const char *str)
{
	int len = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--str;
	return (ret);
}

/**
 * _str_len - Computes the length of a string.
 * @s: Pointer to the input string whose length is to be determined.
 *
 * Return: The length of the string 's', If 's' is NULL, returns 0.
 */

int _str_len(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _str_cpy - Copies a string from source to target.
 * @target: Pointer to the target string where the contents will be copied.
 * @src: Pointer to the source string to be copied.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set.
 */

char *_str_cpy(char *target, char *src)
{
	int i = 0;

	if (target == src || src == 0)
		return (target);
	while (src[i])
	{
		target[i] = src[i];
		i++;
	}
	target[i] = 0;
	return (target);
}
