// !!!!!

#include "../../minishell.h"

// removes quotes around the name and the value of the current argument
char	*remove_surrounding_quotes(char *input)
{
	char	*result;
	int		length;
	int		length_name;

	length = ft_strlen(input);
	length_name = get_name_length(input);
	result = malloc(length + 1);
	if (result == NULL)
		exit(1);
	if ((input[0] == '"' && input[length_name - 1] == '"')
		|| (input[0] == '\'' && input[length_name - 1] == '\''))
		ft_strlcpy(result, &input[1], length_name - 2 + 1);
	else
		ft_strlcpy(result, input, length_name + 1);
	if (length_name != length)
	{
		result[ft_strlen(result) + 1] = '\0';
		result[ft_strlen(result)] = '=';
		if ((input[length_name + 1] == '"' && input[length - 1] == '"')
			|| (input[length_name + 1] == '\'' && input[length - 1] == '\''))
			ft_strlcpy(&result[ft_strlen(result)], &input[length_name + 2],
				length - length_name - 2);
		else
			ft_strlcpy(&result[ft_strlen(result)], &input[length_name + 1],
				length - length_name);
	}
	return (result);
}

// returns the index of an existing entry name
int	get_entry_index(t_vector *env, char *name)
{
	int				i;
	t_environment	*entry;

	i = 0;
	entry = vector_get(env, i);
	while (entry != NULL)
	{
		if (ft_strcmp(name, entry->name) == 0)
			return (i);
		i++;
		entry = vector_get(env, i);
	}
	return (-1);
}

void	update_existing_entry(t_vector *env, int index, char *new_value)
{
	t_environment	*entry;

	if (new_value != NULL)
	{
		entry = vector_get(env, index);
		if (entry == NULL)
			return ;
		free(entry->value);
		entry->value = malloc(ft_strlen(new_value) + 1);
		if (entry->value == NULL)
			exit(1);
		ft_strlcpy(entry->value, new_value, ft_strlen(new_value) + 1);
	}
}

// if all variables are removed at some point, 
// the starting index will be 1, not 0 anymore
int	get_new_initial_index(t_vector *env)
{
	int				i;
	int				highest_index;
	t_environment	*entry;

	highest_index = 0;
	i = 0;
	entry = vector_get(env, i);
	while (entry != NULL)
	{
		if (entry->initial_index > highest_index)
			highest_index = entry->initial_index;
		i++;
		entry = vector_get(env, i);
	}
	highest_index++;
	return (highest_index);
}

int	is_valid_entry_name(char *name)
{
	if (ft_isalpha(*name) == 0 && *name != '_')
		return (0);
	while (*name != '\0')
	{
		if (ft_isalnum(*name) == 0 && *name != '_')
			return (0);
		name++;
	}
	return (1);
}