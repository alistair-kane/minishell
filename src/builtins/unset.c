/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:40:27 by alkane            #+#    #+#             */
/*   Updated: 2022/05/02 14:40:28 by alkane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	empty_path(t_data *data);
static void	rebuild_envp(t_data *data);

int	builtin_unset(t_data *data, char **args)
{
	int				i;
	int				j;
	t_environment	*entry;

	i = 1;
	while (args[i] != NULL)
	{
		j = 0;
		entry = vector_get(data->environment, j);
		while (entry != NULL)
		{
			if (ft_strcmp(args[i], entry->name) == 0)
			{
				vector_delete(data->environment, j);
				if (ft_strcmp("PATH", args[i]) == 0)
					empty_path(data);
			}
			j++;
			entry = vector_get(data->environment, j);
		}
		i++;
	}
	rebuild_envp(data);
	return (i);
}

static void	empty_path(t_data *data)
{
	free_path(data);
	data->path = NULL;
}

static void	rebuild_envp(t_data *data)
{
	int				i;
	t_environment	*entry;

	free_c_vector(data->envp);
	data->envp = NULL;
	i = 0;
	entry = vector_get(data->environment, i);
	while (entry != NULL)
	{
		add_to_envp(data, entry->name, entry->value);
		i++;
		entry = vector_get(data->environment, i);
	}
}
