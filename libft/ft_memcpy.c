/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 22:08:01 by alkane            #+#    #+#             */
/*   Updated: 2021/12/08 01:18:01 by alkane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dp;
	unsigned const char	*sp;

	if (dest || src)
	{
		i = 0;
		dp = dest;
		sp = src;
		while (i < n)
		{
			*dp++ = *sp++;
			i++;
		}
		return (dest);
	}
	return (0);
}
