/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 21:04:27 by alkane            #+#    #+#             */
/*   Updated: 2021/12/08 16:13:56 by alkane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*res_string;

	if (!s || !f)
		return (0);
	i = 0;
	res_string = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!res_string || !s)
		return (NULL);
	while (s[i])
	{
		res_string[i] = (*f)(i, s[i]);
		i++;
	}
	return (res_string);
}
