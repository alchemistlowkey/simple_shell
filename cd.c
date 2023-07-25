#include "shell.h"

/**
  * cd - Afunction that changes working directory.
  * @finder: The new current working directory.
  * Return: 0 on success, -1 on failure.
  */

int cd(const char *finder)
{
	char *buff = NULL;
	size_t buff_size = 1024;

	if (finder == NULL)
		finder = getcwd(buff, buff_size);
	if (chdir(finder) == -1)
	{
		perror(finder);
		return (98);
	}
	return (1);
}
