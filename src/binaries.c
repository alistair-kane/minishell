// !!!!!

#include "../minishell.h"

static char	*return_path(char **paths, char *execname)
{
	int		i;
	char	*temp;
	char	*path;

	i = -1;
	while (paths[++i] != NULL)
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, execname);
		free(temp);
		if (!access(path, X_OK))
			return (path);
		free(path);
	}
	return (NULL);
}

void	exec_cmd(t_data *data, char **argv)
{
	char		*path;

	if (ft_strrchr(argv[0], '/'))
		path = return_path(data->path, ft_strrchr(argv[0], '/'));
	else
		path = return_path(data->path, argv[0]);
	if (path == NULL)
		exit_error("command not found");
	execve(path, argv, data->envp);
	exit_error(path);
}