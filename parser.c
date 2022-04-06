/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:40:06 by alkane            #+#    #+#             */
/*   Updated: 2022/04/06 14:35:57 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// searching path to match
// int	check_binaries(t_data *data, char **arg)
// {
// 	int		i;
// 	char	*temp;
// 	char	*path;

// 	i = -1;
// 	// needs to refactored for t-vector struct!!!!!
// 	while (paths[++i] != NULL)
// 	{
// 		if (i == 0)
// 			//incremented forwartd by 5 to "look" past PATHS start of string
// 			ft_memmove(paths[i], paths[i] + 5, ft_strlen(paths[i] + 5));
// 		temp = ft_strjoin(paths[i], "/");
// 		path = ft_strjoin(temp, arg);
// 		free(temp);
// 		if (!access(path, X_OK))
// 			return (path);
// 		free(path);
// 	}
// 	// only finding the path of the binary, need to decide when its executed later
// 	return (NULL);
// }

int	check_builtin(t_data *data, char **arg)
{
	if (!ft_strncmp("echo", arg[0], ft_strlen(arg[0])))
		return(builtin_echo(data, arg));
	// else if (!ft_strncmp("cd", arg[0], 2))
	// 	return(builtin_cd(data, arg));
	// else if (!ft_strncmp("pwd", arg[0], 3))
	// 	return(builtin_pwd(data));
	// else if (!ft_strncmp("export", arg[0], 3))
	// 	return(builtin_export(data));
	// else if (!ft_strncmp("unset", arg[0], 3))
	// 	return(builtin_unset(data));
	// else if (!ft_strncmp("env", arg[0], 3))
	// 	return(builtin_env(data));
	// else if (!ft_strncmp("exit", arg, 3))
	// 	return(builtin_exit(data));
	return (0);
}

int	parse_args(t_data *data, char **arg)
{
	int	consumed;
	
	// check for pipe and redirects
	
	consumed = check_builtin(data, arg);
	if (!consumed)
		return (consumed);
	
	// consumed = check_binaries(data, arg);
	// if (!consumed)
		return (consumed);
}

void	parser(t_data *data, char *buf)
{
	char	**args;
	int		i;

	// line preprocessing goes here

	// !!!!! split must be replaced
	// new pre-parser should handle all whitespace chars and ___ " ' $ ___ (not splitting inside)
	args = ms_split(buf);
	i = 0;
	while (args[i])
	{
		i += parse_args(data, &args[i]);
		
		// line is here incase parse_args not functioning as intended
		// i++;
	}
	// !!!!! free split (args)
}