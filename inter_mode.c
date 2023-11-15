#include "shell.h"

/**
 * is_interactive - Checks if the program is running in an interactive mode.
 * @info: Pointer to the info_t structure containing program information.
 *
 * Return: 1 if the program is running in interactive mode otherwise, returns 0
 */

int is_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->read_file_descriptor <= 2);
}
