// !!!!!

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <dirent.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "libft/vector.h"

# include <stdio.h>

# define PROMPT "$ "

typedef struct s_environment
{
	char	*name;
	char	*value;
}				t_environment;

typedef struct s_data
{
	t_vector	*env;
	t_vector	*environment;
	t_vector	*history;
	char		**path;
	char		*pwd;
}				t_data;

t_data	*data_init(void);

void	data_cleanup(t_data *data);

void	parser(t_data *data, char *buf);

int		builtin_echo(t_data *data, char **buf);
int		builtin_cd(t_data *data, char **buf);
int		builtin_pwd(t_data *data);
int		builtin_export(t_data *data, char **args);
int		builtin_unset(t_data *data, char **args);
int		builtin_env(t_data *data);
void	builtin_exit(int status);

char	**ms_split(char *line);

int		is_reserved_symbol(char *argument);
int		get_name_length(char *entry);

void	sort_all_entries(t_vector *env);

#endif
