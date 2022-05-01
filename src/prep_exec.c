// !!!!!

#include "../minishell.h"

static int	handle_reserved_symbols(t_exec *exec, char **arguments, int symbol,
				int *output);
static int	handle_input(t_exec *exec, char *filename);
static int	handle_output(t_exec *exec, char *filename, int append);
static int	handle_commands(t_exec *exec, char **arguments);

int	prep_exec(t_data *data, char **arguments)
{
	char	*temp;
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
		if (symbol == RESERVED_SYMBOL_PIPE && output == 1)
		{
			vector_add(data->exec, exec);
			output = 0;
			exec = init_exec();
		}
		if (symbol > 0)
		{
			if (symbol == RESERVED_SYMBOL_PIPE && i == 2 && exec->here_flag == 0
				&& exec->input_file != NULL)
			{
				free(exec->input_file);
				exec->input_file = NULL;
				temp = create_filename(exec, "temp");
				handle_input(exec, temp);
				close(open(exec->input_file, O_RDWR | O_CREAT, 0644));
			}
			i += handle_reserved_symbols(exec, &arguments[i], symbol, &output);
		}
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
	char	*filename;

	if (symbol == RESERVED_SYMBOL_REDIRECT_INPUT)
	{
		return (handle_input(exec, arguments[1]));
	}
	if (symbol == RESERVED_SYMBOL_REDIRECT_OUTPUT
		|| symbol == RESERVED_SYMBOL_APPEND_OUTPUT)
	{
		*output = 1;
		if (symbol == RESERVED_SYMBOL_APPEND_OUTPUT)
			return (handle_output(exec, arguments[1], 1));
		else
			return (handle_output(exec, arguments[1], 0));
	}
	if (symbol == RESERVED_SYMBOL_HERE_DOC)
	{
		exec->here_flag = 1;
		filename = handle_here_doc(exec, arguments[1]);
		return (handle_input(exec, filename));
	}
	return (1);
}

static int	handle_input(t_exec *exec, char *filename)
{
	int	length;

	if (filename == NULL)
		return (1);
	if (exec->input_file != NULL)
		free(exec->input_file);
	length = ft_strlen(filename);
	exec->input_file = ft_calloc(length + 1, sizeof(char));
	if (exec->input_file == NULL)
		exit(1);
	ft_strlcpy(exec->input_file, filename, length + 1);
	return (2);
}

static int	handle_output(t_exec *exec, char *filename, int append)
{
	int	i;
	int	length;

	if (filename == NULL)
		return (1);
	i = 0;
	while (exec->output_files[i] != NULL)
		i++;
	if (i >= 128)
		return (2);
	exec->append_output[i] = append;
	length = ft_strlen(filename);
	exec->output_files[i] = ft_calloc(length + 1, sizeof(char));
	if (exec->output_files[i] == NULL)
		exit(1);
	ft_strlcpy(exec->output_files[i], filename, length + 1);
	return (2);
}

// 'comsume' every argument until you hit the end or a reserved symbol
static int	handle_commands(t_exec *exec, char **arguments)
{
	char	**command;
	int		i;
	int		length;

	command = ft_calloc(128, sizeof(char *));
	if (command == NULL)
		exit(1);
	i = 0;
	while (is_reserved_symbol(arguments[i]) == 0)
	{
		length = ft_strlen(arguments[i]);
		command[i] = malloc(length + 1);
		if (command[i] == NULL)
			exit(1);
		ft_strlcpy(command[i], arguments[i], length + 1);
		i++;
		if (arguments[i] == NULL)
			break ;
	}
	command[i] = NULL;
	vector_add(exec->commands, command);
	return (i);
}
