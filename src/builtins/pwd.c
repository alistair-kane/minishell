// !!!!!

#include "../../minishell.h"

// !!!!! add new_line char !?
int	builtin_pwd(t_data *data)
{
	ft_putstr_fd(data->pwd, 1); // !!!!! changed to just getpwd()?
	ft_putchar_fd('\n', 1);
	return (1);
}