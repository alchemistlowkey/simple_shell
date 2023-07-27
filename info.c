#include "shell.h"

/**
* set_info - It initializes info_type struct
* @info: struct
* @av: argument vector
*/
void set_info(info_type *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = tokenize(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		while (info->argv && info->argv[i])
			i++;
		info->argc = i;
	}
}

/**
* clear_info - It initializes info_type struct to NULL.
* @info: struct.
*/
void clear_info(info_type *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
* free_info - frees info_type struct
* @info: struct
* @i: integer type
*/
void free_info(info_type *info, int i)
{
	free_e(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (i)
	{
		if (!info->cmd_buff)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		free_e(info->environ);
			info->environ = NULL;
		b_free((void **)info->cmd_buff);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUFF_FLUSH);
	}
}

/**
 * free_list - frees all nodes
 * @head_point: double pointer
 * Return: void
 */
void free_list(list_t **head_point)
{
	list_t *node, *next_node, *head;

	if (!head_point || !*head_point)
		return;
	head = *head_point;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_point = NULL;
}
