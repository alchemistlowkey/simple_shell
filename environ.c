#include "shell.h"

/**
 * get_environ - It returns the string array copy of our environ
 * @info: It's the structure containing potential arguments.
 * Return: Always 0
 */
char **get_environ(info_type *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * _setenv - Starts a new environment variable,
 * or change an existing one
 * @info: It's the structure containing potential arguments.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_type *info, char *var, char *value)
{
	char *buff = NULL;
	list_t *node;

	if (!var || !value)
		return (0);
	buff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);
	node = info->env;
	while (node)
	{
		char *p = bonnie_clyde(node->str, var);

		if (p && *p == '=')
		{
			free(node->str);
			node->str = buff;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}

/**
 * _unsetenv - It removes an environment variable
 * @info: It's the structure containing potential arguments.
 * Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_type *info, char *var)
{
	list_t *node = info->env;
	size_t i;

	if (!node || !var)
		return (0);
	for (i = 0; node; i++)
	{
		char *p = bonnie_clyde(node->str, var);

		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
	}
	return (info->env_changed);
}
