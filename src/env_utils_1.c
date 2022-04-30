// !!!!!

#include "../minishell.h"

static void	swap_entries(t_environment *first, t_environment *second)
{
	char	name[4096];
	char	value[16384]; // !!!!!
	int		tmp;

	ft_strlcpy(name, first->name, ft_strlen(first->name) + 1);
	ft_strlcpy(value, first->value, ft_strlen(first->value) + 1);
	free(first->name);
	first->name = malloc(ft_strlen(second->name) + 1);
	if (first->name == NULL)
		exit(1);
	ft_strlcpy(first->name, second->name, ft_strlen(second->name) + 1);
	free(first->value);
	if (second->value != NULL)
	{
		first->value = malloc(ft_strlen(second->value) + 1);
		if (first->value == NULL)
			exit(1);
		ft_strlcpy(first->value, second->value, ft_strlen(second->value) + 1);
	}
	else
		first->value = NULL;
	free(second->name);
	second->name = malloc(ft_strlen(name) + 1);
	if (second->name == NULL)
		exit(1);
	ft_strlcpy(second->name, name, ft_strlen(name) + 1);
	free(second->value);
	second->value = malloc(ft_strlen(value) + 1);
	if (second->value == NULL)
		exit(1);
	ft_strlcpy(second->value, value, ft_strlen(value) + 1);
	tmp = first->initial_index;
	first->initial_index = second->initial_index;
	second->initial_index = tmp;
}

void	sort_all_entries(t_vector *env)
{
	int				i;
	int				j;
	int				swaped;
	t_environment	*entry1;
	t_environment	*entry2;

	i = 0;
	while (i < (int)env->total)
	{
		swaped = 0;
		j = -1;
		while (++j < (int)env->total - 1)
		{
			entry1 = vector_get(env, j);
			entry2 = vector_get(env, j + 1);
			if (ft_strcmp(entry1->name, entry2->name) >= 0)
			{
				swap_entries(entry1, entry2);
				swaped = 1;
			}
		}
		if (swaped == 0)
			break ;
		i++;
	}
}

void	add_to_envp(t_data *data, char *name, char *value)
{
	int	i;

	if (value == NULL)
		return ;
	if (data->envp == NULL)
	{
		data->envp = ft_calloc(1024, sizeof(char *)); // !!!!!
		if (data->envp == NULL)
			exit(1);
	}
	i = 0;
	while (data->envp[i] != NULL)
		i++;
	data->envp[i] = malloc(ft_strlen(name) + ft_strlen(value) + 2);
	if (data->envp[i] == NULL)
		exit(1);
	ft_strlcpy(data->envp[i], name, ft_strlen(name) + 1);
	data->envp[i][ft_strlen(name)] = '=';
	ft_strlcpy(&data->envp[i][ft_strlen(name) + 1], value, 
		ft_strlen(value) + 1);
}