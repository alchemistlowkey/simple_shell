#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>

#define READ_BUFF_SIZE 1024
#define WRITE_BUFF_SIZE 1024
#define BUFF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct info_select - this contains pseudo-arguments to pass into a function,
 * allowing a uniform prototype for function pointer struct
 * @arg: It's a string generated from getline containing arguments
 * @argv: It's an array of strings generated from arg
 * @path: It's a string path for the current command
 * @argc: It's the argument count
 * @line_count: It's the error count
 * @err_num: It's the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: It's the history node
 * @alias: It's the alias node
 * @env_changed: on if environ was changed
 * @status: It's the return status of the last executed command
 * @cmd_buff: The address of pointer to cmd_buf, on if chaining
 * @cmd_buff_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: It's the history line number count
 */
typedef struct info_select
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buff;
	int cmd_buff_type;
	int readfd;
	int histcount;
} info_type;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin_s - contains a builtin string and related function
 * @type: builtin command flag
 * @func: the function
 */
typedef struct builtin_s
{
	char *type;
	int (*func)(info_type *);
} builtin_table;

int main(int ac, char **av);
void find_command(info_type *info);
int interactive(info_type *info);
int find_builtin(info_type *info);
void create_child(info_type *info);
int prompt(info_type *info, char **av);

int is_cmd(info_type *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_type *, char *, char *);

void err_puts(char *);
int err_putchar(char);
int fd_put(char c, int fd);
int fd_puts(char *str, int fd);

int _strlen(char *);
int _strcmp(char *, char *);
char *bonnie_clyde(const char *, const char *);
char *_strcat(char *, char *);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

char **tokenize(char *, char *);
char **tokenize2(char *, char);

char *_memset(char *, char, unsigned int);
void free_e(char **);
void *_realloc(void *, unsigned int, unsigned int);

int b_free(void **);

int _isdelim(char, char *);
int _isalpha(int);
int _atoi(char *);

int err_atoi(char *);
void print_error(info_type *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);

size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

int write_history(info_type*info);
int read_history(info_type*info);
int build_history_list(info_type*info, char *buf, int linecount);
int renumber_history(info_type *info);
char *get_history_file(info_type *info);

char *_getenv(info_type*, const char *);
int handle_env(info_type*);
int handle_setenv(info_type*);
int handle_unsetenv(info_type*);
int populate_env_list(info_type*);

char **get_environ(info_type*);
int _unsetenv(info_type*, char *);
int _setenv(info_type*, char *, char *);

ssize_t input_buff(info_type *, char **, size_t *);
ssize_t read_buff(info_type *info, char *buff, size_t *i);
ssize_t _input(info_type *);
int _getline(info_type *, char **, size_t *);
void sigintHandler(int);

void clear_info(info_type *);
void set_info(info_type *, char **);
void free_info(info_type *, int);
void free_list(list_t **);

int is_chain(info_type *, char *, size_t *);
void check_chain(info_type *, char *, size_t *, size_t, size_t);

int sh_exit(info_type*);
int sh_cd(info_type*);
int sh_help(info_type*);

int sh_history(info_type*);
int sh_alias(info_type*);

int unset_alias(info_type *info, char *str);
int set_alias(info_type *info, char *str);
int print_alias(list_t *node);

#endif
