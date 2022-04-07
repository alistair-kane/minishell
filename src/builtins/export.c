// !!!!!

#include "../../minishell.h"

static void	export_print_list(t_data *data);
static void	get_key_value_pair(char *argument, t_environment *entry);
static int	get_entry_index(t_vector *env, char *name);
static void	update_existing_entry(t_vector *env, int index, char *new_value);

/*
without any arguments, this prints all variables available
*/
// TODO - 1. !!!!! enter in ms -> remove extra newline !!!!!
int	builtin_export(t_data *data, char **args)
{
	int				index;
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
	if (ft_strncmp("PATH", entry.name, ft_strlen(entry.name)) == 0)
	{
		// !!!!! free old path
		data->path = ft_split(entry.value, ':');
	}
	index = get_entry_index(data->environment, entry.name);
	if (index >= 0)
		update_existing_entry(data->environment, index, entry.value);
	else
		vector_add(data->environment, &entry);
	sort_all_entries(data->environment);
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
		builtin_exit(1);
	ft_strlcpy(entry->name, argument, length_name + 1);
	length_value = 0;
	if (argument[length_name] == '=')
		length_value = ft_strlen(&argument[length_name + 1]);
	// !!!!! remove single and double quotes from input (just the one pair around the input)
	entry->value = malloc(length_value + 1);
	if (entry->value == NULL)
		builtin_exit(1);
	ft_strlcpy(entry->value, &argument[length_name + 1], length_value + 1);
}

// returns the index of an existing entry name
static int	get_entry_index(t_vector *env, char *name)
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

static void	update_existing_entry(t_vector *env, int index, char *new_value)
{
	t_environment	*entry;

	entry = vector_get(env, index);
	if (entry == NULL)
		return ;
	free(entry->value);
	entry->value = malloc(ft_strlen(new_value) + 1);
	if (entry->value == NULL)
		builtin_exit(1);
	ft_strlcpy(entry->value, new_value, ft_strlen(new_value) + 1);
}
