/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 19:55:24 by alkane            #+#    #+#             */
/*   Updated: 2021/11/27 22:06:56 by alkane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	char			*sp1;
	char			*sp2;
	unsigned int	n_len;
	unsigned int	i;

	sp1 = (char *)s1;
	sp2 = (char *)s2;
	n_len = ft_strlen(s2);
	i = 0;
	if (n_len == 0)
		return (sp1);
	while (sp1[i] && (n_len + i <= len))
	{
		if (ft_strncmp(sp1 + i, sp2, n_len) == 0)
			return (sp1 + i);
		i++;
	}
	return (NULL);
}
