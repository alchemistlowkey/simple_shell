#include "shell.h"

/**
 * print_error - prints an error message
 * @info: struct
 * @estr: string containing specified error type
 * Return: 0 or -1 on error
 */
void print_error(info_type *info, char *estr)
{
	err_puts(info->fname);
	err_puts(": ");
	print_d(info->line_count, STDERR_FILENO);
	err_puts(": ");
	err_puts(info->argv[0]);
	err_puts(": ");
	err_puts(estr);
}

/**
 * remove_comments - the function replaces first instance of '#' with '\0'
 * @buff: address of the string to change
 * Return: Always 0;
 */
void remove_comments(char *buff)
{
	int i = 0;

	while (buff[i] != '\0')
	{
		i++;
		if (buff[i] == '#' && (!i || buff[i - 1] == ' '))
		{
			buff[i] = '\0';
			break;
		}
	}
}

/**
 * convert_number - converter function
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 * Return: count.
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = err_putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}
