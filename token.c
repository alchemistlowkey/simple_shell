#include "shell.h"

/**
 * tokenize - A function that split and create a full buffering cmd.
 * @delim: The delimiter for strtok.
 * @buf: The pointer to the input string.
 * Return: A string with full cmd.
 */
char **tokenize(char *buf, char *delim)
{
	int i, j, m, count = 0;
	char **s;

	if (buf == NULL || buf[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; buf[i] != '\0'; i++)
		if (!_isdelim(buf[i], delim) && (_isdelim(buf[i + 1], delim) || !buf[i + 1]))
			count++;
	if (count == 0)
		return (NULL);
	s = malloc((1 + count) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < count; j++)
	{
		int k = 0;

		while (_isdelim(buf[i], delim))
			i++;
		while (!_isdelim(buf[i + k], delim) && buf[i + k])
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
			s[j][m] = buf[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * tokenize2 - A function that split and create a full buffering cmd.
 * @delim: The delimiter for strtok.
 * @buffer: The pointer to the input string.
 * Return: A string with full cmd.
 */
char **tokenize2(char *buffer, char delim)
{
	int i, j, m, count = 0;
	char **s;

	if (buffer == NULL || buffer[0] == 0)
		return (NULL);
	for (i = 0; buffer[i] != '\0'; i++)
		if ((buffer[i] != delim && buffer[i + 1] == delim) ||
			(buffer[i] != delim && !buffer[i + 1]) || buffer[i + 1] == delim)
			count++;
	if (count == 0)
		return (NULL);
	s = malloc((1 + count) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < count; j++)
	{
		int k = 0;

		while (buffer[i + k] && buffer[i + k] != delim)
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
			s[j][m] = buffer[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
