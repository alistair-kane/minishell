/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 18:39:57 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/04/30 18:41:47 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnum(char *input)
{
	while (*input != '\0')
	{
		if (ft_isdigit(*input) == 0)
			return (0);
		input++;
	}
	return (1);
}
