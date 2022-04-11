// !!!!!

#include "../minishell.h"

// static void	free_double(char **dp, int i)
// {
// 	while (dp[++i])
// 		free(dp[i]);
// 	free(dp);
// }

static char	*return_path(char **paths, char *execname)
{
	int		i;
	char	*temp;
	char	*path;

	i = -1;
	while (paths[++i] != NULL)
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, execname);
		free(temp);
		if (!access(path, X_OK))
			return (path);
		free(path);
	}
	return (NULL);
}

static char	*seek_path(t_data *data, char *execname)
{
	
	if (return_path(data->path, execname))
		return (return_path(data->path, execname));
	// free_double(data->path, -1);
	// free(execname);
	return (NULL);
}

int	check_binaries(t_data *data, char **args)
{
	extern  char    **environ;
	char		    *path;
	pid_t           pid;
	int				res;

	path = seek_path(data, args[0]);
	if (!path)
	{
		// free_double(input, 0);
		// exit_error("command not found");
		printf("command not found\n");
	}
	else
	{
		res = 0;
		pid = fork();
    	if(pid == 0) //child
   		{
        	printf("in child\n");
			res = execve(path, args, environ);
        	if(res < 0) 
       		{
        		printf("error: child1: %d exec failed %d\n", pid, errno);
        		exit(91); //must exit child
			}
		}
		else if(pid > 0) //cid>0, parent, waitfor child
		{
			waitpid(pid, NULL, 0);
			printf("child: %d res %d\n", pid, res);
			return (1);
		}
		else //cid1 < 0, error
		{
			printf("error: child fork failed\n");
		}
	}
	// exit_error(path);
	return (1);
}
