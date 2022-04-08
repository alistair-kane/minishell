// !!!!!

#include "../../minishell.h"

int	builtin_env(t_data *data)
{
	int				i;
	t_environment	*entry;

	i = 0;
	entry = vector_get(data->env, i);
	while (entry != NULL)
	{
		if (ft_strlen(entry->value) != 0)
			printf ("%s=%s\n", entry->name, entry->value);
		i++;
		entry = vector_get(data->env, i);
	}
	return (1);
}
