#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc __attribute__((unused)), char **argv)
{
	char *cmd = NULL, *cmd_cpy = NULL, *token = NULL, *delim = " \n";
	size_t n = 0;
	int val, i = 0, j = 0;
	char *buffer = NULL;
	int status;
	pid_t pid;

	while(1)
	{
		if (isatty(STDIN_FILENO) == 1)
			write(STDOUT_FILENO, "#cisfun$ ", 10);

		getline(&buffer, &n, stdin);

		argv = malloc(sizeof(char *) * argc);
		token = strtok(buffer, delim);
		while(token != NULL)
		{
			argv[i] = token;
			token = strtok(NULL, delim);
			i++;
		}
		argv[i] = token;

		pid = fork();
		if(pid == -1)
			return -1;

		if(pid == 0)
			execve(argv[0], argv, NULL);
		else
			wait(&status);
		j++;
			
	}
	free(buffer), free(argv);

	return(0);
}
