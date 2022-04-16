/// !!!!!

#include "../minishell.h"

t_exec	*init_exec(void)
{
	t_exec	*exec;

	exec = ft_calloc(1, sizeof(t_exec));
	if (exec == NULL)
		builtin_exit(1);
	exec->commands = vector_init(10, 10, sizeof(char **));
	if (exec->commands == NULL)
		builtin_exit(1);
	return (exec);
}

void	cleanup_exec(t_exec *exec)
{
	int	i;

	if (exec == NULL)
		return ;
	if (exec->input_file != NULL)
		free(exec->input_file);
	i = 0;
	while (exec->output_files[i] != NULL)
	{
		free(exec->output_files[i]);
		i++;
	}
	vector_cleanup(exec->commands);
	ft_bzero(exec, sizeof(t_exec));
}
