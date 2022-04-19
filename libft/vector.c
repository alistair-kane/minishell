/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:02:24 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/04/19 12:07:12 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "vector.h"

t_vector	*vector_init(size_t capacity, size_t grow_count, size_t size)
{
	t_vector	*vec;

	vec = ft_calloc(1, sizeof(t_vector));
	if (vec == NULL)
		return (NULL);
	vec->capacity = capacity;
	vec->grow_count = grow_count;
	vec->data_size = size;
	if (size == 0)
		vec->nodes = malloc(capacity * sizeof(void *));
	else
		vec->nodes = malloc(capacity * size);
	if (vec->nodes == NULL)
	{
		free(vec);
		return (NULL);
	}
	return (vec);
}

void	vector_cleanup(t_vector *vector)
{
	size_t	i;

	if (vector == NULL)
		return ;
	i = 0;
	while (i < vector->total)
	{
		if (vector->cleanup_cb != NULL)
			vector->cleanup_cb(vector_get(vector, i));
		if (vector->data_size == 0)
			free(vector->nodes[i]);
		i++;
	}
	free(vector->nodes);
	free(vector);
}

void	vector_custom_cleanup(t_vector *vector,
			void (*vector_cleanup_cb)(void *data))
{
	vector->cleanup_cb = vector_cleanup_cb;
}

void	vector_clear(t_vector *vector)
{
	size_t	i;

	if (vector == NULL)
		return ;
	i = 0;
	while (i < vector->total)
	{
		if (vector->cleanup_cb != NULL)
			vector->cleanup_cb(vector_get(vector, i));
		if (vector->data_size == 0)
			free(vector->nodes[i]);
		i++;
	}
	vector->total = 0;
}

void	*vector_get(t_vector *vector, int index)
{
	char	*buf;

	if (index < 0 || index >= (int)vector->total)
		return (NULL);
	if (vector->data_size == 0)
		return (vector->nodes[index]);
	buf = (char *)vector->nodes;
	return (&buf[index * vector->data_size]);
}
