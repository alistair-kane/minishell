/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:52:41 by alkane            #+#    #+#             */
/*   Updated: 2022/05/02 18:15:03 by alkane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	max(int val1, int val2)
{
	if (val1 > val2)
		return (val1);
	return (val2);
}

char	*get_home_dir(t_data *data)
{
	size_t			i;
	t_environment	*temp;

	i = -1;
	while (++i < data->environment->total)
	{
		temp = vector_get(data->environment, i);
		if (!ft_strncmp(temp->name, "HOME", 4))
			return (temp->value);
	}
	return (NULL);
}

void	set_old_pwd(t_data *data)
{
	char *temp[3];

	temp[0] = "export";
	temp[1] = ft_strjoin("OLDPWD=", data->pwd);
	temp[2] = NULL;
	builtin_export(data, temp);
	free(temp[1]);
}

void	set_new_pwd(t_data *data)
{
	char	*temp[3];
	char	buf[PATH_MAX];
	
	getcwd(buf, PATH_MAX);
	temp[0] = "export";
	temp[1] = ft_strjoin("PWD=", buf);
	temp[2] = NULL;
	builtin_export(data, temp);
	free(temp[1]);
	ft_strlcpy(data->pwd, buf, ft_strlen(buf) + 1);
}
