/*
** EPITECH PROJECT, 2017
** minishell1_2017
** File description:
** Minishell 1 header
*/

#ifndef __MY_SH_H_
#define __MY_SH_H_

#include <stdbool.h>
#include "linked_list.h"

#define IS_ALPHA(value) (((value <= 'z' && value >= 'a') || \
(value <= 'Z' && value >= 'A') || (value == '_')) ? 1 : 0)

/* SETENV ERRORS */
#define SETENV_TOO_MUCH_ARGS "setenv: Too many arguments.\n"
#define SETENV_FIRST_ALPHA "setenv: Variable name must begin with a letter.\n"
#define SETENV_ONLY_ALPHA_NUM "setenv: Variable name must \
contain alphanumeric characters.\n"

/* UNSETENV ERRORS */
#define UNSETENV_NEA "unsetenv: Too few arguments.\n"

/* SET ERRORS */
#define SET_FIRST_ALPHA "set: Variable name must begin with a letter.\n"
#define SET_ONLY_ALPHA_NUM "set: Variable name must \
contain alphanumeric characters.\n"

/* UNSET ERRORS */
#define UNSET_NEA "unset: Too few arguments.\n"

/* ENV ERRORS */
#define ENV_TOO_MUCH_ARGS "env: Too many arguments.\n"

/* EXIT ERRORS */
#define EXIT_EXPRESSION_SYNTAX "exit: Expression Syntax.\n"
#define EXIT_BAD_NB "exit: Badly formed number.\n"

/* CD ERRORS */
#define CD_TOO_MUCH_ARGS "cd: Too many arguments.\n"
#define CD_DIR_NOT_FOUNT ": No such file or directory.\n"
#define CD_HOME_NOT_FOUNT "cd: No home directory.\n"

/* PARSINGS INFOS */

#define PARSER_TOKEN "[;],[&&],[||],[|]"
#define PARSER_BUILTIN "[exit],[cd],[env],[setenv],[unsetenv],[echo],[alias]\
,[history],[builtins],[set],[unset],[chdir]"

#define PARSER_REDIRECT "[>],[<],[<<],[>>]"

#define PARSER_ISOLATE "[<<],[>>],[<],[>],[;],[&&],[||],[|]"

#define REDIRECT_AMBIGOUS_OUTPUT "Ambiguous output redirect\n"
#define REDIRECT_MISSING_NAME "Missing name for redirect\n"

#define PIPE_NULL_COMMAND "Invalid null command.\n"

#define EXEC_FORMAT_ERROR "Exec format error. Wrong Architecture"

#define EMPTY_CMD (command_t){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

typedef struct history_elem {
	int id;
	char *time;
	char *cmd;
} history_elem_t;

typedef struct shell_var {
	char *var;
	char *value;
} shell_var_t;

typedef struct term {
	linked_list_t *alias;
	linked_list_t *history;
	char **env;
	linked_list_t *shell_vars;
} terminal_t;

typedef struct {
	char *cmd_name;
	int (*cmd_func)(terminal_t *term, char **argv);
} builtin_t;

typedef enum {
	ARGUMENT,
	TOKEN,
	COMMAND,
	BUILTIN,
	REDIRECT,
	REDIRECT_INFO
} type_t;

typedef struct {
	int type;
	char *strings;
} node_parser_t;

typedef struct command {
	char **arguments;
	int has_redirection;
	int left_redirection;
	int right_redirection;
	char *left_redirection_type;
	char *left_redirection_arg;
	char *right_redirection_type;
	char *right_redirection_arg;
	bool has_pipe_before;
	bool has_pipe_after;
	bool is_builtin;
	bool is_and;
	bool is_or;
} command_t;

typedef struct parser {
	int nb_nodes;
	node_parser_t *parsing_infos;
	char **to_parse;
	int *types;
	command_t *commands;
} parser_t;

void set_parser_types(parser_t *parser);
int set_parser_commands(parser_t *parser);
int get_cmd_nb_args(parser_t *parser, int start);
void fill_command(parser_t *parser, int start, int nb_cmd);

void display_prompt(void);

char **duplicate_environment(char **env);
void destroy_env(char **env);

char **get_env_var(char **env, char *key);
char *get_env_var_value(char **env, char *key);

int get_tab_size(char **tab);

int mysh(char **env);

int my_exit(char **cmd_args, int *return_value);

int run_cmd(char **env, char **cmd_args, int has_pipe_after);

char **split_path(char const *path);

int handle_builtin(char **cmd_args, terminal_t *term);

int display_environment(terminal_t *term, char **cmd_args);

int command_cd(terminal_t *term, char **cmd_args);
int move_to_home(terminal_t *term);
char *get_home_str(char ***env, char *path);

int builtin_builtins(terminal_t *term, char **cmd_args);

int set_env_var(char ***env, char **cmd_args);
int set_env(terminal_t *term, char **cmd_args);
int unset_env(terminal_t *term, char **cmd_args);

int run_line(char *command, terminal_t *term, int *return_value);
int run_commands(parser_t *parser, terminal_t *term, int *return_value);

int setup_redirections(int pipe_fd[4], int *read_from, command_t *cmd);

void destroy_parser(parser_t *parser);

int my_perror(const char *premessage);

char *isolate_tokens(char **line, const char *to_isolate, \
const char *ignore_start, const char *ignore_end);
int my_array_index(char *word, char **array);

char *my_strndup(char const *str, int n);

int alias(terminal_t *term, char **cmd_args);

int command_echo(terminal_t *term, char **cmd_args);

void destroy_struct(terminal_t *term);
terminal_t *struct_init(char **env);

char **apply_alias(char *alias, char **args, terminal_t *term);

void add_history_elem(char *cmd, terminal_t *term);
int command_history(terminal_t *term, char **cmd_args);

bool is_alias_loop(char *current, linked_list_t **list);
int exec_all_alias(parser_t *parser, terminal_t *term);

int make_globbing(parser_t *parser);

void reset_parser(parser_t *parser, int new_size);

int builtin_set(terminal_t *term, char **cmd_args);
int builtin_unset(terminal_t *term, char **cmd_args);

int parse_vars(terminal_t *term, parser_t *parser);

int is_invalid_array(parser_t *parser);

void read_rc(char **env, terminal_t *term);

void add_elem_to_array(char ***res, int *index, int nb, char *elem);

extern const builtin_t builtin[];

#endif /* __MY_SH_H_ */
