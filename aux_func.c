#include "shell.h"

/**
 * _strcmp - A funtion that compares two strings
 * @str1: string 1
 * @str2: string 2
 * Return: 1 if strings are the same, 0 if not
 */
int _strcmp(char *str1, char *str2)
{
	int i, j = 0;

	for (i = 0; j == 0; i++)
	{
		if (str1[i] == '\0' && str2[i] == '\0')
		{
			break;
		}
		j = str1[i] - str2[i];
	}
	return (j);
}

/**
 * _strlen - A function that finds the length of the string
 * @str: The input string
 * Return: The length of the string
 */
int _strlen(char *str)
{
	int length = 0;

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
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
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
	int dlen = 0, slen = 0;

	while (dest[dlen] != '\0')
		dlen++;

	while (slen >= 0)
	{
		dest[dlen] = src[slen];
		if (src[slen] == '\0')
			break;
		dlen++;
		slen++;
	}
	return (dest);
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
