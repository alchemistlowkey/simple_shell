#include "shell.h"

/**
 * tokenize - A function that split and create a full string cmd.
 * @delim: The delimiter for strtok.
 * @buffer: The pointer to the input string.
 * Return: A string with full cmd.
 */
char **tokenize(char *buffer, const char *delim)
{
	char *token = NULL, **cmds = NULL;
	size_t buffsize = 0;
	int i;

	if (buffer == NULL)
		return (NULL);

	buffsize = _strlen(buffer);
	cmds = malloc((buffsize + 1) * sizeof(char *));
	if (cmds == NULL)
	{
		perror("Unable to allocate buffer");
		free(buffer);
		free_d(cmds);
		exit(EXIT_FAILURE);
	}

	token = strtok(buffer, delim);
	for (i = 0; token != NULL; i++)
	{
		cmds[i] = malloc(_strlen(token) + 1);
		if (cmds[i] == NULL)
		{
			perror("Unable to allocate buffer");
			free_d(cmds);
			return (NULL);
		}
		_strcpy(cmds[i], token);
		token = strtok(NULL, delim);
	}
	cmds[i] = NULL;
	return (cmds);
}
