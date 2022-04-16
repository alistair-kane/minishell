// !!!!!

#include "../minishell.h"

static void	cleanup_exec(t_exec *exec);

void	data_cleanup(t_data *data)
{
	if (data == NULL)
		return ;
	free_path(data);
	cleanup_exec(data->exec);
	vector_cleanup(data->environment);
	vector_cleanup(data->history);
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

static void	cleanup_exec(t_exec *exec)
{
	int	i;

	if (exec == NULL)
		return ;
	if (exec->input_file != NULL)
		free(exec->input_file);
	i = 0;
	while (exec->output_files[i] != NULL)
	{
		free(exec->output_files[i]);
		i++;
	}
	vector_cleanup(exec->commands);
}
