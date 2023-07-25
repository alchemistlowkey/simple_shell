#include "shell.h"

/**
 * print_environment - A function that prints all enviromental variables.
 * @env: The pointer to enviromental variables.
 * Return: Nothing.
 */

void print_environment(char **env)
{
	size_t i, length = 0;

	for (i = 0; env[i]; i++)
	{
		length = _strlen(env[i]);
		write(STDOUT_FILENO, env[i], length);
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * _getPATH - A function to gets the full value from.
 * enviromental variable PATH.
 * @env: The pointer to enviromental variables.
 * Return: All tokenized pathfinder for commands.
 */

char **_getPATH(char **env)
{
	char *pathvalue = NULL, **pathfinder = NULL;
	unsigned int i = 0;

	pathvalue = strtok(env[i], "=");
	for (i = 0; env[i]; i++)
	{
		if (_strcmp(pathvalue, "PATH"))
		{
			pathvalue = strtok(NULL, "\n");
			pathfinder = tokenize(pathvalue, ":");
			return (pathfinder);
		}
		pathvalue = strtok(env[i], "=");
	}
	return (NULL);
}
