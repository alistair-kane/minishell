/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alistair <alistair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:22:37 by alkane            #+#    #+#             */
/*   Updated: 2022/04/07 01:34:16 by alistair         ###   ########.fr       */
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

static int	check_paths(t_data *data, char *end)
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
		// printf("Path: %s\n", temp);
		// dir = opendir(temp);
		if (!chdir(temp))
			printf("Found a dir: %s\n", temp);
		free(temp);
	}
	return (0);
}

int	builtin_cd(t_data *data, char **buf)
{
	int		i;
	int		j;
	char	*cur_path;
	
	if (!data)
		return (0);

	i = 1;
	j = 0;
	// condition met when only "cd" is input -> change to home directory
	// if home unset, keep current directory
	if (!buf[i])
	{
		cur_path = get_home_dir(data);
		printf("home dir %s\n", cur_path);
		
		// checking if home unset
		if (!cur_path)
			return(1); // !!!!!
		// update pwd !!!!!
		chdir(cur_path);
		return(1);
	}
	// !!!!! does "\" also need to be supported? How to test
	else if (buf[i][j] == '/')
	{
		printf("Slash found\n");
		cur_path = buf[i];
	}
	else if (buf[i])
	{
		check_paths(data, buf[i]);
	}
	return (1); // !!!!!
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
**/