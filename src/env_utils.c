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

static void	env_var_replace(t_data *data, char **var_holder)
{
	t_environment	*temp;
	size_t			i;

	i = -1;
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

static char	*expansion_ops(t_data *data, char *arg, int j)
{
	int		end;
	int		total_len;
	char	*new_arg;
	char	*var_holder;
	char	trail[4096];

	total_len = ft_strlen(arg) + 1;
	new_arg = ft_calloc(PATH_MAX, 1);
	var_holder = ft_calloc(PATH_MAX, 1);
	j += 1;
	end = j + get_name_length_whitespace(&arg[j]);
	ft_strlcpy(new_arg, arg, j);
	ft_strlcpy(var_holder, &arg[j], end - j + 1);
	ft_strlcpy(trail, &arg[end], total_len - end);
	env_var_replace(data, &var_holder);
	if (var_holder == NULL)
		ft_strlcat(new_arg, trail, ft_strlen(new_arg) + ft_strlen(trail) + 1);
	else
	{
		total_len = ft_strlcat(new_arg, var_holder, ft_strlen(new_arg) \
			+ ft_strlen(var_holder) + 1);
		ft_strlcat(new_arg, trail, total_len + ft_strlen(trail) + 1);
	}
	free(var_holder);
	return (new_arg);
}

void	check_reset(char *arg, int *delp1, int *delp2, int *i)
{
	if (*delp1 != -1 && *delp2 != -1)
	{
		*delp2 -= 1;
		ft_memmove(&arg[*delp1], &arg[*delp1 + 1], ft_strlen(arg) - *delp1);
		ft_memmove(&arg[*delp2], &arg[*delp2 + 1], ft_strlen(arg) - *delp2);
		*delp1 = -1;
		*delp2 = -1;
		*i -= 2;
	}
}

void	char_cleanup(char *arg)
{
	int	i;
	int	delp1;
	int	delp2;
	int	single;
	int	dbl;

	single = 0;
	dbl = 0;
	delp1 = -1;
	delp2 = -1;
	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '\'' || arg[i] == '"')
		{
			if (handle_quotes(arg[i], &dbl, &single) == 1)
			{
				if (delp1 == -1)
					delp1 = i;
				else
					delp2 = i;
			}
		}
		check_reset(arg, &delp1, &delp2, &i);
	}
}

void	env_expansion(t_data *data, char **args)
{
	int	i;
	int	j;
	int	sqf;
	int	dqf;

	i = -1;
	sqf = -1;
	dqf = -1;
	while (args[++i] != NULL)
	{
		j = -1;
		while (args[i][++j])
		{
			if (args[i][j] == '\"')
				dqf *= -1;
			if (args[i][j] == '\'' && dqf == -1)
				sqf *= -1;
			if (args[i][j] == '\\')
				j++;
			else if (args[i][j] == '$' && sqf == -1)
				args[i] = expansion_ops(data, args[i], j);
		}
		char_cleanup(args[i]);
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
