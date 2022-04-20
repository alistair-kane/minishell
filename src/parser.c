// !!!!!

#include "../minishell.h"

// searching path to match
// int	check_binaries(t_data *data, char **arg)
// {
// 	int		i;
// 	char	*temp;
// 	char	*path;

// 	i = -1;
// 	// needs to refactored for t-vector struct!!!!!
// 	while (paths[++i] != NULL)
// 	{
// 		if (i == 0)
// 			//incremented forwartd by 5 to "look" past PATHS start of string
// 			ft_memmove(paths[i], paths[i] + 5, ft_strlen(paths[i] + 5));
// 		temp = ft_strjoin(paths[i], "/");
// 		path = ft_strjoin(temp, arg);
// 		free(temp);
// 		if (!access(path, X_OK))
// 			return (path);
// 		free(path);
// 	}
// 	// only finding the path of the binary, need to decide when its executed later
// 	return (NULL);
// }

int	check_builtin(t_data *data, char **args)
{
	if (!ft_strcmp("echo", args[0]))
		return (builtin_echo(data, args));
	else if (!ft_strcmp("cd", args[0]))
		return (builtin_cd(data, args));
	else if (!ft_strcmp("pwd", args[0]))
		return (builtin_pwd(data));
	else if (!ft_strcmp("export", args[0]))
		return (builtin_export(data, args));
	else if (!ft_strcmp("unset", args[0]))
		return (builtin_unset(data, args));
	else if (!ft_strcmp("env", args[0]))
		return (builtin_env(data));
	else if (!ft_strcmp("exit", args[0]))
		builtin_exit(0);
	return (0);
}

// int	parse_args(t_data *data, char **arg)
// {
// 	int	consumed;
	
// 	// check for pipe and redirects
// 	// check for -1 return e.g. cd = too many arguments 
// 	consumed = check_builtin(data, arg);
// 	if (consumed)
// 		return (consumed);
	
// 	consumed = check_binaries(data, arg);
// 	// if (!consumed)
// 	return (consumed);
// }

void	parser(t_data *data, char *buf)
{
	char	**args;

	// new pre-parser should handle all whitespace chars and ___ " ' $ ___ (not splitting inside)
	args = ms_split(data, buf);
	env_expansion(data, args);
	if (prep_exec(data, args) != 0)
	{
		printf("syntax error\n");
		free_vector(args);
		vector_clear(data->exec);
		return ;
	}
	exec(data);
	// // #ifdef _DEBUG
	// char	**tmp;
	// int		j;
	// int		k;
	// t_exec	*exec;
	// i = 0;
	// while (i < (int)data->exec->total)
	// {
	// 	exec = vector_get(data->exec, i);
	// 	printf ("!!!input: %s\n", exec->input_file);
	// 	j = 0;
	// 	while (exec->output_files[j] != NULL)
	// 	{
	// 		printf("!!!output: %s\n", exec->output_files[j]);
	// 		j++;
	// 	}
	// 	k = 0;
	// 	tmp = vector_get(exec->commands, k);
	// 	while (tmp != NULL)
	// 	{
	// 		j = 0;
	// 		printf("test: %s", *tmp);
	// 		while (tmp[j] != NULL)
	// 		{
	// 			printf("!params:§%s, %d\n", tmp[j], j);
	// 			j++;
	// 		}
	// 		k++;
	// 		tmp = vector_get(exec->commands, k);
	// 	}
	// 	i++;
	// }
	// #endif // _DEBUG
	// i = 0;
	// while (args[i])
	// {
	// 	i += parse_args(data, &args[i]);
	// 	// printf("\nargs parsed: %i\n", i);
	// 	// line is here incase parse_args not functioning as intended
	// 	// i++;
	// }
	free_vector(args);
	vector_clear(data->exec);
}
