#include "shell.h"

/**
 * execute - A function that executes a cmd.
 * @cmd: The pointer to tokienized cmd
 * @name: The name of the shell.
 * @env: The pointer to the enviromental variables.
 * @circles: Number of executed circles.
 * Return: Nothing.
 */
void execute(char **cmd, char *name, char **env, int circles)
{
	char **pathfinder = NULL, *full_path = NULL;
	struct stat st;
	unsigned int i;

	if (_strcmp(cmd[0], "env") != 0)
		print_environment(env);
	if (stat(cmd[0], &st) == 0)
	{
		if (execve(cmd[0], cmd, env) < 0)
		{
			perror(name);
			free_e(cmd);
		}
	}
	else
	{
		pathfinder = _getPATH(env);
		for (i = 0; pathfinder[i]; i++)
		{
			full_path = _strcat(pathfinder[i], cmd[0]);
			if (stat(full_path, &st) == 0)
			{
				if (execve(full_path, cmd, env) < 0)
				{
					perror(name);
					free_d(pathfinder);
					free_e(cmd);
				}
				return;
			}
		}
		errormsg(name, circles, cmd);
		free_d(pathfinder);
	}
}
