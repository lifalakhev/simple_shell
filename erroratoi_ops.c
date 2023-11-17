#include "shell.h"

/**
 * error_atoi - converts a string to an integer.
 * @str: the string to be converted.
 * Return: 0 if no nums in string, converted number otherwise
 *       -1 on error.
 */

int error_atoi(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - prints an error message.
 * @info: the parameter & return info struct.
 * @er_str: string containing specified error type
 * Return: 0 if no nums in string, converted num otherwise
 *        -1 on error
 */

void print_error(info_t *info, char *er_str)
{
	_ltputs(info->fileName);
	_ltputs(": ");
	print_dec(info->line_count, STDERR_FILENO);
	_ltputs(": ");
	_ltputs(info->argv[0]);
	_ltputs(": ");
	_ltputs(er_str);
}

/**
 * print_dec - function prints a decimal (integer) number (base 10).
 * @input: the input
 * @file_des: the filedescriptor to write to.
 *
 * Return: number of characters printed.
 */

int print_dec(int input, int file_des)
{
	int (*__put_char)(char) = _put_char;
	int i, count = 0;
	unsigned int _abc_, current;

	if (file_des == STDERR_FILENO)
		__put_char = _ltputchar;
	if (input < 0)
	{
		_abc_ = -input;
		__put_char('-');
		count++;
	}
	else
		_abc_ = input;
	current = _abc_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abc_ / i)
		{
			__put_char('0' + current / i);
			count++;
		}
		current %= i;
	}
	__put_char('0' + current);
	count++;

	return (count);
}

/**
 * clear_comments - function replaces first instance of '#' with '\0'.
 * @buffer: address of string to modify.
 *
 * Return: Always 0.
 */

void clear_comments(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
}

/**
 * converts_num - converter function
 * @num: number.
 * @base: base.
 * @flags: argument flags.
 *
 * Return: string.
 */

char *converts_num(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *pointer;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pointer = &buffer[49];
	*pointer = '\0';

	do	{
		*--pointer = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--pointer = sign;
	return (pointer);
}
