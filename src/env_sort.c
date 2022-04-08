// !!!!!

#include "../minishell.h"

static void	swap_entries(t_environment *first, t_environment *second);

// !!!!! works but should be optimized !?
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

static void	swap_entries(t_environment *first, t_environment *second)
{
	char	name[4096];
	char	value[4096];

	ft_strlcpy(name, first->name, ft_strlen(first->name) + 1);
	ft_strlcpy(value, first->value, ft_strlen(first->value) + 1);
	free(first->name);
	first->name = malloc(ft_strlen(second->name) + 1);
	if (first->name == NULL)
		builtin_exit(1);
	ft_strlcpy(first->name, second->name, ft_strlen(second->name) + 1);
	free(first->value);
	first->value = malloc(ft_strlen(second->value) + 1);
	if (first->value == NULL)
		builtin_exit(1);
	ft_strlcpy(first->value, second->value, ft_strlen(second->value) + 1);
	free(second->name);
	second->name = malloc(ft_strlen(name) + 1);
	if (second->name == NULL)
		builtin_exit(1);
	ft_strlcpy(second->name, name, ft_strlen(name) + 1);
	free(second->value);
	second->value = malloc(ft_strlen(value) + 1);
	if (second->value == NULL)
		builtin_exit(1);
	ft_strlcpy(second->value, value, ft_strlen(value) + 1);
}
