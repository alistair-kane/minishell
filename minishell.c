/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:19:48 by alkane            #+#    #+#             */
/*   Updated: 2022/04/02 17:29:05 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

static t_data	*data_init(void);
static void		data_cleanup(t_data *data);

int	main(void)
{
	char	*buf;
	t_data	*data;

	data = data_init();
	if (data == NULL)
		return (-1);
	buf = readline(PROMPT);
	while (buf != NULL)
	{
		vector_add(data->history, buf);
		buf = readline(PROMPT);
	}
	data_cleanup(data);
	return (0);
}

static t_data	*data_init(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->history = vector_init(100, 100, 0);
	if (data->history == NULL)
	{
		data_cleanup(data);
		return (NULL);
	}
	return (data);
}

static void	data_cleanup(t_data *data)
{
	if (data == NULL)
		return ;
	vector_cleanup(data->history);
	free(data);
}
