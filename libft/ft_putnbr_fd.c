/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:20:14 by alkane            #+#    #+#             */
/*   Updated: 2021/12/03 13:48:11 by alkane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long		int_l;
	char			int_array[26];
	unsigned int	i;

	int_l = (long long)n;
	if (n < 0)
		int_l *= -1;
	i = 0;
	while (int_l)
	{
		int_array[i++] = (char)(int_l % 10 + '0');
		int_l /= 10;
	}
	if (n < 0)
		int_array[i++] = '-';
	if (n == 0)
		int_array[i++] = '0';
	while (i--)
		write(fd, &int_array[i], 1);
}
