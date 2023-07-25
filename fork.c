#include "shell.h"

/**
 * child - A function that creates a sub process.
 * @cmd: The pointer to tokenized cmd
 * @name: The pointer to the name of shell.
 * @env: The pointer to the enviromental variables.
 * @circles: Number of executed circles.
 * Return: Nothing.
 */
void child(char **cmd, char *name, char **env, int circles)
{
	int pid = 0;
	int status = 0;
	int w_error = 0;

	pid = fork();
	if (pid < 0)
	{
		perror("Error: ");
		free_e(cmd);
	}
	else if (pid == 0)
	{
		execute(cmd, name, env, circles);
		free_d(cmd);
	}
	else
	{
		w_error = waitpid(pid, &status, 0);
		if (w_error < 0)
		{
			free_e(cmd);
		}
		free_d(cmd);
	}
}
