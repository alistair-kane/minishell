// !!!!!

#include "../minishell.h"

// if a reserved symbol is found, a positive value is returned;
// the functions also check for invalid inputs like "<<<" or "||"
int	is_reserved_symbol(char *argument)
{
	if (ft_strcmp("|", argument) == 0)
		return (RESERVED_SYMBOL_PIPE);
	if (ft_strcmp("<", argument) == 0)
		return (RESERVED_SYMBOL_REDIRECT_INPUT);
	if (ft_strcmp(">", argument) == 0)
		return (RESERVED_SYMBOL_REDIRECT_OUTPUT);
	if (ft_strcmp("<<", argument) == 0)
		return (RESERVED_SYMBOL_DELIMITER);
	if (ft_strcmp(">>", argument) == 0)
		return (RESERVED_SYMBOL_APPEND_OUTPUT);
	if (argument[1] == '|' || argument[1] == '<' || argument[1] == '>')
		return (-1);
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
		if (is_whitespace(*entry) || *entry == '\'' || *entry == '\"' || *entry == '$')
			break ;
		length++;
		entry++;
	}
	return (length);
}