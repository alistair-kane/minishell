// !!!!!

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <dirent.h>
# include <sys/stat.h>
# ifdef __linux__
#  include <linux/limits.h> // maybe unnecessary for final submission?
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

# define PROMPT "$ "

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
	t_vector	*history;
	char		**path;
	char		*pwd;
	size_t		args_len;
}				t_data;

t_data	*data_init(void);

void	data_cleanup(t_data *data);
void	free_path(t_data *data);
void	cleanup_environment(void *data);

void	parser(t_data *data, char *buf);

int		builtin_echo(t_data *data, char **buf);
int		builtin_cd(t_data *data, char **args);
int		builtin_pwd(t_data *data);
int		builtin_export(t_data *data, char **args);
int		builtin_unset(t_data *data, char **args);
int		builtin_env(t_data *data);
void	builtin_exit(int status);

char	**ms_split(t_data *data, char *line);
int		check_binaries(t_data *data, char **args);

int		is_reserved_symbol(char *argument);
int		get_name_length(char *entry);

void	sort_all_entries(t_vector *env);
void	env_expansion(t_data *data, char **args);

#endif
