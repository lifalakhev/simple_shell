#include "shell.h"

/**
 * interactive - Checks if the program is running in an interactive mode.
 * @info: Pointer to the info_t structure containing program information.
 *
 * Return: 1 if the program is running in interactive mode otherwise, returns 0
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->read_file_des <= 2);
}
