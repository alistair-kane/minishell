#include "../../minishell.h"

static char	*get_home_dir(t_data *data)
{
	size_t			i;
	t_environment	*temp;

	i = -1;
	while (++i < data->environment->total)
	{
		temp = vector_get(data->environment, i);
		if (!ft_strncmp(temp->name, "HOME", 4))
			return (temp->value);
	}
	return (NULL);
}

static char	*check_paths(t_data *data, char *end, char *cur_path)
{
	int		i;
	char	*temp;

	i = -1;
	while (data->path[++i])
	{
		temp = ft_calloc(PATH_MAX, sizeof(char));
		ft_strlcpy(temp, data->path[i], ft_strlen(data->path[i]));
		if (temp[ft_strlen(temp) - 1] != '/')
			ft_strlcat(temp, "/", ft_strlen(temp) + 1);
		ft_strlcat(temp, end, ft_strlen(temp) + ft_strlen(end));
		if (!chdir(temp))
			ft_strlcpy(cur_path, temp, ft_strlen(temp));
		free(temp);
	}
	return (cur_path);
}

static void	add_pwd_parse(t_data *data, char **dir, char *cur_path)
{
	int	temp_len;

	temp_len = ft_strlcpy(cur_path, data->pwd, ft_strlen(data->pwd) + 1);
	temp_len = ft_strlcat(cur_path, "/", temp_len + 2);
	ft_strlcat(cur_path, dir[1], temp_len + ft_strlen(dir[1]) + 1);
	parse_cur_path(cur_path);
}

static int	test_chdir(t_data *data, char *cur_path)
{
	int				index;
	t_environment	*entry;
	t_environment	new;

	if (chdir(cur_path) == 0)
	{
		ft_strlcpy(data->pwd, cur_path, ft_strlen(cur_path) + 1);
		index = get_entry_index(data->environment, "PWD");
		if (index >= 0)
		{
			entry = vector_get(data->environment, index);
			free(entry->value);
			entry->value = malloc(ft_strlen(data->pwd) + 1);
			ft_strlcpy(entry->value, data->pwd, ft_strlen(data->pwd) + 1);
		}
		else
		{
			new.name = ft_strdup("PWD");
			new.value = ft_strdup(data->pwd);
			new.initial_index = get_new_initial_index(data->environment);
			vector_add(data->environment, &new);
		}
	}
	else
		printf("No such file or directory\n");
	free(cur_path);
	return (2);
}

int	builtin_cd(t_data *data, char **args)
{
	char	*cur_path;

	if (data->args_len > 1)
	{
		printf("cd: too many arguments\n");
		return (data->args_len);
	}
	cur_path = ft_calloc(PATH_MAX, sizeof(char));
	if (!args[1])
		ft_strlcpy(cur_path, get_home_dir(data), PATH_MAX);
	else if (args[1][0] == '/')
	{
		ft_strlcpy(cur_path, args[1], ft_strlen(args[1]) + 1);
		parse_cur_path(cur_path);
	}
	else if (args[1][0] == '.' || !ft_strcmp(args[1], ".."))
		add_pwd_parse(data, args, cur_path);
	else if (args[1])
	{
		cur_path = check_paths(data, args[1], cur_path);
		add_pwd_parse(data, args, cur_path);
	}
	return (test_chdir(data, cur_path));
}
