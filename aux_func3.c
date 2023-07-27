#include "shell.h"

/**
 * *_strncat - it concatenates two strings
 * @dest: string where src string is append to
 * @src: string that is append to the dest string
 * @n: an integer
 * Return: dest
 */

char *_strncat(char *dest, char *src, int n)
{
	int dlen = 0, slen = 0;

	while (dest[dlen] != '\0')
		dlen++;
	while (slen < n)
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
 * *_strncpy - It copies n string
 * @dest: string that the src string is appended to
 * @src: string that is appended to the dest string
 * @n: maximum number of byte from src
 *
 * Return: dest
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i = 0;

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

/**
 * _isalpha - checks for alphabet
 * @c: The character input
 * Return: if c is an alphabet
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * _isdelim - checks if the character is a delimeter
 * @c: character to be checked
 * @delim: the delimeter string
 * Return: If true 1 , if false, 0
 */
int _isdelim(char c, char *delim)
{
	while (*delim)
	if (*delim++ == c)
		return (1);
	return (0);
}
