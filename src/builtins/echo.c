/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:27:44 by alkane            #+#    #+#             */
/*   Updated: 2022/04/30 19:26:18 by alkane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	flag_handler(char **buf, int *n_flag)
{
	int	i;
	int	j;

	*n_flag = 0;
	i = 1;
	while (buf[i] && !ft_strncmp(buf[i], "-n", 2))
	{
		j = 2;
		while (buf[i][j])
		{
			if (buf[i][j] != 'n')
				return (i);
			j++;
		}
		*n_flag = 1;
		i++;
	}
	return (i);
}

static void	check_escape_c(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\\')
		{
			if (arg[i + 1] == 'a' || arg[i + 1] == 'b' \
			|| arg[i + 1] == 'e' || arg[i + 1] == 'f' \
			|| arg[i + 1] == 'n' || arg[i + 1] == 'r' \
			|| arg[i + 1] == 't' || arg[i + 1] == 'v' \
			|| arg[i + 1] == '\\' || arg[i + 1] == '\'' \
			|| arg[i + 1] == '"' || arg[i + 1] == '?')
				i++;
		}
		ft_putchar_fd(arg[i], 1);
		i++;
	}
}

int	builtin_echo(t_data *data, char **args)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	if (!data)
		return (0);
	i = flag_handler(args, &n_flag);
	while (args[i])
	{
		check_escape_c(args[i]);
		if (args[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	return (i);
}
