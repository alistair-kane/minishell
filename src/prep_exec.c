// !!!!!

#include "../minishell.h"

static int	handle_reserved_symbols(t_exec *exec, char **arguments, int symbol,
				int *output);
static void	handle_input(t_exec *exec, char *filename);
static void	handle_output(t_exec *exec, char *filename);
static int	handle_commands(t_exec *exec, char **arguments);

// !!!!! todo? problem if last arguments is a '|' e.g. echo "test" |
int	prep_exec(t_data *data, char **arguments)
{
	int		i;
	int		output;
	int		symbol;
	t_exec	*exec;

	exec = init_exec();
	output = 0;
	i = 0;
	while (arguments[i] != NULL)
	{
		symbol = is_reserved_symbol(arguments[i]);
		if (symbol < 0)
			return (-1); // !!!!! printf("syntax error\n");
		if (symbol == RESERVED_SYMBOL_PIPE && output == 1)
		{
			vector_add(data->exec, exec);
			output = 0;
			exec = init_exec();
		}
		if (symbol > 0)
			i += handle_reserved_symbols(exec, &arguments[i], symbol, &output);
		else
			i += handle_commands(exec, &arguments[i]);
	}
	vector_add(data->exec, exec);
	return (0);
}

// returns the number of 'consumed' arguments (returns 1 for the pipe)
static int	handle_reserved_symbols(t_exec *exec, char **arguments, int symbol,
	int *output)
{
	if (symbol == RESERVED_SYMBOL_REDIRECT_INPUT)
	{
		handle_input(exec, arguments[1]);
		return (2);
	}
	if (symbol == RESERVED_SYMBOL_REDIRECT_OUTPUT)
	{
		*output = 1;
		handle_output(exec, arguments[1]);
		return (2);
	}
	// todo !!!!!
	return (1);
}

static void	handle_input(t_exec *exec, char *filename)
{
	int	length;

	if (filename == NULL)
		return ;
	if (exec->input_file != NULL)
		free(exec->input_file);
	length = ft_strlen(filename);
	exec->input_file = ft_calloc(length + 1, sizeof(char));
	if (exec->input_file == NULL)
		builtin_exit(1);
	ft_strlcpy(exec->input_file, filename, length + 1);
}

static void	handle_output(t_exec *exec, char *filename)
{
	int	i;
	int	length;

	if (filename == NULL)
		return ;
	i = 0;
	while (exec->output_files[i] != NULL)
		i++;
	if (i >= 128)
		return ;
	length = ft_strlen(filename);
	exec->output_files[i] = ft_calloc(length + 1, sizeof(char));
	if (exec->output_files[i] == NULL)
		builtin_exit(1);
	ft_strlcpy(exec->output_files[i], filename, length + 1);
}

// 'comsume' every argument until you hit the end or a reserved symbol
static int	handle_commands(t_exec *exec, char **arguments)
{
	char	**command;
	int		i;
	int		length;

	command = ft_calloc(128, sizeof(char *));
	if (command == NULL)
		builtin_exit(1);
	i = 0;
	while (is_reserved_symbol(arguments[i]) == 0)
	{
		length = ft_strlen(arguments[i]);
		command[i] = malloc(length + 1);
		if (command[i] == NULL)
			builtin_exit(1);
		ft_strlcpy(command[i], arguments[i], length + 1);
		i++;
		if (arguments[i] == NULL)
			break ;
	}
	command[i] = NULL;
	vector_add(exec->commands, command);
	return (i);
}
