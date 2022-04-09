/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alistair <alistair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:22:37 by alkane            #+#    #+#             */
/*   Updated: 2022/04/09 02:47:38 by alistair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// should return int of "args consumed"

// cd for example consumes itself = return 1
// cd modifiers 'current directory' char* each time it modifies the current dir
// 		current directory var initialized as home directory (from path vector)

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
		temp = data->path[i];
		if (temp[ft_strlen(temp) - 1] != '/') // !!!!! need to support \ ?
			temp = ft_strjoin(temp, "/");
		temp = ft_strjoin(temp, end);
		// test with munkilib
		if (!chdir(temp))
			ft_strlcpy(cur_path, temp, ft_strlen(temp));
	}
	free(temp);
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
	char	temp[PATH_MAX];
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (path[i])
	{
		if (path[i] == '/' && path[i + 1] == '.' && path[i + 2] != '.')
			i += 1;
		else
			temp[j++] = path[i];
		i++;
	}
	ft_strlcpy(path, temp, j + 1);
	return (path);
}

/**
	if there is a char > than 46 (46 is .) update pre_start
	check for dot dot ..
	if found remove text from pre_start
**/

// norminette function

static size_t	iterate_path(char *path, size_t *i)
{
	size_t	j;
			
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
	size_t	pre_start;
	size_t	i;
	size_t	j;
	size_t	dynlen;

	dynlen = ft_strlen(path);
	i = -1;
	while (++i <= ft_strlen(path))
	{
		if (path[i] > '.')
		{
			pre_start = i;
			j = iterate_path(path, &i);
		}
		if (!ft_strncmp(&path[i], "..", 2))
		{
			dynlen -= j + 3;
			ft_memmove(&path[pre_start - 1], &path[i + 2], dynlen);
			i = -1;
		}
	}
	path[dynlen] = '\0';
	return (path);
}

static void	parse_cur_path(char *path, char *cur_path)
{
	cur_path = path;
	
	cur_path = remove_dup_slash(path);
	// printf("no double slash: %s\n\n", path);
	
	cur_path = remove_dotslash(cur_path);
	// printf("no ./'s: %s\n\n", cur_path);
	
	cur_path = handle_dotdot(cur_path);
	// printf("after .. handle: %s\n\n", cur_path);
	return;
}

static	char *path_lower(char *path)
{
	char	*ret;
	int		i;

	ret = ft_calloc(ft_strlen(path) + 1, sizeof(char));
	i = -1;
	while (path[++i])
		ret[i] = tolower(path[i]);
	return (ret);
}

// !!!!! needs norming

int	builtin_cd(t_data *data, char **dir)
{
	char	*cur_path;
	char	*temp;
	int		temp_len;

	if (!data)
		builtin_exit(1);
	cur_path = ft_calloc(PATH_MAX, sizeof(char));
	// if home unset, keep current directory? !!!!!
	if (!dir[1])
		cur_path = get_home_dir(data);
	// absolute path 
	else if (dir[1][0] == '/')
		parse_cur_path(dir[1], cur_path);
	// dot / dotdot path start
	else if (dir[1][0] == '.' || !ft_strncmp(dir[1], "..", 2))
	{
		temp_len = ft_strlcpy(cur_path, data->pwd, ft_strlen(data->pwd) + 1);
		temp_len = ft_strlcat(cur_path, "/", temp_len + 2);
		ft_strlcat(cur_path, dir[1], temp_len + ft_strlen(dir[1]) + 1);
		parse_cur_path(cur_path, cur_path);
	}
	// step 5 checking CDPATH
	else if (dir[1])
	{
		cur_path = check_paths(data, dir[1], cur_path);
		if (*cur_path == '\0')
		{
			temp_len = ft_strlcpy(cur_path, data->pwd, ft_strlen(data->pwd) + 1);
			temp_len = ft_strlcat(cur_path, "/", temp_len + 2);
			ft_strlcat(cur_path, dir[1], temp_len + ft_strlen(dir[1]) + 1);
		}
		parse_cur_path(cur_path, cur_path);
	}
	temp = path_lower(cur_path);
	if (!chdir(temp))
		ft_strlcpy(data->pwd, cur_path, ft_strlen(cur_path) + 1);
	else
		printf("no such file or directory\n");
	free(temp);
	free(cur_path);
	return (1);
}