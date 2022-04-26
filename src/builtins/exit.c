// !!!!! add header

// will have to take the exit status from pipe later on maybe...?

#include "../../minishell.h"

// !!!!! returns a value between 0 and 255
void	builtin_exit(t_data *data, char **args)
{
	int	i;

	data->exit = 1;
	if (args[1] == NULL)
		data->exit_value = 0;
	else
		data->exit_value = ft_atoi(args[1]);
	i = 1;
	while (args[i] != NULL)
		i++;
	if (i > 2)
	{
		printf("exit: too many arguments\n");
		data->exit = 0;
		data->exit_value = 0;
	}
}
