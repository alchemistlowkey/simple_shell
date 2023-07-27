#include "shell.h"

/**
 * err_putchar - writes the char c to stderr
 * @c: character
 * Return: 1.
 */
int err_putchar(char c)
{
	static int i;
	static char buff[WRITE_BUFF_SIZE];

	if (c == BUFF_FLUSH || i >= WRITE_BUFF_SIZE)
	{
		write(2, buff, i);
		i = 0;
	}
	if (c != BUFF_FLUSH)
		buff[i++] = c;
	return (1);
}

/**
 * err_puts - prints an input string
 * @str: string
 * Return: Nothing
 */
void err_puts(char *str)
{
	int i;

	if (!str)
		return;
	for (i = 0; str[i] != '\0'; i++)
	{
		err_putchar(str[i]);
	}
}

/**
 * fd_puts - prints an input str
 * @str: the string
 * @fd: the filedescriptor
 * Return: the number of chars put
 */
int fd_puts(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += fd_put(*str++, fd);
	}
	return (i);
}

/**
 * fd_put - writes the char c to given fd
 * @c: character
 * @fd: filedescriptor
 * Return: On success 1.
 */
int fd_put(char c, int fd)
{
	static int i;
	static char buff[WRITE_BUFF_SIZE];

	if (c == BUFF_FLUSH || i >= WRITE_BUFF_SIZE)
	{
		write(fd, buff, i);
		i = 0;
	}
	if (c != BUFF_FLUSH)
		buff[i++] = c;
	return (1);
}

/**
 * err_atoi - it converts a string to an integer
 * @str: string to be converted
 * Return: 0 or -1.
 */
int err_atoi(char *str)
{
	int i = 0;
	unsigned long int res = 0;

	if (*str == '+')
		str++;
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			res *= 10;
			res += (str[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}
