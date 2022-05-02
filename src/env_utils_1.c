/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:39:29 by alkane            #+#    #+#             */
/*   Updated: 2022/05/02 14:39:33 by alkane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	swap_entries(t_environment *first, t_environment *second)
{
	char	name[4096];
	char	value[16384];
	int		tmp;

	ft_strlcpy(name, first->name, ft_strlen(first->name) + 1);
	ft_strlcpy(value, first->value, ft_strlen(first->value) + 1);
	free(first->name);
	first->name = ft_strdup(second->name);
	free(first->value);
	first->value = ft_strdup(second->value);
	free(second->name);
	second->name = ft_strdup(name);
	free(second->value);
	second->value = ft_strdup(value);
	tmp = first->initial_index;
	first->initial_index = second->initial_index;
	second->initial_index = tmp;
}

void	sort_all_entries(t_vector *env)
{
	int				i;
	int				j;
	int				swaped;
	t_environment	*entry1;
	t_environment	*entry2;

	i = 0;
	while (i < (int)env->total)
	{
		swaped = 0;
		j = -1;
		while (++j < (int)env->total - 1)
		{
			entry1 = vector_get(env, j);
			entry2 = vector_get(env, j + 1);
			if (ft_strcmp(entry1->name, entry2->name) >= 0)
			{
				swap_entries(entry1, entry2);
				swaped = 1;
			}
		}
		if (swaped == 0)
			break ;
		i++;
	}
}

void	add_to_envp(t_data *data, char *name, char *value)
{
	int	i;

	if (value == NULL)
		return ;
	if (data->envp == NULL)
	{
		data->envp = ft_calloc(1024, sizeof(char *));
		if (data->envp == NULL)
			exit(1);
	}
	i = 0;
	while (data->envp[i] != NULL)
		i++;
	data->envp[i] = malloc(ft_strlen(name) + ft_strlen(value) + 2);
	if (data->envp[i] == NULL)
		exit(1);
	ft_strlcpy(data->envp[i], name, ft_strlen(name) + 1);
	data->envp[i][ft_strlen(name)] = '=';
	ft_strlcpy(&data->envp[i][ft_strlen(name) + 1], value,
		ft_strlen(value) + 1);
}
