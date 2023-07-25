#include "shell.h"

/**
 * main - A function that runs our shell.
 * @ac: The number of inputed arguments.
 * @av: The pointer to array of inputed arguments.
 * @env: The pointer to array of enviromental variables.
 * Return: Always 0.
 */
int main(int ac __attribute__((unused)), char **av, char **env)
{
	char *buffer = NULL, **cmd = NULL;
	size_t buff_size = 0;
	ssize_t keyin = 0;
	int circles = 0;

	while (1)
	{
		circles++;
		prompt();
		signal(SIGINT, handle);
		keyin = getline(&buffer, &buff_size, stdin);
		if (keyin == EOF)
			_end(buffer);
		else if (*buffer == '\n')
			free(buffer);
		else
		{
			buffer[_strlen(buffer) - 1] = '\0';
			cmd = tokenize(buffer, " \0");
			free(buffer);
			if (_strcmp(cmd[0], "exit") != 0)
				s_exit(cmd);
			else if (_strcmp(cmd[0], "cd") != 0)
				cd(cmd[1]);
			else
				child(cmd, av[0], env, circles);
		}
		fflush(stdin);
		buffer = NULL, buff_size = 0;
	}
	if (keyin == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}


/**
 * prompt - A function that prints the prompt
 * Return: Nothing.
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "#cisfun$ ", 9);
}


/**
 * handle - A function to handle Ctr + C signal.
 * @signals: The signal to handle.
 * Return: Nothing.
 */
void handle(int signals)
{
	(void)signals;
	write(STDOUT_FILENO, "\n#cisfun$ ", 10);
}


/**
 * _end - A function that chaecks if buffer is EOF
 * @buffer: The pointer to the input string.
 * Return: Nothing
 */
void _end(char *buffer)
{
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n", 1);
	free(buffer);
	exit(EXIT_SUCCESS);
}


/**
 * _exit - A function that exits the shell.
 * @cmd: The pointer to tokenized cmd.
 * Return: Nothing.
 */
void s_exit(char **cmd)
{
	int ex = 0;

	if (cmd[1] == NULL)
	{
		free_d(cmd);
		exit(EXIT_SUCCESS);
	}

	ex = _atoi(cmd[1]);
	free_d(cmd);
	exit(ex);
}
