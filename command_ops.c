#include "shell.h"

/**
 * exec_cd - Function to change directory.
 * @info: Pointer to the struct containing information.
 *
 * Return: 0 on success, 1 on failure.
 */
int exec_cd(info_t *info)
{
	char *cur_dir, *hd, buffer[1024];
	int chdir_return;

	cur_dir = getcwd(buffer, 1024);
	if (!cur_dir)
		_lvprint("Failed to retrieve current directory\n");
	if (!info->argv[1])
	{
		hd = get_env_var(info, "HOME=");
		if (!hd)
			chdir_return = chdir((hd = get_env_var(info, "PWD=")) ?
					hd : "/");
		else
			chdir_return = chdir(hd);
	}
	else if (_str_cmp(info->argv[1], "-") == 0)
	{
		if (!get_env_var(info, "OLDPWD="))
		{
			_lvprint(cur_dir);
			_put_char('\n');
			return (1);
		}
		_lvprint(get_env_var(info, "OLDPWD=")), _put_char('\n');
		chdir_return = chdir((hd = get_env_var(info, "OLDPWD=")) ? hd : "/");
	}
	else
		chdir_return = chdir(info->argv[1]);
			if (chdir_return == -1)
			{
				print_error(info, "Failed to change directory to ");
				_ltputs(info->argv[1]), _ltputchar('\n');
			}
			else
			{
				set_custom_env(info, "OLDPWD", get_env_var(info, "PWD="));
				set_custom_env(info, "PWD", getcwd(buffer, 1024));
			}
			return (0);
}

/**
 * exec_exit - Handles exit command and parses error number from argument.
 * @info: Pointer to the structure containing command information.
 *
 * Return:
 *     1 if an illegal number is presented, -2 if no argument or valid number
 */

int exec_exit(info_t *info)
{
	int parsed_num;

	if (info->argc > 1)
	{
		parsed_num = error_atoi(info->argv[1]);
		if (parsed_num == -1)
		{
			info->status = 2;
			print_error(info, "Invalid number: ");
			_ltputs(info->argv[1]);
			_ltputchar('\n');
			return (1);
		}

		info->error_num = error_atoi(info->argv[1]);
		return (-2);
	}

	info->error_num = -1;
	return (-2);
}

/**
 * exec_help - Executes the 'help' function.
 * @info: Pointer to the info structure containing command arguments.
 *
 * Return: Always returns 0.
 */

int exec_help(info_t *info)
{
	char **cmd_args;

	cmd_args = info->argv;
	_lvprint("Sorry, 'help' function is currently under development.\n");
	if (0)
		_lvprint(*cmd_args);
	return (0);
}

/**
 * exec_cmd_history - Executes the command history from info structure.
 * @info: Pointer to the info structure containing command history.
 *
 * Return: Always returns 0 after displaying the command history.
 */

int exec_cmd_history(info_t *info)
{
	print_list(info->history);
	return (0);
}
