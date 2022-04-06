// !!!!!

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
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
	t_vector	*environment;
	t_vector	*history;
	//char		**path; !!!!! to we need this??
}				t_data;

t_data	*data_init(void);
void	data_cleanup(t_data *data);

void	parser(t_data *data, char *buf);

int		builtin_echo(t_data *data, char **buf);

char	**ms_split(char *line);

#endif
