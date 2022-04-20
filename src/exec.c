/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:54:42 by alkane            #+#    #+#             */
/*   Updated: 2022/04/20 16:55:49 by alkane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_error(const char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

static int	file_open(const char *name, int o_flags)
{
	int	fd;

	fd = open(name, o_flags, 0644);
	if (fd < 0)
		exit_error(name);
	return (fd);
}

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

static char	*seek_path(t_data *data, char *execname)
{
	if (return_path(data->path, execname))
		return (return_path(data->path, execname));
	free(execname);
	return (NULL);
}

static void	exec_cmd(t_data *data, char **argv)
{
	char		*path;
	extern char	**environ;

	printf("!in exec %s\n", argv[0]);
	if (ft_strrchr(argv[0], '/'))
		path = seek_path(data, ft_strrchr(argv[0], '/'));
	else
		path = seek_path(data, argv[0]);
	if (path == NULL)
		exit_error("command not found");
	execve(path, argv, environ);
	exit_error(path);
}

static void	piping(t_data *data, char **argv, int i, t_exec *exec)
{
	int	pid;
	int	fd[2];
	int	j;
	char buf[1000];

	printf("!in piping %s\n", argv[0]);
	if (pipe(fd) == -1)
		exit_error("pipe");
	pid = fork();
	if (pid < 0)
		exit_error("fork");
	if (pid > 0)
	{	
		close(fd[1]);
		// dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
		read(fd[0], buf, 1000);
		printf("buf: %s", buf);
		close(fd[0]);
	}
	else
	{		
		if (i == 0)
		{
			if (exec->input_file != NULL)
			{
				fd[0] = file_open(exec->input_file, O_RDONLY);
				dup2(fd[0], STDIN_FILENO);
			}
		}
		if (i == (int)exec->commands->total - 1)
		{
			j = 0;
			while (exec->output_files[j] != NULL)
			{
				fd[1] = file_open(exec->output_files[j], O_WRONLY | O_CREAT | O_TRUNC);
				j++;
			}
			printf("!in child\n");
			dup2(fd[1], STDOUT_FILENO);
		}
		printf("!in child2222\n");
		// !!!!! read from child in parent here
		close(fd[0]);
		// dup2(fd[1], STDOUT_FILENO);
		if (check_builtin(data, argv) == 0)
			exec_cmd(data, argv);
		close(fd[1]);
	}
}

void	exec(t_data *data)
{
	int		i;
	int		j;
	int		fd[2];
	t_exec	*exec;
	char	**cmd;

	i = 0;
	while (i < (int)data->exec->total)
	{
		exec = vector_get(data->exec, i);
		// need to handle here_doc here
		// if (!ft_strncmp(exec->input_file, "here_doc", ft_strlen(argv[1])))
		// {
		// 	fd[0] = file_open(input_to_limiter(argv[2]), O_RDONLY);
		// 	fd[1] = file_open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND);
		// 	i = 2;
		// }
		// else
		// {
		j = 0;
		cmd = vector_get(exec->commands, j);
		while (cmd != NULL)
		{
			if (ft_strcmp(cmd[0], "exit") == 0 && exec->commands->total == 1)
				builtin_exit(0); // !!!!! need to check output behaviour
			else	
				piping(data, cmd, j, exec);
			j++;
			cmd = vector_get(exec->commands, j);
		}
		// exec_cmd(data, cmd);
		close(fd[0]);
		close(fd[1]);
		i++;
		// return (EXIT_SUCCESS);
	}
}
