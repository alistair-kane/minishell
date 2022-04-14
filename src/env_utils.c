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

static void env_var_replace(t_data *data, char **var_holder)
{
	t_environment	*temp;
	size_t			i;

	i = -1;
	printf("var holder %s\n", *var_holder);
	while (++i < data->environment->total)
	{
		temp = vector_get(data->environment, i);
		if (!ft_strcmp(temp->name, *var_holder))
		{
			ft_strlcpy(*var_holder, temp->value, ft_strlen(temp->value) + 1);
			return ;
		}
	}
	*var_holder = NULL;
}

static void expansion_ops(t_data *data, char **args, int i, int j)
{
	int		start; // could be removed/substituted for j only, but makes code less clear
	int		end;
	int		total_len;
	char	*var_holder;
	char	trailing[4096];

	total_len = ft_strlen(args[i]) + 1;
	var_holder = ft_calloc(PATH_MAX, 1);
	start = j + 1;
	end = start + get_name_length_whitespace(&args[i][start]);
	ft_strlcpy(var_holder, &args[i][start], end - start + 1);
	ft_strlcpy(trailing, &args[i][end], total_len - end);
	printf("trailing %s\n", trailing);
	env_var_replace(data, &var_holder);
	printf("var holder: %s\n", var_holder);
	args[i][start - 1] = '\0';
	if (var_holder == NULL)
		ft_strlcat(args[i], trailing, total_len);
	else
	{
		total_len = ft_strlcat(args[i], var_holder, total_len + ft_strlen(var_holder));
		ft_strlcat(args[i], trailing, total_len + ft_strlen(trailing) + 1);
	}
	free(var_holder);
}

void	env_expansion(t_data *data, char **args)
{
	int	i;
	int	j;

	i = -1;
	while (args[++i] != NULL && data)
	{
		j = 0;
		if (args[i][j] == '\'' && args[i][ft_strlen(args[i]) - 1] == '\'')
			return ;
		while (args[i][j])
		{
			if (args[i][j] == '\\')
				j += 2;
			else if (args[i][j] == '$')
				expansion_ops(data, args, i, j);
			j++;
		}
	}
}

