#include "shell.h"

/**
 * _strcmp - A funtion that compares two strings
 * @str1: string 1
 * @str2: string 2
 * Return: 1 if strings are the same, 0 if not
 */
int _strcmp(char *str1, char *str2)
{
	unsigned int i;

	for (i = 0; str1[i]; i++)
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}

	return (1);
}

/**
 * _strlen - A function that finds the length of the string
 * @str: The input string
 * Return: The length of the string
 */
unsigned int _strlen(char *str)
{
	unsigned int length = 0;

	while (str[length])
		length++;

	return (length);
}

/**
 * _strcpy - A function that copies a string to another string
 * @dest: The pointer to the copyed string
 * @src: The pointer to string to copy for
 * Return: A pointer to copied string
 */
char *_strcpy(char *dest, char *src)
{
	char *tmp = dest;

	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (tmp);
}

/**
 * _strcat - a function that concatenates two strings.
 * @dest: an input string
 * @src: an input string
 * Return: A pointer to the resulting string
 */
char *_strcat(char *dest, char *src)
{
	char *tmp = dest;

	while (*dest)
		dest++;

	*dest++ = '/';
	while (*src)
		*dest++ = *src++;
	return (tmp);
}

/**
 * _atoi - a function that converts string to integer.
 * @str: An input string.
 * Return: integer from conversion.
 */
int _atoi(char *str)
{
	int symbol = 1;
	unsigned int count = 0;
	char flag = 0;

	if (str == NULL)
		return (0);
	while (*str)
	{
		if (*str == '-')
			symbol *= -1;
		if (*str >= '0' && *str <= '9')
		{
			flag = 1;
			count = count * 10 + (*str - '0');
		}
		else if (*str < '0' || *str > '9')
		{
			if (flag == 1)
				break;
		}
		str++;
	}
	if (symbol < 0)
		count = (-1 * (count));
	return (count);
}
