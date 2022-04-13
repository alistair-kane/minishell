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

// static void	env_var_replace(t_data *data, char **argp, char *arg)
// {
// 	t_environment	*temp;
// 	size_t			i;
// 	char			*ret;

// 	i = -1;
// 	ret = NULL;
// 	while (++i < data->environment->total && argp)
// 	{
// 		temp = vector_get(data->environment, i);
// 		printf("%s\n", arg);
// 		if (!ft_strcmp(temp->name, arg))
// 		{
// 			printf("arg in replace func %s\n", arg);
			// ret = ft_calloc(ft_strlen(temp->value) + 1, sizeof(char));
			// ft_strlcpy(ret, temp->value, ft_strlen(temp->value) + 1);
	// 		*argp = ret;
	// 		// !!!!! I thought reassigning the pointer like this would cause leaks, valgrind shows nothing though
		// }
	// }
	// if (!ret)
	// {
	// 	ret = ft_calloc(1, sizeof(char));
	// 	*argp = ret;
// 	}
// }

void	env_expansion(t_data *data, char **args)
{
	int	i;
	int	j;
	int	start;
	int	end;
	// char *temp;

	i = -1;
	while (args[++i] != NULL && data)
	{
		// get the environmental variables
		// loop through environ.name looking for a full match with arg[i] + 1 (after $)
		// if found, change the text where arg[i] is to be the text held in envion.value
		printf("arg passed in: %s\n", args[i]);

		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '\\')
				j += 2;
			else if (args[i][j] == '$')
			{
				start = j + 1;
				// end = start + get_name_length_whitespace(&args[i][j]);
				// printf("string: %s\nstart:%d\nend:%d\n", &args[i][j], start, end);
				// temp = ft_strnstr(args[i], &args[i][j + 1], (end - j));
				// printf("temp: %s\n", ft_strnstr(args[i], &args[i][start], end - start));
				// env_var_replace(data, args, NULL);
				// printf("strnstr: %s\n",);
				// temp = &args[i][j]
			}
			j++;

		}
// "asdbf '$PATH' dsfgad"



		// if (args[i][0] == '$')
		// {
		// 	temp = args[i] + 1;
		// 	env_var_replace(data, &args[i], temp);
		// }
		// // closed "" handled
		// else if (args[i][0] == '"' && args[i][1] == '$')
		// {
		// 	// needs to behave like printf , ie printing all other chars around $
		// 	temp = args[i] + 2;
		// 	temp = ft_strtrim(temp, "\"");
		// 	env_var_replace(data, &args[i], temp);
		// 	free(temp);	
		// }
	}
}
