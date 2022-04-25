// !!!!!
#include "../minishell.h"

int	check_parent_builtin(t_data *data, char **cmd, int exec)
{
	if (ft_strcmp(cmd[0], "cd") == 0 || ft_strcmp(cmd[0], "unset") == 0 \
		|| (ft_strcmp(cmd[0], "export") == 0 && cmd[1] != NULL))
	{
		if (exec == 1)
		{
			if (!ft_strcmp(cmd[0], "cd"))
				builtin_cd(data, cmd);
			else if (!ft_strcmp(cmd[0], "unset"))
				builtin_unset(data, cmd);
			else if (!ft_strcmp(cmd[0], "export"))
				builtin_export(data, cmd);
			data->status = 0;
		}
		else
			return (1);
	}
	return (0);
}