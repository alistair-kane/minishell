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
	char	value[16384]; // !!!!!
	int		tmp;

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
	tmp = first->initial_index;
	first->initial_index = second->initial_index;
	second->initial_index = tmp;
}

static void	env_var_replace(t_data *data, char **argp, char *arg)
{
	t_environment	*temp;
	size_t			i;
	char			*ret;

	i = -1;
	ret = NULL;
	while (++i < data->environment->total)
	{
		temp = vector_get(data->environment, i);
		if (!ft_strcmp(temp->name, arg))
		{
			ret = ft_calloc(ft_strlen(temp->value) + 1, sizeof(char));
			ft_strlcpy(ret, temp->value, ft_strlen(temp->value) + 1);
			*argp = ret;
			// !!!!! I thought reassigning the pointer like this would cause leaks, valgrind shows nothing though
		}
	}
	if (!ret)
	{
		ret = ft_calloc(1, sizeof(char));
		*argp = ret;
	}
}

void	env_expansion(t_data *data, char **args)
{
	int	i;
	char *temp;

	i = -1;
	while (args[++i] != NULL)
	{
		// get the environmental variables
		// loop through environ.name looking for a full match with arg[i] + 1 (after $)
		// if found, change the text where arg[i] is to be the text held in envion.value
		if (args[i][0] == '$')
		{
			temp = args[i] + 1;
			env_var_replace(data, &args[i], temp);
		}
		// closed "" handled
		else if (args[i][0] == '"' && args[i][1] == '$')
		{
			temp = args[i] + 2;
			temp = ft_strtrim(temp, "\"");
			env_var_replace(data, &args[i], temp);
			free(temp);	
		}
	}
}
