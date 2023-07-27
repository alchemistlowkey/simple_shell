#include "shell.h"

/**
* check_chain - checks if we should continue chaining based on last status
* @info: struct
* @buff: pointer
* @p: pointer
* @i: size_t type
* @l: size_t type
* Return: Void
*/
void check_chain(info_type *info, char *buff, size_t *p, size_t i, size_t l)
{
	size_t j = *p;

	if (info->cmd_buff_type == CMD_AND)
	{
		if (info->status)
		{
			buff[i] = 0;
			j = l;
		}
	}
	if (info->cmd_buff_type == CMD_OR)
	{
		if (!info->status)
		{
			buff[i] = 0;
			j = l;
		}
	}

	*p = j;
}

/**
* is_chain - tests if current character in buffer is a chain delimeter
* @info: struct
* @buff: pointer
* @p: pointer
* Return:integer
*/
int is_chain(info_type *info, char *buff, size_t *p)
{
	size_t j = *p;

	if (buff[j] == '|' && buff[j + 1] == '|')
	{
		buff[j] = 0;
		j++;
		info->cmd_buff_type = CMD_OR;
	}
	else if (buff[j] == '&' && buff[j + 1] == '&')
	{
		buff[j] = 0;
		j++;
		info->cmd_buff_type = CMD_AND;
	}
	else if (buff[j] == ';')
	{
		buff[j] = 0;
		info->cmd_buff_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;

	return (1);
}
