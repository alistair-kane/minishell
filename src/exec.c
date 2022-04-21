/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alistair <alistair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:54:42 by alkane            #+#    #+#             */
/*   Updated: 2022/04/22 01:08:08 by alistair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_error(const char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

// static int	file_open(const char *name, int o_flags)
// {
// 	int	fd;

// 	fd = open(name, o_flags, 0644);
// 	if (fd < 0)
// 		exit_error(name);
// 	return (fd);
// }

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

static void close_ends(int *fds)
{
	close(fds[READ_END]);
	close(fds[WRITE_END]);
}

static void	piping(t_data *data, t_exec *exec)
{
	pid_t	pid;
	int		new_fds[2];
	int		old_fds[2];
	int		i;
	char	**cmd_1;

	i = 0;
	cmd_1 = vector_get(exec->commands, i);
	while (cmd_1 != NULL)
	{
		if (vector_get(exec->commands, i + 1) != NULL) // if there is a next cmd
		{
			if (pipe(new_fds) == -1)
				exit_error("pipe");
		}
		pid = fork();
		if (pid < 0)
			exit_error("fork");
		if (pid == 0) // child process
		{
			if (i > 0) // if there is a previous cmd
			{
				dup2(old_fds[READ_END], STDIN_FILENO);
				close_ends(old_fds);
			}
			if (vector_get(exec->commands, i + 1) != NULL) // if there is a next cmd
			{
				close(new_fds[READ_END]);
				dup2(new_fds[WRITE_END], STDOUT_FILENO);
				close(new_fds[WRITE_END]);
			}
			if (check_builtin(data, cmd_1))
				exit(0); // exit child after finding built-in
			exec_cmd(data, cmd_1);
			printf("Failed to execute '%s'\n", *cmd_1);
			exit(1);
		}
		else // parent process
		{
			if (i > 0) // if there is a previous cmd
				close_ends(old_fds);
			waitpid(pid, NULL, 0);
			if (vector_get(exec->commands, i + 1) != NULL) // if there is a next cmd
			{
				old_fds[READ_END] = new_fds[READ_END];
				old_fds[WRITE_END] = new_fds[WRITE_END];
			}
			check_builtin(data, cmd_1);
		}
		i++;
		cmd_1 = vector_get(exec->commands, i);
	}
	if (exec->commands->total > 1) // if multiple cmds after loop
		close_ends(old_fds);
}

void	exec(t_data *data)
{
	int		i;
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
		// j = 0;
		cmd = vector_get(exec->commands, 0);
		if (ft_strcmp(cmd[0], "exit") == 0 && exec->commands->total == 1)
			builtin_exit(data, cmd); // !!!!! need to check output behaviour
		else
			piping(data, exec);
		i++;
		// return (EXIT_SUCCESS);
	}
}


/**
 * ignore
if (i == 0)
{
	if (exec->input_file != NULL)
	{
		fd[0] = file_open(exec->input_file, O_RDONLY);
		dup2(fd[READ_END], STDIN_FILENO);
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
	// printf("!in child\n");
	dup2(fd[1], STDOUT_FILENO);
}
**/