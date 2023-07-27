#include "shell.h"

/**
* sh_help - changes the current directory of the process
* @info: Struct
* constant function prototype.
* Return: Always 0
*/
int sh_help(info_type *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help!!!. Function not yet implemented \n");

	if (0)
		_puts(*arg_array);
	return (0);
}

/**
* sh_exit - exits the shell
* @info: Struct.
* Return: exits
*/
int sh_exit(info_type *info)
{
	if (info->argv[1])
	{
		int exitcheck = err_atoi(info->argv[1]);

		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			err_puts(info->argv[1]);
			err_putchar('\n');
			return (1);
		}
		info->err_num = err_atoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * sh_alias - It mimics the alias builtin (man alias)
 * @info: Structure contains potential arguments. It is used to
 * maintain a constant function prototype.
 * Return: Always 0
 */
int sh_alias(info_type *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}

/**
 * sh_history - It displays the history list, one command by line, starting
 * with line numbers, starting at 0.
 * @info: Structure contains potential arguments. It is used to
 * maintain a constant function prototype.
 * Return: Always 0
 */
int sh_history(info_type *info)
{
	print_list(info->history);
	return (0);
}
