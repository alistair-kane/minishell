// !!!!! add header

// will have to take the exit status from pipe later on maybe...?

#include "../../minishell.h"

// !!!!! returns a value between 0 and 255
void	builtin_exit(t_data *data, char **args)
{
	data->exit = 1;
	if (args[1] == NULL)
		data->exit_value = 0;
	else
		data->exit_value = ft_atoi(args[1]);
	//exit(status);
}
