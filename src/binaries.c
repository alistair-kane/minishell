/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:41:27 by alkane            #+#    #+#             */
/*   Updated: 2022/05/02 19:14:31 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char	*path;
	char	*temp;

	if (argv[0][0] == '/')
		path = argv[0];
	else if (ft_strrchr(argv[0], '/'))
	{
		temp = ft_strjoin(data->pwd, "/");
		path = ft_strjoin(temp, argv[0]);
		free(temp);
	}
	else
		path = return_path(data->path, argv[0]);
	if (path == NULL)
		exit_error("command not found");
	execve(path, argv, data->envp);
	exit_error(path);
}
