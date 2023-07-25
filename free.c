#include "shell.h"

/**
 * free_e - A function that frees all the memory allocated and exit.
 * @cmd: The pointer to allocated cmd memory to free.
 * Return: Nothing.
 */
void free_e(char **cmd)
{
	size_t i;

	if (cmd == NULL)
		return;

	for (i = 0; cmd[i]; i++)
	{
		free(cmd[i]);
	}

	if (cmd[i] == NULL)
		free(cmd[i]);
	free(cmd);
	exit(EXIT_FAILURE);
}

/**
 * free_d - A function that frees all the memory allocated for cmd.
 * @cmd: The pointer to allocated memory to free.
 * Return: Nothing.
 */
void free_d(char **cmd)
{
	size_t i;

	if (cmd == NULL)
		return;

	for (i = 0; cmd[i]; i++)
	{
		free(cmd[i]);
	}

	if (cmd[i] == NULL)
		free(cmd[i]);
	free(cmd);
}
