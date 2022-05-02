/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:50:02 by alkane            #+#    #+#             */
/*   Updated: 2022/05/02 18:28:36 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*handle_question_var(t_data *data, char *var_holder)
{
	char			*status;
	char			trail[PATH_MAX];

	status = ft_itoa(WEXITSTATUS(data->status));
	ft_strlcpy(trail, &var_holder[ft_strlen(status)], PATH_MAX);
	ft_strlcpy(var_holder, status, ft_strlen(status) + 1);
	ft_strlcat(var_holder, trail, PATH_MAX - ft_strlen(status));
	free(status);
	return (var_holder);
}

static char	*env_var_replace(t_data *data, char *var_holder)
{
	t_environment	*temp;
	size_t			i;

	if (var_holder[0] == '?')
		return (handle_question_var(data, var_holder));
	i = -1;
	while (++i < data->environment->total)
	{
		temp = vector_get(data->environment, i);
		if (!ft_strcmp(temp->name, var_holder))
		{
			ft_strlcpy(var_holder, temp->value, ft_strlen(temp->value) + 1);
			return (var_holder);
		}
	}
	free(var_holder);
	return (NULL);
}

static char	*expansion_ops(t_data *data, char *arg, int i)
{
	int		end;
	int		total_len;
	char	*new_arg;
	char	*var_holder;
	char	trail[4096];

	total_len = ft_strlen(arg) + 1;
	new_arg = ft_calloc(PATH_MAX, 1);
	var_holder = ft_calloc(PATH_MAX, 1);
	end = i + get_env_var_end(&arg[i]);
	ft_strlcpy(new_arg, arg, i);
	ft_strlcpy(var_holder, &arg[i], end - i + 1);
	ft_strlcpy(trail, &arg[end], total_len - end);
	free(arg);
	var_holder = env_var_replace(data, var_holder);
	if (var_holder == NULL)
		ft_strlcat(new_arg, trail, ft_strlen(new_arg) + ft_strlen(trail) + 1);
	else
	{
		total_len = ft_strlcat(new_arg, var_holder, ft_strlen(new_arg) \
			+ ft_strlen(var_holder) + 1);
		ft_strlcat(new_arg, trail, total_len + ft_strlen(trail) + 1);
		free(var_holder);
	}
	return (new_arg);
}

static char	*expansion_helper(t_data *data, char *arg, int *i)
{
	arg = expansion_ops(data, arg, *i + 1);
	if (arg[*i] == '$')
		(*i)--;
	return (arg);
}

char	*env_expansion(t_data *data, char *arg)
{
	int	i;
	int	qf[2];

	qf[0] = -1;
	qf[1] = -1;
	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '\"')
			qf[1] *= -1;
		if (arg[i] == '\'' && qf[1] == -1)
			qf[0] *= -1;
		if (arg[i] == '\\')
			i++;
		else if (arg[i] == '$' && qf[0] == -1)
		{
			if (arg[i + 1] == '\0')
				return (arg);
			if (arg[i + 1] == '$')
				i++;
			else
				arg = expansion_helper(data, arg, &i);
		}
	}
	return (arg);
}
