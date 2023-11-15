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
