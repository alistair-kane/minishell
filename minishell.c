/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:42:16 by alkane            #+#    #+#             */
/*   Updated: 2022/05/02 14:42:17 by alkane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*buf;
	int		ret;
	t_data	*data;

	data = data_init();
	if (data == NULL)
		return (-1);
	while (1)
	{
		buf = readline(PROMPT);
		if (buf == NULL)
		{
			printf("%sexit\n", PROMPT);
			break ;
		}
		if (ft_strlen(buf))
			add_history(buf);
		parser(data, buf);
		if (data->exit != 0)
			break ;
	}
	ret = data->exit_value;
	data_cleanup(data);
	return (ret);
}
