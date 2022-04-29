/// !!!!!

#include "../minishell.h"

t_exec	*init_exec(void)
{
	t_exec	*exec;

	exec = ft_calloc(1, sizeof(t_exec));
	if (exec == NULL)
		exit(1);
	exec->commands = vector_init(10, 10, 0);
	if (exec->commands == NULL)
		exit(1);
	exec->here_flag = 0;
	vector_custom_cleanup(exec->commands, &cleanup_exec_commands);
	return (exec);
}

char	*handle_here_doc(t_exec *exec, char *delimiter)
{
	char	*filename;
	char	*line;
	char	*new_delimiter;
	int		fd;

	if (delimiter == NULL)
		return (NULL);
	new_delimiter = ft_strjoin(delimiter, "\n");
	filename = create_filename(exec, "temp");
	if (filename == NULL)
		return (NULL); // !!!!! todo: catch return with no file
	fd = open(filename, O_RDWR | O_CREAT, 0644);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL || ft_strcmp(line, new_delimiter) == 0)
			break ;
		write(fd, line, ft_strlen(line));
	}
	close(fd);
	free(new_delimiter);
	return (filename);
}

char	*create_filename(t_exec *exec, char *filename)
{
	int	i;

	filename = ft_strjoin("./", filename);
	i = ft_strlen(filename) - 1;
	while (access(filename, F_OK) == 0)
	{
		if (filename[i] == 'z' || filename[i] == 'Z')
			i--;
		if (i == 0)
		{
			free(filename);
			return (NULL);
		}
		filename[i]++;
	}
	i = 0;
	while (exec->temp_files[i] != NULL)
		i++;
	exec->temp_files[i] = filename;
	return (filename);
}
