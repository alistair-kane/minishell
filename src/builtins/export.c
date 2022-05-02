// !!!!!

#include "../../minishell.h"

static void	handle_valid_input(t_data *data, t_environment *entry, int update);
static void	export_print_list(t_data *data);
static int	get_key_value_pair(char *argument, t_environment *entry);

// without any arguments, this prints all variables available
int	builtin_export(t_data *data, char **args)
{
	int				i;
	int				update;
	t_environment	entry;

	if (args[1] == NULL)
	{
		export_print_list(data);
		return (1);
	}
	i = 0;
	while (args[++i] != NULL)
	{
		update = get_key_value_pair(args[i], &entry);
		if (is_valid_entry_name(entry.name) == 0)
		{
			printf ("export: '%s': not a valid identifier\n", entry.name);
			free(entry.name);
			if (entry.value != NULL)
				free(entry.value);
			return (i);
		}
		handle_valid_input(data, &entry, update);
	}
	sort_all_entries(data->environment);
	return (i);
}

static void	handle_valid_input(t_data *data, t_environment *entry, int update)
{
	int				index;

	if (ft_strcmp("PATH", entry->name) == 0)
	{
		free_path(data);
		data->path = ft_split(entry->value, ':');
	}
	index = get_entry_index(data->environment, entry->name);
	if (index >= 0)
	{
		if (update == 1)
			update_existing_entry(data->environment, index, entry->value);
		free(entry->name);
		free(entry->value);
	}
	else
	{
		entry->initial_index = get_new_initial_index(data->environment);
		vector_add(data->environment, entry);
		add_to_envp(data, entry->name, entry->value);
	}
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

static int	get_key_value_pair(char *argument, t_environment *entry)
{
	int	length_name;
	int	length_value;
	int	update;

	update = 1;
	argument = remove_surrounding_quotes(argument);
	length_name = get_name_length(argument);
	entry->name = malloc(length_name + 1);
	if (entry->name == NULL)
		exit(1);
	ft_strlcpy(entry->name, argument, length_name + 1);
	length_value = 0;
	if (argument[length_name] == '=')
		length_value = ft_strlen(&argument[length_name + 1]);
	else
		update = 0;
	entry->value = ft_calloc(length_value + 1, sizeof(char));
	if (entry->value == NULL)
		exit(1);
	if (length_value != 0)
		ft_strlcpy(entry->value, &argument[length_name + 1], length_value + 1);
	free(argument);
	return (update);
}
