// !!!!! 
#include "../minishell.h"

void	exit_error(const char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

static void	child_helper(t_data *data, t_exec *exec, int *fds, int i)
{
	char	**cmd;

	cmd = vector_get(exec->commands, i);
	if (i > 0) // if there is a previous cmd
	{
		dup2((fds +2)[READ_END], STDIN_FILENO);
		close_ends(fds +2);
	}
	else if (i == 0 && exec->input_file != NULL) // at first cmd and input file is given
		redirect_input(exec);
	if (vector_get(exec->commands, i + 1) != NULL) // if there is a next cmd
	{
		close(fds[READ_END]);
		dup2(fds[WRITE_END], STDOUT_FILENO);
		close(fds[WRITE_END]);
	}
	else if (exec->output_files[0] != NULL) // if there is no next cmd and output file
		redirect_output(exec, 1);
	// if (ft_strcmp(cmd[0], "cd") == 0 || ft_strcmp(cmd[0], "unset") == 0)
	if (check_parent_builtin(data, cmd, 0))
		exit(0); // exit child after finding built-in cd or unset or export with params
	else if (check_builtin(cmd))
	{
		exec_builtin(data, cmd);
		exit(0);
	}
	else
		exec_cmd(data, cmd);
	printf("Failed to execute '%s'\n", *cmd);
	exit(1);
}

static void parent_helper(t_data *data, t_exec *exec, int *fds, int i)
{
	if (i > 0) // if there is a previous cmd
		close_ends(fds + 2);
	waitpid(data->pid, &(data->status), 0);
	if (vector_get(exec->commands, i + 1) != NULL) // if there is a next cmd
	{
		(fds +2)[READ_END] = fds[READ_END];
		(fds +2)[WRITE_END] = fds[WRITE_END];
	}
	check_parent_builtin(data, vector_get(exec->commands, i), 1);
}

static void	piping(t_data *data, t_exec *exec)
{
	int		fds[4];
	int		i;
	char	**cmd_1;

	i = 0;
	cmd_1 = vector_get(exec->commands, i);
	while (cmd_1 != NULL)
	{
		if (vector_get(exec->commands, i + 1) != NULL) // if there is a next cmd
			open_pipe(fds);
		data->pid = fork();
		if (data->pid < 0)
			exit_error("fork");
		if (data->pid == 0) // child process
			child_helper(data, exec, fds, i);
		else // parent process
			parent_helper(data, exec, fds, i);
		cmd_1 = vector_get(exec->commands, ++i);
	}
	if (exec->commands->total > 1) // if multiple cmds after loop
		close_ends(fds + 2);
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
		{
			redirect_output(exec, 0); // create output files
		}
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
