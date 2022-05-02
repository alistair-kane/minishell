/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:40:19 by alkane            #+#    #+#             */
/*   Updated: 2022/05/02 14:40:20 by alkane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_reset(char *arg, int *delp1, int *delp2, int *i)
{
	if (*delp1 != -1 && *delp2 != -1)
	{
		*delp2 -= 1;
		ft_memmove(&arg[*delp1], &arg[*delp1 + 1], ft_strlen(arg) - *delp1);
		ft_memmove(&arg[*delp2], &arg[*delp2 + 1], ft_strlen(arg) - *delp2);
		*delp1 = -1;
		*delp2 = -1;
		*i -= 2;
		return (1);
	}
	return (0);
}

static void	char_cleanup(char *arg)
{
	int	i;
	int	delp[2];
	int	quotes[2];

	ft_bzero(quotes, sizeof(int) * 2);
	delp[0] = -1;
	delp[1] = -1;
	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '\\')
			i += 2;
		if (arg[i] == '\'' || arg[i] == '"')
		{
			if (handle_quotes(arg[i], &quotes[0], &quotes[1]) == 1)
			{
				if (delp[0] == -1)
					delp[0] = i;
				else
					delp[1] = i;
			}
		}
		check_reset(arg, &delp[0], &delp[1], &i);
	}
}

void	quote_master(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		char_cleanup(args[i]);
	}
}

// returns 1, if something changes
int	handle_quotes(char c, int *double_quotes, int *single_quotes)
{
	if (c == '"')
	{
		if (*double_quotes == 1)
			*double_quotes = 0;
		else
		{
			if (*single_quotes == 0)
				*double_quotes = 1;
			else
				return (0);
		}
		return (1);
	}
	if (*single_quotes == 1)
		*single_quotes = 0;
	else
	{
		if (*double_quotes == 0)
			*single_quotes = 1;
		else
			return (0);
	}
	return (1);
}

int	parse_reserved_symbols(char **line)
{
	if (**line == '$')
	{
		(*line)++;
		while (is_whitespace(**line) == 0 && **line != '<' && **line != '>'
			&& **line != '|' && **line != '\0')
			(*line)++;
	}
	else if (**line == '<')
		while (**line == '<')
			(*line)++;
	else if (**line == '>')
		while (**line == '>')
			(*line)++;
	else if (**line == '|')
		while (**line == '|')
			(*line)++;
	else
		return (0);
	return (1);
}
