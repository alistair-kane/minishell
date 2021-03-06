/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:39:40 by alkane            #+#    #+#             */
/*   Updated: 2022/05/02 14:39:41 by alkane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_valid_symbol(char **args, int i, int symbol);

int	check_argument_logic(char **args)
{
	int	i;
	int	symbol;
	int	error;

	if (args[0][0] == '\0')
		return (1);
	error = 0;
	i = 0;
	while (args[i] != NULL)
	{
		symbol = is_reserved_symbol(args[i]);
		if (symbol < 0)
			error = 1;
		else if (symbol > 0)
			error = handle_valid_symbol(args, i, symbol);
		if (error != 0)
		{
			printf("syntax error near unexpected token '%s'\n", args[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	handle_valid_symbol(char **args, int i, int symbol)
{
	int	error;

	error = 0;
	if (args[i + 1] == NULL)
	{
		error = 1;
	}
	else if (is_reserved_symbol(args[i + 1]) > 0)
	{
		error = 1;
	}
	if (symbol == RESERVED_SYMBOL_PIPE)
	{
		if (i == 0 || is_reserved_symbol(args[i - 1]) > 0)
			error = 1;
	}
	return (error);
}
