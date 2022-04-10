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

int	check_builtin(t_data *data, char **arg)
{
	if (!ft_strcmp("echo", arg[0]))
		return (builtin_echo(data, arg));
	else if (!ft_strcmp("cd", arg[0]))
		return (builtin_cd(data, arg));
	else if (!ft_strcmp("pwd", arg[0]))
		return (builtin_pwd(data));
	else if (!ft_strcmp("export", arg[0]))
		return (builtin_export(data, arg));
	else if (!ft_strcmp("unset", arg[0]))
		return (builtin_unset(data, arg));
	else if (!ft_strcmp("env", arg[0]))
		return (builtin_env(data));
	else if (!ft_strcmp("exit", arg[0]))
		// 0 represents exit code
		builtin_exit(0);

	// 1 returned for testing only
	return (1);
}

void	env_var_replace(t_data *data, char **argp, char *arg)
{
	t_environment	*temp;
	size_t			i;
	char			*ret;

	i = -1;
	while (++i < data->environment->total)
	{
		temp = vector_get(data->environment, i);
		if (!ft_strcmp(temp->name, arg))
		{
			ret = ft_calloc(ft_strlen(temp->value) + 1, sizeof(char));
			ft_strlcpy(ret, temp->value, ft_strlen(temp->value) + 1);
			*argp = ret;
			// !!!!! I thought reassigning the pointer like this would cause leaks, valgrind shows nothing though
		}
	}
}

void	env_expansion(t_data *data, char **args)
{
	int	i;
	char *temp;

	if (args && data)
	{
		i = -1;
		while (args[++i] != NULL)
		{
			// get the environmental variables
			// loop through environ.name looking for a full match with arg[i] + 1 (after $)
			// if found, change the text where arg[i] is to be the text held in envion.value
			if (args[i][0] == '$')
			{
				temp = args[i] + 1;
				env_var_replace(data, &args[i], temp);
			}
			// closed "" handled
			else if (args[i][0] == '"' && args[i][1] == '$')
			{
				temp = args[i] + 2;
				temp = ft_strtrim(temp, "\"");
				env_var_replace(data, &args[i], temp);
				free(temp);
			}
		}
	}
}


int	parse_args(t_data *data, char **arg)
{
	int	consumed;
	
	// check for pipe and redirects
	
	consumed = check_builtin(data, arg);
	if (!consumed)
		return (consumed);
	
	// consumed = check_binaries(data, arg);
	// if (!consumed)
		return (consumed);
}

void	parser(t_data *data, char *buf)
{
	char	**args;
	int		i;

	// line preprocessing goes here

	// !!!!! split must be replaced
	// new pre-parser should handle all whitespace chars and ___ " ' $ ___ (not splitting inside)
	args = ms_split(buf);
	env_expansion(data, args);
	i = 0;
	while (args[i])
	{
		i += parse_args(data, &args[i]);
		
		// line is here incase parse_args not functioning as intended
		// i++;
	}
	// !!!!! free split (args)
}