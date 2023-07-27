#include "shell.h"

/**
* find_path - finds this cmd's PATH
* @info: struct
* @pathstr: PATH string
* @cmd: the command to find
* Return: full path of cmd if found or NULL
*/
char *find_path(info_type *info, char *pathstr, char *cmd)
{
	int i = 0, curr_position = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && bonnie_clyde(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_position, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_position = i;
		}
		i++;
	}
	return (NULL);
}

/**
* is_cmd - suggests if a file is an executable cmd
* @info: struct
* @path: path to the file
*
* Return: 0 or 1.
*/
int is_cmd(info_type *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
* dup_chars - it duplicates characters
* @pathstr: the PATH string
* @go: starting index
* @come: stopping index
* Return: pointer
*/

char *dup_chars(char *pathstr, int go, int come)
{
	static char buff[1024];
	int i = 0, k = 0;

	for (k = 0, i = go; i < come; i++)
		if (pathstr[i] != ':')
			buff[k++] = pathstr[i];
	buff[k] = 0;
	return (buff);
}
