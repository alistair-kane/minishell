/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:14:47 by alkane            #+#    #+#             */
/*   Updated: 2022/04/05 18:14:27 by alkane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "libft/vector.h"

# include <stdio.h>

# define PROMPT "$ "

typedef struct s_data
{
	t_vector	*history;
}				t_data;

t_data	*data_init(void);
void	data_cleanup(t_data *data);

void	parser(t_data *data, char *buf);

int	builtin_echo(t_data *data, char **buf);

#endif
