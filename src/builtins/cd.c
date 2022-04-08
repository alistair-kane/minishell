/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:22:37 by alkane            #+#    #+#             */
/*   Updated: 2022/04/08 20:29:11 by alkane           ###   ########.fr       */
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

static char	*check_paths(t_data *data, char *end)
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
			return(temp);
	}
	// !!!!! other error
	return (NULL);
}

static char* remove_dup_slash(char *path)
{
	char	temp[PATH_MAX];
	char	*ret;
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
	ret = ft_calloc(j + 1, sizeof(char));
	ft_strlcpy(ret, temp, j);
	return (ret);
}

static char	*remove_dotslash(char *path)
{
	char	temp[PATH_MAX];
	char	*ret;
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
	ret = ft_calloc(j + 1, sizeof(char));
	ft_strlcpy(ret, temp, j);
	return (ret);
}

static char	*handle_dotdot(char *path)
{
	// if there is a char > than 46 (46 is .) update PRECEDING_START
	// if found, look for a / , if found increment PRECEDING
	// check for dot dot ..
	//		if found remove text from PRECEDING_START and decrement PRECEDING
	// int	pre;
	int	pre_start;
	int	len;
	int	i;
	
	len = ft_strlen(path);
	i = 0;
	while (i <= len)
	{
		if (path[i] > '.')
		{
			pre_start = i;
			// pre += 1;
			while (path[i])
			{
				if (path[i++] == '/')
				{
					// pre += 1;
					break;
				}
			}
		}
		if (!ft_strncmp(&path[i], "..", 2))
		{
			// start of cut = pre start
			// i + 2
			
			// home/ test/.. /more/stillmore
			// 		i		j
			ft_memmove(path, &path[pre_start], (len - (i - pre_start)));
			printf("Path after cut: %s", path);
		}
		i++;
	}
	return (path);
}

static void	parse_cur_path(char *path)
{


	path = remove_dup_slash(path);
	printf("no double slash: %s\n", path);
	
	path = remove_dotslash(path);
	printf("no ./'s: %s\n", path);
	
	path = handle_dotdot(path);
	printf("after .. handle: %s\n", path);
	
	return;
}

// static char	*chop_path(t_data *data)
// {
// 	char	*last_dir;
// 	size_t	len;
// 	char	*ret;

// 	last_dir = ft_strrchr(data->pwd, '/');
// 	ret = NULL;
// 	if (last_dir)
// 	{
// 		len = (size_t)(last_dir - data->pwd);
// 		ret = ft_calloc(len + 1, sizeof(char));
// 		ft_memcpy(ret, data->pwd, len);
// 	}
// 	return(ret);
// }

int	builtin_cd(t_data *data, char **dir)
{
	char	*cur_path;
	
	if (!data)
		return (1); // !!!!!
	cur_path = NULL;
	
	// condition met when only "cd" is input -> change to home directory
	// if home unset, keep current directory
	if (!dir[1])
		cur_path = get_home_dir(data);


	// absolute path 
	else if (dir[1][0] == '/')
	{
		cur_path = dir[1];
		parse_cur_path(dir[1]);
	}

	// step 5 checking CDPATH
	else if (dir[1])
		cur_path = check_paths(data, dir[1]);
	
	// printf("cur path after 5%s\n", cur_path);
	// step 7 adding slash (does not check if / already in pwd)
	if (!cur_path)
		cur_path = ft_strjoin(data->pwd, ft_strjoin("/", dir[1]));
	
	if (cur_path[0] != '/')
		cur_path = ft_strjoin(data->pwd, ft_strjoin("/", dir[1]));

	// printf("cur_path b4 8: %s\n", cur_path);
	
	// step 8
	// printf("Current path: %s\n", cur_path);
	// on success zero is returned
	if (!chdir(cur_path))
		data->pwd = cur_path;
	else
		printf("no such file or directory\n");
	// chdir and update pwd !!!!!
	return (1);
}

/** Starting with the first pathname in the <colon>-separated
    pathnames of CDPATH (see the ENVIRONMENT VARIABLES section)
           
	if the pathname is non-null, 
	
	test if the concatenation of that pathname, 
	
	(+ a <slash> character if that pathname did not end with a <slash> character)
	, and the directory operand names a directory. 
		
	If the pathname is null, test if the concatenation of dot, a <slash> character, 
	and the operand names a directory. In either case, if the resulting string
    names an existing directory, set curpath to that string and
    proceed to step 7. 

Otherwise, repeat this step with the next
pathname in CDPATH until all pathnames have been tested.

For all path names inside CDPATH
	check if null
	if not null, add '/' to the path if it does not end with one
	add together the path with / at end and input, check if its a path
	
if the pathname is null test if ./input is a directory

if at any point a directory is found set it to the current path and go forward

//|| dir[1][0] == '.' || (ft_strncmp(dir[1], "..", 2) == 0))
**/