#include "shell.h"

/**
* prompt - the shell loop
* @info: struct
* @av: argument vector
* Return: 0, 1, or error code, depending on status
*/
int prompt(info_type *info, char **av)
{
	ssize_t i = 0;
	int builtin_ret = 0;

	while (i != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		err_putchar(BUFF_FLUSH);
		i = _input(info);
		if (i != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_command(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
* create_child - create a child process to run cmd
* @info: struct
* Return: void
*/
void create_child(info_type *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

/**
* find_builtin - to find a builtin command.
* @info: struct.
* Return: -1, 0, 1, 2. depending on the status.
*/
int find_builtin(info_type *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintab1[] = {
		{"exit", sh_exit},
		{"env", handle_env},
		{"help", sh_help},
		{"history", sh_history},
		{"setenv", handle_setenv},
		{"unsetenv", handle_unsetenv},
		{"cd", sh_cd},
		{"alias", sh_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintab1[i].type; i++)
		if (_strcmp(info->argv[0], builtintab1[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintab1[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * interactive - A function that prints the prompt
 * @info: struct
 * Return: interactive mode
 */

int interactive(info_type *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
* find_command - it finds a command in PATH
* @info: struct
* Return: void
*/
void find_command(info_type *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
	{
		if (!_isdelim(info->arg[i], " \t\n"))
			k++;
	}
	if (!k)
		return;
	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		create_child(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			create_child(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}
