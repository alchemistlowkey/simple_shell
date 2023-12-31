#include "shell.h"

/**
 * _getenv - gets the value of an environ variable
 * @info: It's the structure contains potential arguments.
 * @name: env var name
 * Return: NULL
 */
char *_getenv(info_type *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = bonnie_clyde(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * handle_setenv - Start a new environment variable,
 * or change an already existing one
 * @info: It's the structure contains potential arguments.
 * Return: Always 0
 */
int handle_setenv(info_type *info)
{
	if (info->argc != 3)
	{
		err_puts("number of arguements not enough\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * handle_unsetenv - It removes an environment variable
 * @info: Struct
 * Return: Always 0
 */
int handle_unsetenv(info_type *info)
{
	int i;

	if (info->argc == 1)
	{
		err_puts("add more arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}


/**
 * populate_env_list - It populates env linked list
 * @info: struct.
 * Return: Always 0
 */
int populate_env_list(info_type *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

/**
 * handle_env - it prints the current environment.
 * @info: structure contains potential arguments.
 * Return: Always 0
 */
int handle_env(info_type *info)
{
	print_list_str(info->env);
	return (0);
}
