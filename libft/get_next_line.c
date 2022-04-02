/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alistair <alistair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 17:08:24 by alkane            #+#    #+#             */
/*   Updated: 2022/01/20 20:09:58 by alistair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*return_free(char *line)
{
	free(line);
	return (NULL);
}

static void	bufjoiner(char **s1, char *buf)
{
	char			*dst;
	unsigned int	total_size;
	int				i;
	int				j;

	if (!*s1 || !buf)
		return ;
	total_size = ft_strlen(*s1) + ft_strlen(buf) + 1;
	dst = ft_calloc(total_size, sizeof (char));
	if (!dst)
		return ;
	i = -1;
	while (s1[0][++i])
		dst[i] = s1[0][i];
	free(s1[0]);
	j = 0;
	while ((buf[j] != '\n') && buf[j])
		dst[i++] = buf[j++];
	if (buf[j] == '\n')
		dst[i] = '\n';
	*s1 = dst;
}

static void	memory_shift(char *buf)
{
	int		first_l_len;
	int		second_l_len;
	int		len_buf;

	len_buf = ft_strlen(buf);
	first_l_len = len_buf - ft_strlen(ft_strchr(buf, '\n') + 1);
	second_l_len = len_buf - first_l_len;
	ft_memmove(buf, &buf[first_l_len], second_l_len);
	ft_memset(&buf[second_l_len], '\0', first_l_len);
}

char	*get_next_line(int fd)
{
	static char		buf[BUFFER_SIZE + 1];
	int				read_bytes;
	char			*line;

	if (fd < 0)
		return (NULL);
	line = ft_calloc(1, sizeof(char));
	while (!ft_strchr(buf, '\n'))
	{
		if (*buf)
			bufjoiner(&line, buf);
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes <= 0 && !(*line))
			return (return_free(line));
		buf[read_bytes] = '\0';
		if (!ft_strchr(buf, '\n') && read_bytes < BUFFER_SIZE)
		{
			bufjoiner(&line, buf);
			ft_memset(buf, '\0', 1);
			return (line);
		}
	}
	bufjoiner(&line, buf);
	memory_shift(buf);
	return (line);
}

// int main(void)
// {
// 	int	fd;
// 	char *res;
// 	int i;

// 	fd = open("multiple_line_no_nl", O_RDWR);
// 	i = 0;
// 	while (i < 9)
// 	{
// 		res = get_next_line(fd);
// 		printf("line %i: %s",i, res);
// 		i++;
// 	}
// }