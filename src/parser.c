/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:39:46 by alkane            #+#    #+#             */
/*   Updated: 2022/05/02 14:39:46 by alkane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtin(char **args)
{
	if ((!ft_strcmp("echo", args[0]) || (!ft_strcmp("cd", args[0])) \
		|| (!ft_strcmp("pwd", args[0])) || (!ft_strcmp("export", args[0])) \
		|| (!ft_strcmp("unset", args[0])) || (!ft_strcmp("env", args[0])) \
		|| (!ft_strcmp("exit", args[0]))))
		return (1);
	return (0);
}

void	exec_builtin(t_data *data, char **args)
{
	if (!ft_strcmp("echo", args[0]))
		builtin_echo(data, args);
	else if (!ft_strcmp("cd", args[0]))
		builtin_cd(data, args);
	else if (!ft_strcmp("pwd", args[0]))
		builtin_pwd(data);
	else if (!ft_strcmp("export", args[0]))
		builtin_export(data, args);
	else if (!ft_strcmp("unset", args[0]))
		builtin_unset(data, args);
	else if (!ft_strcmp("env", args[0]))
		builtin_env(data, args);
	else if (!ft_strcmp("exit", args[0]))
		builtin_exit(data, args);
	exit(0);
}

void	parser(t_data *data, char *buf)
{
	char	**args;

	buf = env_expansion(data, buf);
	args = ms_split(data, buf);
	free(buf);
	quote_master(args);
	if (check_argument_logic(args) != 0)
	{
		free_c_vector(args);
		return ;
	}
	prep_exec(data, args);
	exec(data);
	free_c_vector(args);
	vector_clear(data->exec);
}
