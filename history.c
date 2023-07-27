#include "shell.h"

/**
* write_history - creates a file, or makes changes to an existing one
* @info: struct
* Return: 1 or -1
*/
int write_history(info_type *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		fd_puts(node->str, fd);
		fd_put('\n', fd);
	}
	fd_put(BUFF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
* read_history - It reads history from file
* @info: struct
* Return: histcount on success, otherwise 0
*/
int read_history(info_type *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			build_history_list(info, buff + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buff + last, linecount++);
	free(buff);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
* build_history_list - It adds entry to a history linked list
* @info: Its sastructure containing potential arguments.
* @buff: bufffer
* @linecount: the history linecount, histcount
* Return: Always 0
*/
int build_history_list(info_type *info, char *buff, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buff, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
* renumber_history - It renumbers the history linked list after changes
* @info: It's the tructure containing potential arguments.
* Return: the new histcount
*/
int renumber_history(info_type *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}

/**
* get_history_file - It gets the history file
* @info: struct
* Return: allocated string containing history file
*/
char *get_history_file(info_type *info)
{
	char *buff, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dir);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}
