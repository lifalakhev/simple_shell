#include "shell.h"

/**
 * hsh - Main function for the custom shell.
 * @info: Pointer to the shell information structure.
 * @argv: Array of strings representing command-line arguments.
 *
 * Return: 0 on success, Otherwise 1 on error, or error of code.
 */

int hsh(info_t *info, char **argv)
{
	ssize_t input_result = 0;
	int builtin_cmd_result = 1;

	while (input_result != -1 && builtin_cmd_result != -2)
	{
		reset_info(info);

		if (interactive(info))
			_lvprint("$ ");

		_ltputchar(BUF_FLUSH);
		input_result = _get_input(info);

		if (input_result != -1)
		{
			set_info(info, argv);
			builtin_cmd_result = find_built_in(info);

			if (builtin_cmd_result == -1)
				search_cmd(info);
		}
		else if (interactive(info))
			_put_char('\n');
		free_info(info, 0);
	}

	write_history(info);
	free_info(info, 1);

	if (!interactive(info) && info->status)
		exit(info->status);

	if (builtin_cmd_result == -2)
	{
		if (info->error_num == -1)
			exit(info->status);
		exit(info->error_num);
	}

	return (builtin_cmd_result);
}

/**
 * find_built_in - Find and execute a built-in command.
 * @info: Pointer to the shell information structure.
 *
 * Return: the result of the built-in command execution.
 * -1 if the command is not a built-in.
 */
int find_built_in(info_t *info)
{
	int i, btl_ret = -1;
	built_in_table builtintable[] = {
		{"exit", exec_exit},
		{"env", print_environ_info},
		{"help", exec_help},
		{"history", exec_cmd_history},
		{"setenv", set_env_var},
		{"unsetenv", unset_env_var},
		{"cd", exec_cd},
		{"alias", handle_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintable[i].type; i++)
		if (_str_cmp(info->argv[0], builtintable[i].type) == 0)
		{
			info->line_count++;
			btl_ret = builtintable[i].func(info);
			break;
		}
	return (btl_ret);
}

/**
 * search_cmd - Find and execute an external command.
 * @info: Pointer to the shell information structure.
 *
 */

void search_cmd(info_t *info)
{
	char *path = NULL;
	int i, non_delimcount;

	info->path = info->argv[0];
	if (info->line_count_flag == 1)
	{
		info->line_count++;
		info->line_count_flag = 0;
	}
	for (i = 0, non_delimcount = 0; info->arg[i]; i++)
		if (!_is_delim(info->arg[i], " \t\n"))
			non_delimcount++;

	if (!non_delimcount)
		return;

	path = find_path(info, get_env_var(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_exec_cmd(info);
	}
	else
	{
		if ((interactive(info) || get_env_var(info, "PATH=")
					|| info->argv[0][0] == '/') && is_file(info, info->argv[0]))
		{
			fork_exec_cmd(info);
		}
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "Not Found\n");
		}
	}
}

/**
 * fork_exec_cmd - Fork a new process and execute a command.
 * @info: Pointer to the shell information structure.
 *
 */
void fork_exec_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environment(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied!\n");
		}
	}
}
