// !!!!!

#include "../minishell.h"

void	data_cleanup(t_data *data)
{
	if (data == NULL)
		return ;
	free_path(data);
	free_c_vector(data->envp);
	vector_cleanup(data->exec);
	vector_cleanup(data->environment);
	free(data);
}

void	free_path(t_data *data)
{
	int	i;

	if (data == NULL || data->path == NULL)
		return ;
	i = 0;
	while (data->path[i] != NULL)
	{
		free(data->path[i]);
		i++;
	}
	free(data->path); //? !!!!!
}

void	cleanup_environment(void *data)
{
	t_environment	*entry;

	entry = data;
	if (entry->name != NULL)
		free(entry->name);
	if (entry->value != NULL)
		free(entry->value);
}

void	cleanup_exec(void *data)
{
	int		i;
	t_exec	*exec;

	if (data == NULL)
		return ;
	exec = data;
	if (exec->input_file != NULL)
		free(exec->input_file);
	i = 0;
	while (exec->output_files[i] != NULL)
	{
		free(exec->output_files[i]);
		i++;
	}
	i = 0;
	while (exec->temp_files[i] != NULL)
	{
		unlink(exec->temp_files[i]);
		free(exec->temp_files[i]);
		i++;
	}
	vector_cleanup(exec->commands);
}

void	cleanup_exec_commands(void *data)
{
	char	**commands;
	int		i;

	if (data == NULL)
		return ;
	commands = data;
	i = 0;
	while (commands[i] != NULL)
	{
		free(commands[i]);
		i++;
	}
}
