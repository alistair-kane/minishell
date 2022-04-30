// !!!!!

#include "../minishell.h"

static void	init_environment(t_data *data);
static void	init_env_structs(t_data *data);
static void	init_paths(t_data *data);
static void	init_signals(int sig);

t_data	*data_init(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
		return (NULL);
	init_environment(data);
	vector_custom_cleanup(data->environment, cleanup_environment);
	init_paths(data);
	init_signals(SIGINT);
	init_signals(SIGQUIT);
	data->exec = vector_init(10, 10, 0);
	if (data->exec == NULL)
		exit(1);
	vector_custom_cleanup(data->exec, cleanup_exec);
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
		ft_strlcpy(entry.name, environ[i], length_name + 1);
		length_value = ft_strlen(&environ[i][length_name + 1]);
		entry.value = malloc(length_value + 1);
		ft_strlcpy(entry.value, &environ[i][length_name + 1], length_value + 1);
		entry.initial_index = i;
		vector_add(data->environment, &entry);
		add_to_envp(data, entry.name, entry.value);
		i++;
	}
	sort_all_entries(data->environment);
}

static void	init_env_structs(t_data *data)
{
	data->environment = vector_init(100, 100, sizeof(t_environment));
	if (data->environment == NULL)
		exit(1);
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
			ft_strlcpy(data->pwd, entry->value, ft_strlen(entry->value) + 1);
		i++;
		entry = vector_get(data->environment, i);
	}
}

static void	init_signals(int sig)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, sig);
	sa.sa_handler = &signal_handler;
	if (sigaction(sig, &sa, NULL) < 0)
	{
		printf("ERROR! SIGINT\n");
		return ;
	}
}
