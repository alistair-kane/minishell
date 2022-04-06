/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:27:44 by alkane            #+#    #+#             */
/*   Updated: 2022/04/06 15:33:34 by alkane           ###   ########.fr       */
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

int	builtin_echo(t_data *data, char **buf)
{
	int	i;
	int n_flag;

	n_flag = 0;
	if (!data)
		return (0);
		
	// flag handler should parse through all -n -nnnn -n variations
	// gives back next segment to be output position
	i = flag_handler(buf, &n_flag);
	// checking for ending conditions, current goes through all segments
	while (buf[i] && ft_strncmp(buf[i], "|", 1))
	{
		// if a piping is needed, change of fd here?
		ft_putstr_fd(buf[i++], 1);
		ft_putstr_fd(" ", 1);
	}
	// if the -n flag is not active, putstr newline
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	// returns i after each segmentation is consumed
	return (i);
}