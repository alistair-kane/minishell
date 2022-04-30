// !!!!!

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <dirent.h>
# include <sys/stat.h>
# ifdef __linux__
#  include <linux/limits.h> // !!!!! maybe unnecessary for final submission?
# endif
# include <limits.h>
# include <errno.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "libft/vector.h"
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>

# define PROMPT "$ "

# define READ_END 0
# define WRITE_END 1

// 1 = |, 2 = <, 3 = >, 4 = <<, 5 = >>
enum e_reserved_symbol
{
	RESERVED_SYMBOL_PIPE = 1,
	RESERVED_SYMBOL_REDIRECT_INPUT,
	RESERVED_SYMBOL_REDIRECT_OUTPUT,
	RESERVED_SYMBOL_HERE_DOC,
	RESERVED_SYMBOL_APPEND_OUTPUT,
};

// each command is a >> char** <<
typedef struct s_exec
{
	char		*input_file;
	int			here_flag;
	char		*output_files[128];
	int			append_output[128];
	char		*temp_files[128];
	t_vector	*commands;
}				t_exec;

typedef struct s_environment
{
	char	*name;
	char	*value;
	int		initial_index;
}			t_environment;

typedef struct s_args
{
	char	**array;
	size_t	length;
}			t_args;

typedef struct s_data
{
	t_vector	*environment;
	t_vector	*exec;
	t_vector	*history;
	char		**envp;
	char		**path;
	char		pwd[PATH_MAX];
	size_t		args_len;
	pid_t		pid;
	int			status;
	int			exit;
	int			exit_value;
}				t_data;

t_data	*data_init(void);

void	data_cleanup(t_data *data);
void	free_path(t_data *data);
void	cleanup_environment(void *data);
void	cleanup_exec(void *data);
void	cleanup_exec_commands(void *data);

void	parser(t_data *data, char *buf);
void	exec(t_data *data);
void	exit_error(const char *s);
void	open_pipe(int *fds);
void 	redirect_input(t_exec *exec);
void	redirect_output(t_exec *exec, int redir_flag);
void 	close_ends(int *fds);
void	exec_cmd(t_data *data, char **argv);
int		check_parent_builtin(t_data *data, char **cmd, int exec);

int		builtin_echo(t_data *data, char **buf);
int		builtin_cd(t_data *data, char **args);
int		builtin_pwd(t_data *data);
int		builtin_export(t_data *data, char **args);
int		builtin_unset(t_data *data, char **args);
int		builtin_env(t_data *data, char **args);
void	builtin_exit(t_data *data, char **args);

char	**ms_split(t_data *data, char *line);
int		check_binaries(t_data *data, char **args);
int		check_builtin(char **args);
void	exec_builtin(t_data *data, char **args);
int		handle_quotes(char c, int *double_quotes, int *single_quotes);
void	quote_master(char **args);

int		is_reserved_symbol(char *argument);
int		get_name_length(char *entry);
int		get_env_var_end(char *entry);
int		get_name_length_whitespace(char *entry);
void	free_c_vector(char **vector);

void	sort_all_entries(t_vector *env);
char	*env_expansion(t_data *data, char *arg);
void	add_to_envp(t_data *data, char *name, char *value);

void	signal_handler(int signal);

int		prep_exec(t_data *data, char **arguments);
t_exec	*init_exec(void);
char	*handle_here_doc(t_exec *exec, char *delimiter);
char	*create_filename(t_exec *exec, char *filename);

int		check_argument_logic(char **args);

int		get_entry_index(t_vector *env, char *name);
int		get_new_initial_index(t_vector *env);

#endif
