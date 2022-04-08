// !!!!!

#include "../../minishell.h"

int	builtin_pwd(t_data *data)
{
	ft_putstr_fd(data->pwd, 1); // !!!!! changed to just getpwd()?
	return (1);
}