#include "shell.h"

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on error.
 */

int main(int argc, char **argv)
{
	info_t info[] = { INFO_INIT };
	int file_des = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (file_des)
			: "r" (file_des));

	if (argc == 2)
	{
		file_des = open(argv[1], O_RDONLY);
		if (file_des == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_ltputs(argv[0]);
				_ltputs(": 0: Cannot open ");
				_ltputs(argv[1]);
				_ltputchar('\n');
				_ltputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->read_file_des = file_des;
	}
	initial_env_list(info);
	read_history(info);
	hsh(info, argv);
	return (EXIT_SUCCESS);
}
