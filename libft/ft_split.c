/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:48:34 by alkane            #+#    #+#             */
/*   Updated: 2021/12/08 16:13:41 by alkane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	seg_count(char const *s, char c)
{
	unsigned int	cnt;
	unsigned int	i;

	cnt = 0;
	i = 1;
	if (s == 0 || s[0] == 0 || s == NULL)
		return (0);
	if (s[0] != c)
		cnt++;
	while (s[i])
	{
		if (s[i] != c && (s[i - 1] == c))
			cnt++;
		i++;
	}
	return (cnt);
}

static char	**mem_check(char **ch_splits)
{
	unsigned int	i;

	i = 0;
	if (ch_splits == 0)
		return (0);
	if (!ch_splits)
	{
		while (ch_splits[i])
		{
			free(ch_splits[i]);
			i++;
		}
		free(ch_splits);
		return (0);
	}
	return (ch_splits);
}

static char	*next_start(char *sp, char c)
{
	while ((*sp == c) && *sp)
		sp++;
	return (sp);
}

static int	next_len(char *s, char c)
{
	unsigned int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**ch_splits;
	int		i;
	int		j;
	int		word_len;
	char	*sp;

	sp = (char *)s;
	ch_splits = ft_calloc(seg_count(s, c) + 1, sizeof(char *));
	if (!mem_check(ch_splits) || !s || !ch_splits)
		return (0);
	i = -1;
	while (++i < seg_count(s, c))
	{
		if (i > 0)
			sp += word_len;
		sp = next_start(sp, c);
		word_len = next_len(sp, c);
		ch_splits[i] = ft_calloc((word_len) + 1, sizeof(char));
		mem_check(ch_splits);
		j = -1;
		while (++j < word_len)
			ch_splits[i][j] = sp[j];
	}
	ch_splits[i] = NULL;
	return (ch_splits);
}
