/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:39:51 by alkane            #+#    #+#             */
/*   Updated: 2022/05/02 14:39:52 by alkane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (NULL);
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

int	handle_output(t_exec *exec, char *filename, int append)
{
	int	i;
	int	length;

	if (filename == NULL)
		return (1);
	i = 0;
	while (exec->output_files[i] != NULL)
		i++;
	if (i >= 128)
		return (2);
	exec->append_output[i] = append;
	length = ft_strlen(filename);
	exec->output_files[i] = ft_calloc(length + 1, sizeof(char));
	if (exec->output_files[i] == NULL)
		exit(1);
	ft_strlcpy(exec->output_files[i], filename, length + 1);
	return (2);
}

// 'comsume' every argument until you hit the end or a reserved symbol
int	handle_commands(t_exec *exec, char **arguments)
{
	char	**command;
	int		i;
	int		length;

	command = ft_calloc(128, sizeof(char *));
	if (command == NULL)
		exit(1);
	i = 0;
	while (is_reserved_symbol(arguments[i]) == 0)
	{
		length = ft_strlen(arguments[i]);
		command[i] = malloc(length + 1);
		if (command[i] == NULL)
			exit(1);
		ft_strlcpy(command[i], arguments[i], length + 1);
		i++;
		if (arguments[i] == NULL)
			break ;
	}
	command[i] = NULL;
	vector_add(exec->commands, command);
	return (i);
}
