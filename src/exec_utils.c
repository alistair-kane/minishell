// !!!!!

#include "../minishell.h"

static int	file_open(const char *name, int o_flags)
{
	int	fd;

	fd = open(name, o_flags, 0644);
	if (fd < 0)
		exit_error(name);
	return (fd);
}

void open_pipe(int *fds)
{
	if (pipe(fds) == -1)
		exit_error("pipe");
}

void redirect_input(t_exec *exec)
{
	int inputfd;
	
	inputfd = file_open(exec->input_file, O_RDONLY);
	dup2(inputfd, STDIN_FILENO);
	close(inputfd);
	// !!!!! flag for the here_doc to stop deletion of normal input files (unsure of behaviour if mulitple inputs and here with flag however)
	if (exec->here_flag) 
		unlink(exec->input_file);
}

void redirect_output(t_exec *exec)
{
	int j = 0;
	int outputfd;

	while (exec->output_files[j] != NULL)
	{
		if (exec->append_output[j]) // >>
			outputfd = file_open(exec->output_files[j], O_WRONLY | O_CREAT | O_APPEND);
		else // >
			outputfd = file_open(exec->output_files[j], O_WRONLY | O_CREAT | O_TRUNC);
		if (exec->output_files[j + 1] == NULL)
			dup2(outputfd, STDOUT_FILENO);
		close(outputfd);
		j++;
	}
}

void close_ends(int *fds)
{
	close(fds[READ_END]);
	close(fds[WRITE_END]);
}