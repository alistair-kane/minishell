// !!!!!

#include "../minishell.h"

int	check_argument_logic(char **args)
{
	int	i;

	if (args[0][0] == '\0')
		return (1);
	i = 0;
	while (args[i] != NULL)
	{
		i++;
	}
	return (0);
}
