// !!!!!

#include "../minishell.h"

int	check_argument_logic(char **args)
{
	int	i;
	int	symbol;

	if (args[0][0] == '\0')
		return (1);
	i = 0;
	while (args[i] != NULL)
	{
		symbol = is_reserved_symbol(args[i]);
		if (symbol < 0)
		{
			printf("syntax error near unexpected token '%s'\n", args[i]);
			return (1);
		}
		else if (symbol > 0)
		{
			if (args[i + 1] == NULL)
			{
				printf("syntax error near unexpected token '%s'\n", args[i]);
				return (1);
			}
			if (symbol == RESERVED_SYMBOL_PIPE && i == 0)
			{
				printf("syntax error near unexpected token '%s'\n", args[i]);
				return (1);
			}
		}
		i++;
	}
	return (0);
}
