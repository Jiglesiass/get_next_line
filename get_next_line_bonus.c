/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joiglesi <joiglesi@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 08:41:36 by joiglesi          #+#    #+#             */
/*   Updated: 2021/06/30 08:33:39 by joiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_read_line(int fd)
{
	char	*buff;
	char	*tmp;
	int		b_read;
	int		endl;

	buff = NULL;
	endl = 0;
	b_read = BUFFER_SIZE;
	while (!endl && b_read == BUFFER_SIZE)
	{
		tmp = buff;
		buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return (NULL);
		b_read = read(fd, buff, BUFFER_SIZE);
		buff[b_read] = '\0';
		if (ft_strchr(buff, '\n'))
			endl = 1;
		buff = ft_strjoin(tmp, buff);
		if (!buff)
			return (NULL);
	}
	if (b_read == -1)
		return (NULL);
	return (buff);
}

static int	ft_before_read(int fd, char **line, char *buffers[], char **buff)
{
	if (buffers[fd])
	{
		if (ft_strchr(buffers[fd], '\n'))
		{
			*line = ft_substr(buffers[fd], 0, ft_strlen(buffers[fd], '\n'));
			*buff = ft_strdup(buffers[fd]);
			if (!(*buff))
				return (-1);
			free(buffers[fd]);
			buffers[fd] = ft_substr(ft_strchr(*buff, '\n') + 1, 0,
					ft_strlen(ft_strchr(*buff, '\n'), '\0'));
			free(*buff);
			if (!(*line) || !buffers[fd])
				return (-1);
			return (1);
		}
		*buff = ft_strdup(buffers[fd]);
		if (!(*buff))
			return (-1);
		free(buffers[fd]);
		buffers[fd] = NULL;
	}
	return (0);
}

static int	ft_finish(int fd, char **line, char *buffers[], char *buff)
{
	*line = buff;
	free(buffers[fd]);
	buffers[fd] = NULL;
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*buffers[FOPEN_MAX];
	char		*buff;
	int			r;

	if (fd < 0 || fd > FOPEN_MAX)
		return (-1);
	*line = NULL;
	buff = NULL;
	r = ft_before_read(fd, line, buffers, &buff);
	if (r)
		return (r);
	buff = ft_strjoin(buff, ft_read_line(fd));
	if (!buff)
		return (-1);
	if (!ft_strlen(buff, '\0') || !ft_strchr(buff, '\n'))
		return (ft_finish(fd, line, buffers, buff));
	*line = ft_strjoin(*line, ft_substr(buff, 0, ft_strlen(buff, '\n')));
	buffers[fd] = ft_substr(ft_strchr(buff, '\n') + 1, 0,
			ft_strlen(ft_strchr(buff, '\n'), '\0'));
	free(buff);
	if (!(*line) || !buffers[fd])
		return (-1);
	return (1);
}
