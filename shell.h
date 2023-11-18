#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

/* buffer sizes */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Command Types */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* Conversion Types */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* Feature Flags */
#define USE_GETLINE 0
#define USE_STRTOK 0

/* History Configuration */
#define HIST_FILE ".lv"
#define HIST_MAX 4096

extern char **environ;


/**
 * struct strLister - A structure representing a linked list node.
 * @num: An integer data member.
 * @str: A pointer to a character data member.
 * @next: A pointer to the next node in the linked list.
 *
 */
typedef struct strLister
{
	int num;
	char *str;
	struct strLister *next;
} list_t;

/**
 * struct passInfo - Structure for passing information to functions.
 * @arg: A string generated from getline containing arguments.
 * @argv: An array of strings generated from arg.
 * @path: A string path for the current command.
 * @argc: The argument count.
 * @line_count: The error count.
 * @error_num: The error code for exit() calls.
 * @line_count_flag: If on, count this line of input.
 * @fileName: The program filename.
 * @env: Linked list local copy of environ.
 * @history: The history node.
 * @alias: The alias node.
 * @environ: Custom modified copy of environ from LL env.
 * @new_env: On if environ was changed.
 * @status: The return status of the last exec'd command.
 * @cmd_buffer: Address of pointer to cmd ; chain buffe
 * @cmd_buf_type: CMD_type ||, &&, ;.
 * @read_file_des: The file descriptor from which to read line input.
 * @hist_count: The history line number count.
 *
 */
typedef struct passInfo {
    char *arg;
    char **argv;
    char *path;
    int argc;
    unsigned int line_count;
    int error_num;
    int line_count_flag;
    char *fileName;
    list_t *env;
    list_t *history;
    list_t *alias;
    char **environ;
    int new_env;
    int status;

    char **cmd_buffer;
    int cmd_buf_type;
    int read_file_des;
    int hist_count;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}


/**
 * struct builtin - Structure for representing built-in commands.
 * @type: A string representing the name or identifier.
 * @func: A function pointer
 */

typedef struct builtin {
    char *type;
    int (*func)(info_t *);
} built_in_table;


/**
 * shell loop
 * Shell looping Management
 */
int hsh(info_t *, char **);
int find_built_in(info_t *);
void search_cmd(info_t *);
void fork_exec_cmd(info_t *);

/**
 * getline_ops.c
 * Standard Input Operations
 */
void config_handler(int);
ssize_t _get_input(info_t *);
int _get_line(info_t *, char **, size_t *);
ssize_t input_buffer(info_t *, char **, size_t *);
ssize_t read_buffer(info_t *, char *, size_t *);

/**
 * getenviron_op.c
 * Environment Variables Operations
 */
char *strchar(char *, char);
char **get_environment(info_t *);
int set_custom_env(info_t *, char *, char *);
int unset_custom_env(info_t *, char *);

/**
 * memory_management.c
 * Memory Management Functions
 */
int free_pointer(void **);
void free_array_pointers(char **);
void *realloc_mem(void *, unsigned int, unsigned int);

/* Memory Manipulation Functions */
char *memory_set_block(char *, char, unsigned int);

/**
 * inter_mode.c
 * Interactive Mode
 */
int interactive(info_t *);

/**
 * info_ops.c
 * information Operations
 */
void set_info(info_t *, char **);
void reset_info(info_t *);
void free_info(info_t *, int);

/**
 * string_op.c
 * String Operations
 */
int convert_s_to_int(char *);
int _is_delim(char, char *);
int _is_alpha(int);
char *_strn_cpy(char *, char *, int);

/**
 * command_ops.c
 * Command Operatios
 */
int exec_cd(info_t *);
int exec_exit(info_t *);
int exec_help(info_t *);
int exec_cmd_history(info_t *);

/**
 * output_ehandling.c
 * Output Handling
 */
void _ltputs(char *);
int _ltputchar(char);
int lvput_fd(char c, int file_des);
int lvputs_fd(char *str, int file_des);

/**
 * handler_alias.c
 * Alias Handling
 */
int set_alias(info_t *, char *);
int unset_alias(info_t *, char *);
int print_alias(list_t *);
int handle_alias(info_t *);

/**
 * environment_op.c
 * Environment Operations
 */
char *get_env_var(info_t *, const char *);
int initial_env_list(info_t *);
int print_environ_info(info_t *);
int set_env_var(info_t *);
int unset_env_var(info_t *);

/**
 * list_ut.c
 * List Utilities
 */
size_t print_list(const list_t *);
size_t list_l(const list_t *);
ssize_t get_node_index(list_t *, list_t *);
list_t *node_starts_here(list_t *, char *, char);
char **list_strings(list_t *);

/**
 * list_ut1.c
 * Lists Opeartions
 */
list_t *add_node(list_t **, const char *str, int);
list_t *add_node_end(list_t **, const char *str, int);
size_t print_string_list(const list_t *);
void free_list(list_t **);
int delete_node_index(list_t **, unsigned int);

/**
 * vars_ops.c
 * Variable Operations
 */
void c_control(info_t *, char *, size_t *, size_t, size_t);
int cmd_chain(info_t *, char *, size_t *);
int replace_string(char **, char *);
int replace_varsa(info_t *);
int replace_cmd_alias(info_t *);

/**
 * string_ut.c
 * String Computing
 */
int _str_len(char *);
char *_str_cpy(char *, char *);
void _lvprint(char *);
int _put_char(char);
char *_str_dup(const char *);

/**
 * string_ut1.c
 * More on string Computing
 */
int _str_cmp(char *, char *);
char *_str_cat(char *, char *);
char *starts_with(const char *, const char *);
char *_strn_cat(char *, char *, int );

/**
 * output_ehandling.c
 * Output error Handling
 */
void free_info(info_t *, int );
void set_info(info_t *, char **);
void reset_info(info_t *);

/**
 * file_parser_ops.c
 * Parsing Operations
 */
char *find_path(info_t *, char *, char *);
int is_file(info_t *, char *);
char *find_path(info_t *, char *, char *);
char *duplicate_chars(char *, int, int);

/**
 * token_ops.c
 * Tokenization Operations
 */
char **str_tow(char *, char *);
char **str_tow2(char *, char);

/**
 * erroratoi_ops.c
 * Error atoi handling
 */
int error_atoi(char *);
void print_error(info_t *, char *);
int print_dec(int, int);
void clear_comments(char *);
char *converts_num(long int, int, int);

/**
 * history_ut.c
 * History Utility
 */
char *retrieve_histfile(info_t *);
int write_history(info_t *);
int dev_hist_list(info_t *info, char *buffer, int line_count);
int read_history(info_t *);
int renum_history(info_t *);

#endif /* SHELL_ENDS */
