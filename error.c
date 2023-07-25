#include "shell.h"

/**
 * errormsg - A function that prints message not found.
 * @name: The name of the shell.
 * @circles: Integer type.
 * @cmd: The pointer to tokenized cmd.
 * Return: Nothing.
 */
void errormsg(char *name, int circles, char **cmd)
{
	char s;

	s = circles + '0';
	write(STDOUT_FILENO, name, _strlen(name));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, &s, 1);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, cmd[0], _strlen(cmd[0]));
	write(STDOUT_FILENO, ": not found\n", 12);
}
