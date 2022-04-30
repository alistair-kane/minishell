#include "../../minishell.h"

int	max(int val1, int val2)
{
	if (val1 > val2)
		return (val1);
	return (val2);
}

char	*get_home_dir(t_data *data)
{
	size_t			i;
	t_environment	*temp;

	i = -1;
	while (++i < data->environment->total)
	{
		temp = vector_get(data->environment, i);
		if (!ft_strncmp(temp->name, "HOME", 4))
			return (temp->value);
	}
	return (NULL);
}
