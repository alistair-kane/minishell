// !!!!!

#include "../../minishell.h"

static void	export_print_list(t_data *data);
static void	get_key_value_pair(char *argument, t_environment *entry);
static int	is_reserved_symbol(char *argument);

/*
without any arguments, this prints all variables available
*/
// TODO - 1. !!!!! enter in ms -> remove extra newline !!!!! 2. sort the list
int	builtin_export(t_data *data, char **args)
{
	t_environment	entry;

	if (args[1] == NULL)
	{
		export_print_list(data);
		return (1);
	}
	if (is_reserved_symbol(args[1]) == 1)
	{
		export_print_list(data);
		return (1);
	}
	get_key_value_pair(args[1], &entry);
	vector_add(data->environment, &entry);
	return (2);
}

static void	export_print_list(t_data *data)
{
	int				i;
	t_environment	*entry;

	i = 0;
	entry = vector_get(data->environment, i);
	while (entry != NULL)
	{
		if (ft_strlen(entry->value) == 0)
			printf ("declare -x %s\n", entry->name);
		else
			printf ("declare -x %s=\"%s\"\n", entry->name, entry->value);
		i++;
		entry = vector_get(data->environment, i);
	}
}

static void	get_key_value_pair(char *argument, t_environment *entry)
{
	int	length_name;
	int	length_value;

	length_name = get_name_length(argument);
	entry->name = malloc(length_name + 1);
	if (entry->name == NULL)
		return ; // !!!!!
	ft_strlcpy(entry->name, argument, length_name + 1);
	length_value = 0;
	if (argument[length_name] == '=')
		length_value = ft_strlen(&argument[length_name + 1]);
	// !!!!! remove single and double quotes from input (just the one pair around the input)
	entry->value = malloc(length_value + 1);
	if (entry->value == NULL)
		return ; // !!!!!
	ft_strlcpy(entry->value, &argument[length_name + 1], length_value + 1);
}

static int	is_reserved_symbol(char *argument)
{
	if (argument[0] == '|')
		return (1);
	if (argument[0] == '<')
		return (1);
	if (argument[0] == '>')
		return (1);
	// these will never be hit !!!!!
	/*if (ft_strncmp("<<", argument, 2) == 0)
		return (1);
	if (ft_strncmp(">>", argument, 2) == 0)
		return (1);*/
	return (0);
}
