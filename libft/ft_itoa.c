/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:54:35 by alkane            #+#    #+#             */
/*   Updated: 2021/12/03 13:37:45 by alkane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	conversion(int n)
{
	long long	converted;

	converted = (long long)n;
	if (n < 0)
		converted *= -1;
	return (converted);
}

char	*ft_itoa(int n)
{
	long long		int_l;
	char			int_array[26];
	char			*int_p;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	int_l = conversion(n);
	while (int_l)
	{
		int_array[i++] = (char)(int_l % 10 + '0');
		int_l /= 10;
	}
	if (n < 0)
		int_array[i++] = '-';
	if (n == 0)
		int_array[i++] = '0';
	int_p = ft_calloc((i + 1), sizeof (char));
	if (!int_p)
		return (0);
	j = 0;
	while (i--)
		int_p[j++] = int_array[i];
	return (int_p);
}
