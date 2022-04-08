// !!!!!

#include "../../minishell.h"

/*
if no viable argument is found, return without doing anything
*/
int	builtin_unset(t_data *data, char **args)
{
	int				i;
	t_environment	*entry;

	if (args[1] == NULL)
		return (1);
	if (is_reserved_symbol(args[1]) == 1)
		return (1);
	i = 0;
	entry = vector_get(data->environment, i);
	while (entry != NULL)
	{
		if (ft_strncmp(args[1], entry->name, ft_strlen(entry->name)) == 0)
		{
			vector_delete(data->environment, i);
			if (ft_strncmp("PATH", args[1], ft_strlen(args[1])) == 0)
			{
				// todo !!!!! free data->path
				data->path = NULL;
			}
			return (2);
		}
		i++;
		entry = vector_get(data->environment, i);
	}
	return (1);
}
