/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:40:07 by alkane            #+#    #+#             */
/*   Updated: 2022/05/02 14:40:08 by alkane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*goto_next_pos(char *line);
static char	*handle_end_of_arg(char *line, int double_quotes,
				int single_quotes);
static void	skip_whitespaces(char **line);

/*
returns an array of strings - splits the line when finding a whitespace-char, 
that's not part of any string (surrounded by ' or " quotes)
*/
char	**ms_split(t_data *data, char *line)
{
	char	**array;
	char	*last_pos;
	char	*pos;
	int		i;

	str_trim_end(line);
	skip_whitespaces(&line);
	array = ft_calloc(1024, sizeof(void *));
	i = 0;
	last_pos = line;
	pos = goto_next_pos(line);
	while (pos != NULL)
	{
		array[i] = malloc((pos - last_pos) + 1);
		ft_strlcpy(array[i], last_pos, (pos - last_pos) + 1);
		skip_whitespaces(&pos);
		i++;
		last_pos = pos;
		pos = goto_next_pos(pos);
	}
	array[i] = ft_strdup(last_pos);
	array[i + 1] = NULL;
	data->args_len = i;
	return (array);
}

// this will skip multiple whitespace-chars at the start of the string
static char	*goto_next_pos(char *line)
{
	int	double_quotes;
	int	single_quotes;

	double_quotes = 0;
	single_quotes = 0;
	if (parse_reserved_symbols(&line) != 0)
	{
		if (ft_strlen(line) != 0)
			return (line);
		else
			return (NULL);
	}
	while (*line != '\0')
	{
		if (*line == '\\')
			line += 2;
		if (*line == '\'' || *line == '"')
			handle_quotes(*line, &double_quotes, &single_quotes);
		if (handle_end_of_arg(line, double_quotes, single_quotes) != NULL)
			return (line);
		if (*line != '\0')
			line++;
	}
	return (NULL);
}

static char	*handle_end_of_arg(char *line, int double_quotes, int single_quotes)
{
	if (double_quotes == 0 && single_quotes == 0)
	{
		if (*line == '<' || *line == '>' || *line == '|' || *line == '$')
			return (line);
		if (is_whitespace(*line) == 1)
			return (line);
	}
	return (NULL);
}

static void	skip_whitespaces(char **line)
{
	while (is_whitespace(**line) == 1)
		(*line)++;
}
