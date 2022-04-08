// !!!!!

#include "../minishell.h"

void	data_cleanup(t_data *data)
{
	if (data == NULL)
		return ;
	// !!!!! cleanup mallocs of the environment structs -> custom_cleanup
	vector_cleanup(data->environment);
	vector_cleanup(data->env);
	vector_cleanup(data->history);
	free(data);
}
