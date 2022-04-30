/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_trim_end.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:48:51 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/04/30 17:42:04 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	str_trim_end(char *line)
{
	int	count;

	if (line == NULL)
		return ;
	if (*line == '\0')
		return ;
	count = 0;
	while (*line != '\0')
	{
		count++;
		line++;
	}
	line--;
	while (count > 0 && is_whitespace(*line) == 1)
	{
		*line = '\0';
		line--;
		count--;
	}
}
