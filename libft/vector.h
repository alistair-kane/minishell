/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:53:07 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/02/18 12:43:02 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stdlib.h>

typedef struct s_vector
{
	size_t	capacity;
	size_t	total;
	size_t	grow_count;
	size_t	data_size;
	void	**nodes;
}				t_vector;

t_vector	*vector_init(size_t capacity, size_t grow_count, size_t size);
void		vector_cleanup(t_vector *vector);
void		vector_clear(t_vector *vector);
void		*vector_add(t_vector *vector, void *data);
void		*vector_get(t_vector *vector, int index);
void		vector_delete(t_vector *vector, int index);

#endif
