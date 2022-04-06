// !!!!!

#include <stdio.h>

#include <stdlib.h>
#include "../minishell.h"

static void	init_environment(t_data *data);

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
	return (data);
}

static void	init_environment(t_data *data)
{
	extern char		**environ;
	int				i;
	int				length_name;
	int				length_value;
	t_environment	entry;

	data->environment = vector_init(100, 100, sizeof(t_environment));
	if (data->environment == NULL)
		return ; // !!!!!
	i = 0;
	while (environ[i] != NULL)
	{
		length_name = get_name_length(environ[i]);
		entry.name = malloc(length_name + 1);
		if (entry.name == NULL)
			return ; // !!!!!
		ft_strlcpy(entry.name, environ[i], length_name + 1);
		length_value = ft_strlen(&environ[i][length_name + 1]);
		entry.value = malloc(length_value + 1);
		if (entry.value == NULL)
			return ; // !!!!!
		ft_strlcpy(entry.value, &environ[i][length_name + 1], length_value + 1);
		vector_add(data->environment, &entry);
		i++;
	}
}

int	get_name_length(char *entry)
{
	int	length;

	length = 0;
	while (*entry != '\0')
	{
		if (*entry == '=')
			break ;
		length++;
		entry++;
	}
	return (length);
}

void	data_cleanup(t_data *data)
{
	if (data == NULL)
		return ;
	// !!!!! cleanup mallocs of the environment structs -> custom_cleanup
	vector_cleanup(data->environment);
	vector_cleanup(data->history);
	free(data);
}
