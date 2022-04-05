/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:19:48 by alkane            #+#    #+#             */
/*   Updated: 2022/04/05 19:39:31 by alkane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

int	main(void)
{
	char	*buf;
	t_data	*data;

	data = data_init();
	if (data == NULL)
		return (-1);
	buf = readline(PROMPT);
	if (ft_strlen(buf))
		add_history(buf);
	while (buf != NULL)
	{
		vector_add(data->history, buf);
		parser(data, buf);
		buf = readline(PROMPT);
		if (ft_strlen(buf))
			add_history(buf);
	}
	data_cleanup(data);
	return (0);
}

