#include "shell.h"

/**
* _realloc - reallocates a block of memory
* @ptr: pointer to previous mallocated block
* @old_state: size of previous block
* @new_state: size of new block
* Return: pointer.
*/

void *_realloc(void *ptr, unsigned int old_state, unsigned int new_state)
{
	char *str;

	if (!ptr)
		return (malloc(new_state));
	if (!new_state)
		return (free(ptr), NULL);
	if (new_state == old_state)
		return (ptr);

	str = malloc(new_state);
	if (!str)
		return (NULL);

	old_state = old_state < new_state ? old_state : new_state;
	while (old_state--)
		str[old_state] = ((char *)ptr)[old_state];
	free(ptr);
	return (str);
}

/**
 * free_e - A function that frees all the memory allocated and exit.
 * @cmd: The pointer to allocated cmd memory to free.
 * Return: Nothing.
 */
void free_e(char **cmd)
{
	char **str = cmd;

	if (!cmd)
		return;
	while (*cmd)
		free(*cmd++);
	free(str);
}

/**
* b_free - frees a pointer and NULLs the address
* @pointer: double pointer
* Return: 1 or 0.
*/

int b_free(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}

/**
* _memset - fills the memory
* @str: pointer
* @c: character
* @n: amount of bytes to be filled
* Return: A pointer
*/

char *_memset(char *str, char c, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		str[i] = c;
	return (str);
}
