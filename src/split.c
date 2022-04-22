// !!!!!

#include "../minishell.h"

static int	count_arguments(char *line);
static char	*goto_next_pos(char *line);
static void	skip_whitespaces(char **line);
static int	handle_reserved_symbols(char **line);

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
	int		count;

	str_trim_end(line);
	// skip_whitespaces(line); ? !!!!!
	count = count_arguments(line);
	array = ft_calloc(count + 1, sizeof(void *));
	if (array == NULL)
		exit(1);
	i = 0;
	last_pos = line;
	pos = goto_next_pos(line);
	while (pos != NULL)
	{
		array[i] = malloc((pos - last_pos) + 1);
		if (array[i] == NULL)
			exit(1);
		ft_strlcpy(array[i], last_pos, (pos - last_pos) + 1);
		skip_whitespaces(&pos);
		i++;
		last_pos = pos;
		pos = goto_next_pos(pos);
	}
	array[i] = malloc(ft_strlen(last_pos) + 1);
	if (array[i] == NULL)
		exit(1);
	ft_strlcpy(array[i], last_pos, ft_strlen(last_pos) + 1);
	array[i + 1] = NULL;
	data->args_len = i;
	return (array);
}

static int	count_arguments(char *line)
{
	int		count;

	count = 1;
	line = goto_next_pos(line);
	while (line != NULL)
	{
		count++;
		skip_whitespaces(&line);
		line = goto_next_pos(line);
	}
	return (count);
}

// this will skip multiple whitespace-chars at the start of the string
static char	*goto_next_pos(char *line)
{
	int	double_quotes_open;
	int	single_quotes_open;

	double_quotes_open = 0;
	single_quotes_open = 0;
	if (handle_reserved_symbols(&line) != 0)
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
			handle_quotes(*line, &double_quotes_open, &single_quotes_open);
		if (double_quotes_open == 0 && single_quotes_open == 0)
		{
			if (*line == '<' || *line == '>' || *line == '|' || *line == '$')
				return (line);
			if (is_whitespace(*line) == 1)
				return (line);
		}
		if (*line != '\0')
			line++;
	}
	return (NULL);
}

static void	skip_whitespaces(char **line)
{
	while (is_whitespace(**line) == 1)
		(*line)++;
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

static int	handle_reserved_symbols(char **line)
{
	if (**line == '$')
	{
		(*line)++;
		while (is_whitespace(**line) == 0 && **line != '<' && **line != '>'
			&& **line != '|' && **line != '$' && **line != '\0')
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
