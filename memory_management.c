#include "shell.h"

/**
 * free_pointer - Frees memory allocated to a pointer and sets it to NULL.
 * @pointer: A pointer to a pointer whose memory needs to be freed.
 *
 * Return: 1 if freed,
 * otherwise 0,if the pointer is NULL or points to NULL.
 */

int free_pointer(void **pointer)
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
 * free_array_pointers - Frees memory allocated for an array of ptrs
 * and the ptrs themselves.
 *
 * @parray: Pointer to an array of ptrs.
 *
 * If the input pointer is NULL,
 * Func returns without performing any memory deallocation.
 */

void free_array_pointers(char **parray)
{
	char **tempp = parray;

	if (!parray)
	return;

	while (*parray)
		free(*parray++);

	   free(tempp);
}

/**
 * realloc_mem - Reallocates memory and copies its contents.
 * @pointer: Pointer to the block of memory to be reallocated.
 * @old_size: Size of the old block of memory.
 * @new_size: Size of the new block of memory.
 *
 * Return: pointer to newly allocated memory block.(success)
 * If fails or if 'pointer' is NULL and 'new_size' is not 0, returns NULL.
 */

void *realloc_mem(void *pointer, unsigned int old_size, unsigned int new_size)
{
	char *new_pointer;

	if (!pointer)
		return (malloc(new_size));

	if (!new_size)
		return (free(pointer), NULL);

	if (new_size == old_size)
		return (pointer);

	new_pointer = malloc(new_size);
	if (!new_pointer)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_pointer[old_size] = ((char *)pointer)[old_size];

	free(pointer);
	return (new_pointer);
}

/**
 * memory_set_block - Sets a block of memory with a specific value.
 * @m: Pointer to the block of memory to be set.
 * @b: Value to be set in each byte of the memory block.
 * @n: Number of bytes to set in the memory block.
 *
 * Return: pointer to same memory block 'm'.
 */
char *memory_set_block(char *m, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		m[i] = b;

	return (m);
}
