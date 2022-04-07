// !!!!!

#include "../../minishell.h"

int	builtin_pwd(t_data *data)
{
	ft_putstr_fd(data->pwd, 1);
	return (1);
}