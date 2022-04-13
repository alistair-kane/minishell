#include "errno.h"

#include "../../minishell.h"

// should return int of "args consumed"

// cd for example consumes itself = return 1
// cd modifiers pwd char* each time it modifies the current dir
// current directory var initialized as home directory (from path vector)

static int	max(int val1, int val2) // !!!!! could be added to utils if needed elsewhere? 
{
    if (val1 > val2)
		return (val1);
    return (val2);
}

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
		if (temp[ft_strlen(temp) - 1] != '/') // !!!!! need to support \ ?
			ft_strlcat(temp, "/", ft_strlen(temp) + 1);
		ft_strlcat(temp, end, ft_strlen(temp) + ft_strlen(end));
		// test with munkilib
		if (!chdir(temp))
			ft_strlcpy(cur_path, temp, ft_strlen(temp));
		free(temp);
	}
	// !!!!! other error
	return (cur_path);
}

static char	*remove_dup_slash(char *path)
{
	char	temp[PATH_MAX];
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i <= ft_strlen(path))
	{
		if (i == 0)
			temp[j++] = path[i];
		else if (path[i] == '/')
		{
			if (path[i - 1] != '/')
				temp[j++] = path[i];
		}
		else
			temp[j++] = path[i];
		i++;
	}
	ft_strlcpy(path, temp, j);
	return (path);
}

static char	*remove_dotslash(char *path)
{
	char	*temp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	temp = ft_calloc(PATH_MAX, sizeof(char));
	while (path[i])
	{
		if (path[i] == '/' && path[i + 1] == '.' && path[i + 2] != '.')
			i += 1;
		else
			temp[j++] = path[i];
		i++;
	}
	ft_strlcpy(path, temp, j + 1);
	free(temp);
	return (path);
}

static int	iterate_path(char *path, int *i)
{
	int	j;
			
	j = 0;
	while (path[*i])
	{
		if (path[*i] == '/')
			break ;
		(*i)++;
		j++;
	}
	return (j);
}

static char	*handle_dotdot(char *path)
{
	int	pre_start;
	int	i;
	int	j;
	int	dynlen;

	dynlen = ft_strlen(path);
	i = -1;
	while (++i <= (int)ft_strlen(path))
	{
		if (path[i] > '.')
		{
			pre_start = i;
			j = iterate_path(path, &i);
		}
		if (!ft_strncmp(&path[i], "..", 2))
		{
			dynlen -= j + 3;
			ft_memmove(&path[max(0, (pre_start - 1))], &path[i + 2], dynlen);
			i = -1;
		}
	}
	path[dynlen] = '\0';
	if (dynlen < 3 || path == NULL)
		ft_strlcpy(path, "/", 2);
	return (path);
}

static void	parse_cur_path(char *cur_path)
{
	cur_path = remove_dup_slash(cur_path);
	cur_path = remove_dotslash(cur_path);
	cur_path = handle_dotdot(cur_path);
	return ;
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
	if (chdir(cur_path) == 0)
		ft_strlcpy(data->pwd, cur_path, ft_strlen(cur_path) + 1);
	else
		printf("No such file or directory\n");
	free(cur_path);
	// two arguments consumed, therefore returns 2
	return (2);
}

int	builtin_cd(t_data *data, char **dir)
{
	char	*cur_path;

	if (!data)
		builtin_exit(1);
	if (data->args_len > 1)
	{
		printf("cd: too many arguments\n");
		return (data->args_len);
	}
	cur_path = ft_calloc(PATH_MAX, sizeof(char));
	if (!dir[1])
		cur_path = get_home_dir(data);
	else if (dir[1][0] == '/')
	{
		ft_strlcpy(cur_path, dir[1], ft_strlen(dir[1]) + 1);
		parse_cur_path(cur_path);
	}
	else if (dir[1][0] == '.' || !ft_strcmp(dir[1], ".."))
		add_pwd_parse(data, dir, cur_path);
	else if (dir[1])
	{
		cur_path = check_paths(data, dir[1], cur_path);
		add_pwd_parse(data, dir, cur_path);
	}
	return (test_chdir(data, cur_path));
}

// depending on the version of linux, chdir is case sensitive (not accepting capitals) ??

// static	char *path_lower(char *path)
// {
// 	char	*ret;
// 	int		i;

// 	ret = ft_calloc(ft_strlen(path) + 1, sizeof(char));
// 	i = -1;
// 	while (path[++i])
// 		ret[i] = tolower(path[i]);
// 	return (ret);
// }