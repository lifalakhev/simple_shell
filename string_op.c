#include "shell.h"

/**
 * convert_s_to_int - Converts a string to an integer.
 * @s: Input string to convert.
 *
 * Return: 0 if there no numbers in string, otherwise the converted integer.
 */

int convert_s_to_int(char *s)
{
	int i, sign = 1, parse_status = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && parse_status != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			parse_status = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (parse_status == 1)
			parse_status = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

/**
 * is_delim - Checks if a character is a delim within a string of delimiters.
 * @check_c: The character to be checked for being a delimiter.
 * @delim: Pointer to a string containing a set of delimiter characters.
 *
 * Return: 1 if the character 'check_c' is a delim within 'delims' string;
 * otherwise, returns 0.
 */

int is_delim(char check_c, char *delim)
{
	while (*delim)
		if (*delim++ == check_c)
			return (1);
	return (0);
}

/**
 * _isalpha - Checks if a character is an alphabetic character.
 * @check_c: The character to be checked for alphabetic status.
 *
 * Return: 1 if 'check_c' is an alphabetic character (A-Z or a-z);
 * otherwise, returns 0.
 */

int _isalpha(int check_c)
{
	if ((check_c >= 'a' && check_c <= 'z') || (check_c >= 'A' && check_c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * strcpy - Copies up to 'n' characters from 'src' string to 'target' string.
 * @target: Pointer to target string where contents from 'src' will be copied.
 * @src: Pointer to the source string from which characters will be copied.
 * @n: Maximum number of chars to copy from 'src' (including null-terminator).
 *
 * Return: Pointer to 'target' string where characters were copied from 'src'
 */

char *strcpy(char *target, char *src, int n)
{
	int i, j;
	char *s = target;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		target[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			target[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * strcat - Appends up to 'n' characters from 'src' string to 'target' string.
 * @target: Pointer to target str to which contents from 'src' will be appended
 * @src: Pointer to source string whose characters will be appended to 'target'
 * @n: Maximum number of chars to append from 'src' (including null-terminator)
 *
 * Return: Pointer to the 'target' string with appended characters from 'src'
 */

char *strcat(char *target, char *src, int n)
{
	int i, j;
	char *s = target;

	i = 0;
	j = 0;
	while (target[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		target[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		target[i] = '\0';
	return (s);
}
