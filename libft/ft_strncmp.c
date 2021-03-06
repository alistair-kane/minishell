/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 02:50:58 by alkane            #+#    #+#             */
/*   Updated: 2022/04/07 15:49:14 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n != 0)
	{
		while (i < n)
		{
			if ((s1[i] != s2[i]) || s1[i] == '\0' || s2[i] == '\0')
				return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
		}
	}
	return (0);
}
