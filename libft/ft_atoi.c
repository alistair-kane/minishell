/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 21:01:58 by alkane            #+#    #+#             */
/*   Updated: 2021/12/11 20:28:27 by alkane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_space(char ch)
{
	if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\v' || ch == '\f'
		|| ch == '\r')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	unsigned int	i;
	int				negative_count;
	long			return_value;

	i = 0;
	negative_count = 0;
	return_value = 0;
	while ((is_space(nptr[i]) || nptr[i] == '-' || nptr[i] == '+'))
	{
		if ((nptr[i] == '-') || (nptr[i] == '+'))
		{
			if (nptr[i++] == '-')
				negative_count++;
			break ;
		}
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		return_value = return_value * 10 + (nptr[i++] - '0');
	if (negative_count)
		return_value *= -1;
	return (return_value);
}
