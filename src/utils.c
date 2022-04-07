// !!!!!

#include "../minishell.h"

int	is_reserved_symbol(char *argument)
{
	if (argument[0] == '|')
		return (1);
	if (argument[0] == '<')
		return (1);
	if (argument[0] == '>')
		return (1);
	// these will never be hit !!!!!
	/*if (ft_strncmp("<<", argument, 2) == 0)
		return (1);
	if (ft_strncmp(">>", argument, 2) == 0)
		return (1);*/
	return (0);
}
