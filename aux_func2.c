#include "shell.h"

/**
 *_strdup - It returns a pointer to newly allocated space in memory
 * @str: string parameter
 * Return: a pointer or NULL
 */
char *_strdup(const char *str)
{
	unsigned int len;
	char *newstr;

	if (str == NULL)
	{
		return (NULL);
	}
	len = strlen(str) + 1;
	newstr = malloc(sizeof(char) * len);
	if (newstr == NULL)
	{
		return (NULL);
	}
	strcpy(newstr, str);
	return (newstr);
}

/**
* _puts - It prints an input string
* @str: the string to be printed
* Return: Nothing
*/
void _puts(char *str)
{
	int i;

	if (!str)
		return;
	for (i = 0; str[i] != '\0'; i++)
	{
		_putchar(str[i]);
	}
}

/**
* _putchar - it writes the character to standard output
* @c: The character to be printed
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int _putchar(char c)
{
	static int i;
	static char buff[WRITE_BUFF_SIZE];

	if (c == BUFF_FLUSH || i >= WRITE_BUFF_SIZE)
	{
		write(1, buff, i);
		i = 0;
	}
	if (c != BUFF_FLUSH)
		buff[i++] = c;
	return (1);
}

/**
 * *_strchr - it locates a character in a string
 * @str: the string character
 * @chr: the character to locate
 * Return: a pointer or null
 */
char *_strchr(char *str, char chr)
{
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == chr)
		{
			return (str + i);
		}
	}
	if (str[i] == chr)
	{
		return (str + i);
	}
	return ('\0');
}

/**
* bonnie_clyde - checks if clyde starts with bonnie
* @bonnie: the string to search
* @clyde: the substring to find
* Return: address of next char of bonnie or NULL
*/
char *bonnie_clyde(const char *bonnie, const char *clyde)
{
	while (*clyde)
		if (*clyde++ != *bonnie++)
			return (NULL);
	return ((char *)bonnie);
}
