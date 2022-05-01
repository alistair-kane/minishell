/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:52:48 by alkane            #+#    #+#             */
/*   Updated: 2022/05/01 16:52:48 by alkane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	parse_cur_path(char *cur_path)
{
	cur_path = remove_dup_slash(cur_path);
	cur_path = remove_dotslash(cur_path);
	cur_path = handle_dotdot(cur_path);
	return ;
}
