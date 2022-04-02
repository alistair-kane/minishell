/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_add_rm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:34:47 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/02/18 12:43:54 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"

static void	*vector_resize(t_vector *vector);
static void	copy_data(t_vector *vector, void **new);

void	*vector_add(t_vector *vector, void *data)
{
	char	*buf;

	if (vector->total == vector->capacity)
	{
		if (vector_resize(vector) == NULL)
			return (NULL);
	}
	if (vector->data_size == 0)
	{
		vector->nodes[vector->total] = data;
		vector->total++;
		return (vector->nodes[vector->total - 1]);
	}
	buf = (char *)vector->nodes;
	ft_memcpy(&buf[vector->total * vector->data_size], data,
		vector->data_size);
	vector->total++;
	return (&buf[(vector->total - 1) * vector->data_size]);
}

static void	*vector_resize(t_vector *vector)
{
	size_t	new_capacity;
	void	**new;

	new_capacity = vector->capacity + vector->grow_count;
	if (vector->data_size == 0)
		new = malloc(new_capacity * sizeof(void *));
	else
		new = malloc(new_capacity * vector->data_size);
	if (new == NULL)
		return (NULL);
	copy_data(vector, new);
	free(vector->nodes);
	vector->nodes = new;
	vector->capacity = new_capacity;
	return (vector->nodes);
}

static void	copy_data(t_vector *vector, void **new)
{
	size_t	i;

	if (vector->data_size == 0)
	{
		i = 0;
		while (i < vector->total)
		{
			new[i] = vector->nodes[i];
			i++;
		}
		return ;
	}
	ft_memcpy(new, vector->nodes, vector->total * vector->data_size);
}

void	vector_delete(t_vector *vector, int index)
{
	char	*buf;
	size_t	i;

	if (index < 0 || index >= (int)vector->total)
		return ;
	if (vector->data_size == 0)
	{
		free(vector->nodes[index]);
		i = index;
		while (i < vector->total - 1)
		{
			vector->nodes[i] = vector->nodes[i + 1];
			i++;
		}
		vector->nodes[i + 1] = NULL;
	}
	else
	{
		buf = (char *)vector->nodes;
		ft_memmove(&buf[index * vector->data_size],
			&buf[(index + 1) * vector->data_size],
			(vector->total - (index + 1)) * vector->data_size);
	}
	vector->total--;
}
