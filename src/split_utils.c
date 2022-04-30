// !!!!!

#include "../minishell.h"

static int	check_reset(char *arg, int *delp1, int *delp2, int *i)
{
	if (*delp1 != -1 && *delp2 != -1)
	{
		*delp2 -= 1;
		ft_memmove(&arg[*delp1], &arg[*delp1 + 1], ft_strlen(arg) - *delp1);
		ft_memmove(&arg[*delp2], &arg[*delp2 + 1], ft_strlen(arg) - *delp2);
		*delp1 = -1;
		*delp2 = -1;
		*i -= 2;
		return (1);
	}
	return (0);
}

static void	char_cleanup(char *arg)
{
	int	i;
	int	delp1;
	int	delp2;
	int	single;
	int	dbl;

	single = 0;
	dbl = 0;
	delp1 = -1;
	delp2 = -1;
	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '\\')
			i += 2;
		if (arg[i] == '\'' || arg[i] == '"')
		{
			if (handle_quotes(arg[i], &dbl, &single) == 1)
			{
				if (delp1 == -1)
					delp1 = i;
				else
					delp2 = i;
			}
		}
		check_reset(arg, &delp1, &delp2, &i);
	}
}

void	quote_master(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		char_cleanup(args[i]);
	}
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
