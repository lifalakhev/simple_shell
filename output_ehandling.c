#include "shell.h"

/**
 * lvput_fd - Program that Writes a character to a file descriptor with line buffering.
 * @c: The character to be written
 * @file_des: The file descriptor to write to.
 *
 * Return: On success, returns 1; On failure, returns EOF.
 */

int lvput_fd(char c, int file_des)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(file_des, buffer, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buffer[i++] = c;
	return (1);
}

/**
 * lvputs_fd - Program that Writes a string to a file descriptor with line buffering.
 * @str: The string to be written.
 * @file_des: The file descriptor to write to.
 *
 * Return: The number of characters written on success, otherwise 0.
 */
int lvputs_fd(char *str, int file_des)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += lvput_fd(*str++, file_des);
	}
	return (i);
}

/**
 * _ltputchar - Programm that Writes a character to the standard error with line buffering.
 * @c: The character to be written.
 *
 * Return: On success, returns 1; On failure, returns EOF.
 */

int _ltputchar(char c)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buffer[i++] = c;
	return (1);
}

/**
 * _ltputs - Program that Prints a string followed by a newline to the standard output0
 * @str: The string to be printed.
 *
 * Return: Nothing
 */
void _ltputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_ltputchar(str[i]);
		i++;
	}
}
