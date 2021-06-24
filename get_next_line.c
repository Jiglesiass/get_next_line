/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joiglesi <joiglesi@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 08:41:36 by joiglesi          #+#    #+#             */
/*   Updated: 2021/06/24 15:41:22 by joiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s, char c)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{	
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != c && s[i])
		i++;
	if (s[i] == c)
		return ((char *)&s[i]);
	return (NULL);
}

int	ft_fd_finish(t_buff *current, t_buff **buffers)
{
	t_buff	*tr;
	t_buff	*prev;

	tr = NULL;
	prev = *buffers;
	if (prev->next)
	{
		tr = prev->next;
		while (tr)
		{
			if (tr == current)
				break;
			prev = tr;
			tr = tr->next;
		}
		prev->next = tr->next;
		free(tr->buff);
		free(tr);
	}
	else
	{
		free(prev->buff);
		free(prev);
	}
	return (0);
}

char	*ft_read_line(int fd)
{
	char	*buff;
	char	*tmp;
	int		b_read;

	buff = NULL;
	b_read = BUFFER_SIZE;
	while (ft_strchr(buff, '\n') == NULL && b_read == BUFFER_SIZE)
	{
		tmp = buff;
		buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return (NULL);
		b_read = read(fd, buff, BUFFER_SIZE);
		buff[b_read] = '\0';
		buff = ft_strjoin(tmp, buff);
	}
	return (buff);
}

int	get_next_line(int fd, char **line)
{
	static t_buff	*buffers;
	t_buff			*current;
	char			*buff;

	if (fd < 0 || fd > FOPEN_MAX)
		return (-1);
	*line = NULL;
	buff = NULL;
	if (!ft_fd_search(buffers, fd))
	{
		if (ft_lstadd_front(&buffers, ft_lstnew(fd)))
			return (-1);
	}
	current = ft_fd_search(buffers, fd);
	if (current->buff)
	{
		if (ft_strchr(current->buff, '\n'))
		{
			*line = ft_substr(current->buff, 0, ft_strlen(current->buff, '\n'));
			current->buff = ft_substr(ft_strchr(current->buff, '\n') + 1, 0,
					ft_strlen(ft_strchr(current->buff, '\n'), '\0'));
			if (!(*line) || !current->buff)
				return (-1);
			return (1);
		}
		if (current->last && !current->buff[0])
			return (ft_fd_finish(current, &buffers));
		*line = current->buff;
		current->buff = NULL;
	}
	buff = ft_strjoin(buff, ft_read_line(fd));
	if (!buff)
		return (-1);
	if (ft_strlen(buff, '\0') < BUFFER_SIZE)
		current->last = 1;
	if (!ft_strlen(buff, '\0'))
		return (ft_fd_finish(current, &buffers));
	*line = ft_strjoin(*line, ft_substr(buff, 0, ft_strlen(buff, '\n')));
	current->buff = ft_substr(ft_strchr(buff, '\n') + 1, 0,
			ft_strlen(ft_strchr(buff, '\n'), '\0'));
	free(buff);
	if (!(*line) || !current->buff)
		return (-1);
	return (1);
}

/*int	main(void)
{
	char	*line;
	int		fd;
	int		r;

	fd = open("lines", O_RDONLY);
	r = get_next_line(fd, &line);
	printf("\n\n---------- MAIN OUTPUT ----------\n");
	printf("line=[%s]\nreturn=%d\n", line, r);
	printf("---------------------------------\n\n");
	free(line);
	r = get_next_line(fd, &line);
	printf("\n\n---------- MAIN OUTPUT ----------\n");
	printf("line=[%s]\nreturn=%d\n", line, r);
	printf("---------------------------------\n\n");
	free(line);
	r = get_next_line(fd, &line);
	printf("\n\n---------- MAIN OUTPUT ----------\n");
	printf("line=[%s]\nreturn=%d\n", line, r);
	printf("---------------------------------\n\n");
	free(line);
}*/

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
		printf("line %d: %s\nreturn: %d\n", i++, line, r);
		free(line);
		if (r == -1)
			break;
	}
	printf("----- Final Values -----\n");
	printf("line=[%s]\n", line);
	printf("r=%d\n", r);
	return (0);
}*/
