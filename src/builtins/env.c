/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:40:47 by alkane            #+#    #+#             */
/*   Updated: 2022/05/02 14:40:54 by alkane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_environment	*get_next_entry(t_vector *env, int prev_index);

int	builtin_env(t_data *data, char **args)
{
	int				i;
	int				initial_index;
	t_environment	*entry;

	if (args[1] != NULL)
	{
		printf("%s: No such file or directory\n", args[1]);
		return (0);
	}
	initial_index = -1;
	i = 0;
	while (i < (int)data->environment->total)
	{
		entry = get_next_entry(data->environment, initial_index);
		if (ft_strlen(entry->value) != 0)
			printf ("%s=%s\n", entry->name, entry->value);
		initial_index = entry->initial_index;
		i++;
	}
	return (1);
}

static t_environment	*get_next_entry(t_vector *env, int prev_index)
{
	int				i;
	int				check;
	t_environment	*entry;
	t_environment	*ret;

	check = INT_MAX;
	i = 0;
	entry = vector_get(env, i);
	while (entry != NULL)
	{
		if (entry->initial_index > prev_index)
		{
			if (entry->initial_index < check)
			{
				check = entry->initial_index;
				ret = entry;
			}
		}
		i++;
		entry = vector_get(env, i);
	}
	return (ret);
}
