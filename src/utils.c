// !!!!!

#include "../minishell.h"

int	is_reserved_symbol(char *argument)
{
	if (ft_strncmp("<<", argument, 2) == 0)
		return (1);
	if (ft_strncmp(">>", argument, 2) == 0)
		return (1);
	if (argument[0] == '|')
		return (1);
	if (argument[0] == '<')
		return (1);
	if (argument[0] == '>')
		return (1);
	return (0);
}

int	get_name_length(char *entry)
{
	int	length;

	length = 0;
	while (*entry != '\0')
	{
		if (*entry == '=')
			break ;
		length++;
		entry++;
	}
	return (length);
}

int	get_name_length_whitespace(char *entry)
{
	int	length;

	length = 0;
	while (*entry != '\0')
	{
		if (is_whitespace(*entry) || *entry == '\'' || *entry == '\"')
			break ;
		length++;
		entry++;
	}
	return (length);
}