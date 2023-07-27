#include "shell.h"

/**
 * _input - gets a line minus the newline
 * @info: struct
 * Return: r
 */
ssize_t _input(info_type *info)
{
	static char *buff;
	static size_t i, j, length;
	ssize_t r = 0;
	char **buff_p = &(info->arg), *p;

	_putchar(BUFF_FLUSH);
	r = input_buff(info, &buff, &length);
	if (r == -1)
		return (-1);
	if (length)
	{
		j = i;
		p = buff + i;
		check_chain(info, buff, &j, i, length);
		for (; j < length; j++)
		{
			if (is_chain(info, buff, &j))
				break;
		}

		i = j + 1;
		if (i >= length)
		{
			length = 0;
			i = length;
			info->cmd_buff_type = CMD_NORM;
		}
		*buff_p = p;
		return (_strlen(p));
	}
	*buff_p = buff;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: struct
 * @ptr: double pointer
 * @length: size of preallocated ptr buffer if not NULL
 * Return: s
 */
int _getline(info_type *info, char **ptr, size_t *length)
{
	static char buff[READ_BUFF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;
	r = read_buff(info, buff, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = _strchr(buff + i, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);
	if (s)
		_strncat(new_p, buff + i, k - i);
	else
		_strncpy(new_p, buff + i, k - i + 1);
	s += k - i;
	i = k;
	p = new_p;
	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * input_buff - buffers that are chained commands
 * @info: struct
 * @buff: double pointer
 * @length: pointer
 * Return: r.
 */
ssize_t input_buff(info_type *info, char **buff, size_t *length)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*length)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buff, &len_p, stdin);
#else
		r = _getline(info, buff, &len_p);
#endif
		if (r > 0)
		{
			if ((*buff)[r - 1] == '\n')
			{
				(*buff)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buff);
			build_history_list(info, *buff, info->histcount++);
			{
				*length = r;
				info->cmd_buff = buff;
			}
		}
	}
	return (r);
}

/**
 * sigintHandler - handles CTRL C.
 * @signal_num: signal number
 * Return: void
 */
void sigintHandler(__attribute__((unused))int signal_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFF_FLUSH);
}

/**
 * read_buff - reads a buffer
 * @info: struct
 * @buff: buffer
 * @i: size
 * Return: r
 */
ssize_t read_buff(info_type *info, char *buff, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buff, READ_BUFF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}
