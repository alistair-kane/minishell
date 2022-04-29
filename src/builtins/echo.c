/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:27:44 by alkane            #+#    #+#             */
/*   Updated: 2022/04/29 15:28:48 by alkane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// should return int of "-n consumed and set n_flag"

static int	flag_handler(char **buf, int *n_flag)
{
	int	i;
	int j;

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

// should return int of "args consumed"
// maybe passing data to this function is not needed?

int	builtin_echo(t_data *data, char **args)
{
	int	i;
	int	j;
	int	n_flag;

	n_flag = 0;
	if (!data)
		return (0);
		
	// flag handler should parse through all -n -nnnn -n variations
	// gives back next segment to be output position
	i = flag_handler(args, &n_flag);
	// checking for ending conditions, current goes through all segments
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			// too late to fix the space problem with double env $ variable (changed split.c)
			if (args[i][j] == '\\')
			{
				if (args[i][j + 1] == 'a' || args[i][j + 1] == 'b' \
				|| args[i][j + 1] == 'e' || args[i][j + 1] == 'f' \
				|| args[i][j + 1] == 'n' || args[i][j + 1] == 'r' \
				|| args[i][j + 1] == 't' || args[i][j + 1] == 'v' \
				|| args[i][j + 1] == '\\' || args[i][j + 1] == '\'' \
				|| args[i][j + 1] == '"' || args[i][j + 1] == '?')
					j++;
			}
			ft_putchar_fd(args[i][j], 1);
			j++;
		}
		if (args[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	// if the -n flag is not active, putstr newline
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	// returns i after each segmentation is consumed
	return (i);
}
