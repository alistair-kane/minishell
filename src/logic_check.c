// !!!!!

#include "../minishell.h"

int	check_argument_logic(char **args)
{
	int	i;
	int	symbol;
	int	error;

	if (args[0][0] == '\0')
		return (1);
	error = 0;
	i = 0;
	while (args[i] != NULL)
	{
		symbol = is_reserved_symbol(args[i]);
		if (symbol < 0)
			error = 1;
		else if (symbol > 0)
		{
			if (args[i + 1] == NULL)
				error = 1;
			else if (is_reserved_symbol(args[i + 1]) > 0)
				error = 1;
			if (symbol == RESERVED_SYMBOL_PIPE)
				if (i == 0 || is_reserved_symbol(args[i - 1]) > 0)
						error = 1;
		}
		if (error != 0)
		{
			printf("syntax error near unexpected token '%s'\n", args[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
