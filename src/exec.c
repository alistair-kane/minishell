// !!!!! 
#include "../minishell.h"

void	exit_error(const char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
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

	// printf("!in exec %s\n", argv[0]);
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

// static void parent_helper(t_data *data, t_exec *exec, pid_t pid, int i)

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
			else if (i == 0 && exec->input_file != NULL) // at first cmd and input file is given
				redirect_input(exec);
			if (vector_get(exec->commands, i + 1) != NULL) // if there is a next cmd
			{
				close(new_fds[READ_END]);
				dup2(new_fds[WRITE_END], STDOUT_FILENO);
				close(new_fds[WRITE_END]);
			}
			else if (exec->output_files[0] != NULL) // if there is no next cmd and output file
				redirect_output(exec);
			if (check_builtin(cmd_1))
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
			exec_builtin(data, cmd_1);
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
		cmd = vector_get(exec->commands, 0);
		if (cmd == NULL)
			return ; // !!!!! need to create output files
		else
		{
			if (ft_strcmp(cmd[0], "exit") == 0 && exec->commands->total == 1)
				builtin_exit(data, cmd); // !!!!! need to check output behaviour
			else
				piping(data, exec);
			i++;
		}
	}
}
