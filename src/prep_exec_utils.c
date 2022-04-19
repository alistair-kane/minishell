/// !!!!!

#include "../minishell.h"

t_exec	*init_exec(void)
{
	t_exec	*exec;

	exec = ft_calloc(1, sizeof(t_exec));
	if (exec == NULL)
		builtin_exit(1);
	exec->commands = vector_init(10, 10, 0);
	if (exec->commands == NULL)
		builtin_exit(1);
	return (exec);
}
