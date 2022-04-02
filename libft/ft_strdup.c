/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 22:57:38 by alkane            #+#    #+#             */
/*   Updated: 2021/11/27 23:14:11 by alkane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char			*p;
	unsigned int	s_size;

	s_size = ft_strlen(s) + 1;
	p = malloc(s_size);
	if (!p)
		return (NULL);
	ft_strlcpy(p, s, s_size);
	return (p);
}
