// !!!!!

#include <stdio.h>

#include <stdlib.h>
#include "../minishell.h"

static void	init_environment(t_data *data);
static void	init_env_structs(t_data *data);
static void	init_paths(t_data *data);

t_data	*data_init(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->history = vector_init(100, 100, 0);
	if (data->history == NULL)
	{
		data_cleanup(data);
		return (NULL);
	}
	init_environment(data);
	vector_custom_cleanup(data->environment, cleanup_environment);
	init_paths(data);
	return (data);
}

static void	init_environment(t_data *data)
{
	extern char		**environ;
	int				i;
	int				length_name;
	int				length_value;
	t_environment	entry;

	init_env_structs(data);
	i = 0;
	while (environ[i] != NULL)
	{
		length_name = get_name_length(environ[i]);
		entry.name = malloc(length_name + 1);
		if (entry.name == NULL)
			builtin_exit(1);
		ft_strlcpy(entry.name, environ[i], length_name + 1);
		length_value = ft_strlen(&environ[i][length_name + 1]);
		entry.value = malloc(length_value + 1);
		if (entry.value == NULL)
			builtin_exit(1);
		ft_strlcpy(entry.value, &environ[i][length_name + 1], length_value + 1);
		entry.initial_index = i;
		vector_add(data->environment, &entry);
		i++;
	}
	sort_all_entries(data->environment);
}

static void	init_env_structs(t_data *data)
{
	data->environment = vector_init(100, 100, sizeof(t_environment));
	if (data->environment == NULL)
		builtin_exit(1);
}

static void	init_paths(t_data *data)
{
	int				i;
	t_environment	*entry;

	i = 0;
	entry = vector_get(data->environment, i);
	while (entry != NULL)
	{
		if (!ft_strncmp(entry->name, "PATH", ft_strlen(entry->name)))
			data->path = ft_split(entry->value, ':');
		else if (!ft_strncmp(entry->name, "PWD", ft_strlen(entry->name)))
			data->pwd = entry->value;
		i++;
		entry = vector_get(data->environment, i);
	}
}
