/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joiglesi <joiglesi@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 08:41:36 by joiglesi          #+#    #+#             */
/*   Updated: 2021/06/29 13:26:44 by joiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_line(int fd)
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
	}
	return (buff);
}

int	get_next_line(int fd, char **line)
{
	static char	*buffers[FOPEN_MAX];
	char		*buff;

	if (fd < 0 || fd > FOPEN_MAX)
		return (-1);
	*line = NULL;
	buff = NULL;
	if (buffers[fd])
	{
		if (ft_strchr(buffers[fd], '\n'))
		{
			*line = ft_substr(buffers[fd], 0, ft_strlen(buffers[fd], '\n'));
			buff = ft_strdup(buffers[fd]);
			free(buffers[fd]);
			buffers[fd] = ft_substr(ft_strchr(buff, '\n') + 1, 0,
					ft_strlen(ft_strchr(buff, '\n'), '\0'));
			free(buff);
			if (!(*line) || !buffers[fd])
				return (-1);
			return (1);
		}
		buff = ft_strdup(buffers[fd]);
		free(buffers[fd]);
		buffers[fd] = NULL;
	}
	buff = ft_strjoin(buff, ft_read_line(fd));
	if (!buff)
		return (-1);
	if (!ft_strlen(buff, '\0') || !ft_strchr(buff, '\n'))
	{
		*line = buff;
		free(buffers[fd]);
		buffers[fd] = NULL;
		return (0);
	}
	*line = ft_strjoin(*line, ft_substr(buff, 0, ft_strlen(buff, '\n')));
	buffers[fd] = ft_substr(ft_strchr(buff, '\n') + 1, 0,
			ft_strlen(ft_strchr(buff, '\n'), '\0'));
	free(buff);
	if (!(*line) || !buffers[fd])
		return (-1);
	return (1);
}

/*int	main(void)
{
	char	*line;
	int		fd;
	int		r;
	int		i;

	fd = open("lines", O_RDONLY);
	if (fd == -1)
		return (1);
	i = 1;
	while ((r = get_next_line(fd, &line)))
	{
		printf("line %d: [%s]\nreturn: %d\n", i++, line, r);
		free(line);
		if (r == -1)
			break;
	}
	printf("----- Final Values -----\n");
	printf("line=[%s]\n", line);
	printf("r=%d\n", r);
	r = get_next_line(fd, &line);
	printf("\n\n---------- MAIN OUTPUT ----------\n");
	printf("line=[%s]\nreturn=%d\n", line, r);
	printf("---------------------------------\n\n");
	free(line);
	return (0);
}*/
