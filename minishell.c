// !!!!!

#include "minishell.h"

int	main(void)
{
	char	*buf;
	int		ret;
	t_data	*data;

	data = data_init();
	if (data == NULL)
		return (-1);
	while (1)
	{
		buf = readline(PROMPT);
		if (buf == NULL) // !!!!! TODO
			break ;
		if (ft_strlen(buf))
			add_history(buf);
		vector_add(data->history, buf);
		parser(data, buf);
		if (data->exit != 0)
			break ;
	}
	ret = data->exit_value;
	data_cleanup(data);
	return (ret);
}
