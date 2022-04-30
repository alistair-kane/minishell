// !!!!! add header

#include "../../minishell.h"

static void	exit_helper(t_data *data, char **args, int error);

void	builtin_exit(t_data *data, char **args)
{
	int	error;

	error = 0;
	data->exit = 1;
	if (args[1] == NULL)
		data->exit_value = 0;
	else
	{
		data->exit_value = 255;
		if (ft_isnum(args[1]) == 1)
			data->exit_value = ft_atoi(args[1]);
		else
			error = 1;
	}
	printf("exit\n");
	if (error == 1)
		printf("exit: %s: numeric argument required\n", args[1]);
	exit_helper(data, args, error);
}

static void	exit_helper(t_data *data, char **args, int error)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
		i++;
	if (i > 2)
	{
		if (error == 0)
			printf("exit: too many arguments\n");
		data->exit = error;
		data->exit_value = 1;
	}
}
