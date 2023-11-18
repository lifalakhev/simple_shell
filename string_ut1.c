#include "shell.h"

/**
 * _str_cmp - Compares two strings lexicographically.
 * @str1: Pointer to the first string.
 * @str2: Pointer to the second string.
 *
 * Return: Negative value (< 0) if 'str1' is lexicographically < 'str2'.
 * 0 if 'str1' is equal to 'str2'.
 * Positive value (> 0) if 'str1' is lexicographically greater than 'str2'.
 */

int _str_cmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * _str_cat - Concatenates two strings.
 * @target: Pointer to the target string where the contents will be appended.
 * @src: Pointer to the source string to be appended to the target.
 *
 * Return: Pointer to the beginning of the target string after concatenation.
 */

char *_str_cat(char *target, char *src)
{
	char *ret = target;

	while (*target)
		target++;
	while (*src)
		*target++ = *src++;
	*target = *src;
	return (ret);
}

/**
 * _strn_cat - Concatenates two strings.
 * @target: Pointer to the first string
 * @src: Pointer to the source string to be appended
 * @n: Amount of bytes available to be usd.e
 *
 * Return: Pointer to the beginning of the target string after concatenation.
 */
char *_strn_cat(char *target, char *src, int n)
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

/**
 * starts_with - Checks if a string starts with another string.
 * @p_str: Pointer to the string to be checked.
 * @needle: Pointer to the substring being searched for.
 *
 * Return: Pointer to the location in 'p_str' where 'needle' begins.
 * - If 'needle' is an empty string, returns 'p_str'.
 * - If 'needle' is not found at the beginning of 'p_str', returns NULL.
 */

char *starts_with(const char *p_str, const char *needle)
{
	while (*needle)
		if (*needle++ != *p_str++)
			return (NULL);
	return ((char *)p_str);
}
