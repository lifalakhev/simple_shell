#include "shell.h"

/**
 * str_tow - Splits a string into an array of strings based on a delimiter.
 * @str: Pointer to the input string to be split.
 * @d: Pointer to the delimiter string used for splitting (default is " ").
 *
 * Return: A pointer to an array of strings On success, On failure: NULL
 */

char **str_tow(char *str, char *d)
{
	int i, j, k, m, nw = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!_is_delim(str[i], d) && (_is_delim(str[i + 1], d) || !str[i + 1]))
			nw++;

	if (nw == 0)
		return (NULL);
	s = malloc((1 + nw) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < nw; j++)
	{
		while (_is_delim(str[i], d))
			i++;
		k = 0;
		while (!_is_delim(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * str_tow2 - Splits string into an array of strings based on  single delimiter
 * @str: Pointer to the input string to be split.
 * @d: Single character delimiter used for splitting.
 *
 * Return: On success: A dynamically allocated array of str, On failure: NULL.
 */

char **str_tow2(char *str, char d)
{
	int i, j, k, m, nw = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			nw++;
	if (nw == 0)
		return (NULL);
	s = malloc((1 + nw) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < nw; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
