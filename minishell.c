// !!!!!

#include "minishell.h"

int	main(void)
{
	char	*buf;
	t_data	*data;

	data = data_init();
	if (data == NULL)
		return (-1);
	while (1)
	{
		buf = readline(PROMPT);
		if (buf != NULL)
		{
			if (ft_strlen(buf))
				add_history(buf);
			vector_add(data->history, buf);
			parser(data, buf);
			if (data->exit != 0)
				break ;
		}
	}
	data_cleanup(data);
	return (data->exit_value);
}
