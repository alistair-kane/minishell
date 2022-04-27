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
		if (check_reset(arg, &delp1, &delp2, &i) != 0)
			break ;
	}
}

void	quote_master(char **args)
{
	int	i;

	i = -1;
	while(args[++i])
	{
		char_cleanup(args[i]);
	}
}