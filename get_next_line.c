/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joiglesi <joiglesi@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 08:41:36 by joiglesi          #+#    #+#             */
/*   Updated: 2021/06/23 15:43:59 by joiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

typedef struct s_buff {
	int				fd;
	char			*buff;
	struct s_buff	*next;
}					t_buff;

size_t	ft_strlen(const char *s, char c)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] != c)
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s, '\0'))
		substr = (char *)malloc(sizeof(char));
	else
		substr = (char *)malloc(len * sizeof(char) + 1);
	if (substr == NULL)
	{
		free((char *)s);
		return (NULL);
	}
	i = 0;
	while (i < len && start < ft_strlen(s, '\0'))
		substr[i++] = s[start++];
	substr[i] = '\0';
	free((char *)s);
	return (substr);
}

t_buff	*ft_fd_search(t_buff *lst, int fd)
{
	t_buff	*tr;

	if (!lst)
		return (NULL);
	tr = lst;
	while (tr)
	{
		if (tr->fd == fd)
			return (tr);
		tr = tr->next;
	}
	return (NULL);
}

int	ft_lstadd_front(t_buff **alst, t_buff *new)
{
	if (!new)
		return (1);
	new->next = *alst;
	*alst = new;
	return (0);
}

t_buff	*ft_lstnew(int fd)
{
	t_buff	*new;

	new = (t_buff *)malloc(sizeof(t_buff));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->buff = NULL;
	new->next = NULL;
	return (new);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*jstr;
	size_t	len;
	size_t	i;
	size_t	j;

	len = ft_strlen(s1, '\0') + ft_strlen(s2, '\0');
	jstr = (char *)malloc(sizeof(char) * (len + 1));
	if (jstr == NULL)
	{
		free((char *)s1);
		free((char *)s2);
		return (NULL);
	}
	len = ft_strlen(s1, '\0');
	i = -1;
	while (++i < len)
		jstr[i] = s1[i];
	len += ft_strlen(s2, '\0');
	j = 0;
	while (i < len)
		jstr[i++] = s2[j++];
	jstr[i] = '\0';
	free((char *)s1);
	free((char *)s2);
	return (jstr);
}

int	ft_fd_finish(t_buff *current, char *buff, char **line)
{
	*line = ft_strjoin(*line, ft_substr(buff, 0, ft_strlen(buff, '\n')));
	if (!(*line))
		return (-1);
	free(buff);
	free(current);
	return (0);
}

char	*ft_read_line(int fd, int bufflen)
{
	char	*buff;
	char	*tmp;
	int		b_read;

	if (bufflen)
		buff = ft_strjoin(tmp, buff);
	else
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

	*line = NULL;
	buff = NULL;
	if (fd == -1)
		return (-1);
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
			*line = ft_substr(current->buff, 0, ft_strlen(buff, '\n'));
			current->buff = ft_substr(ft_strchr(current->buff, '\n'), 0,
					ft_strlen(ft_strchr(current->buff, '\n'), '\0'));
			if (!(*line) || !current->buff)
				return (-1);
			return (1);
		}
		current->buff = NULL;
	}
	buff = ft_read_line(fd, ft_strlen(buff, '\0'));
	if (!buff)
		return (-1);
	if (ft_strlen(buff, '\0') < BUFFER_SIZE)
		return (ft_fd_finish(current, buff, line));
	*line = ft_strjoin(*line, ft_substr(buff, 0, ft_strlen(buff, '\n')));
	current->buff = ft_substr(ft_strchr(buff, '\n'), 0,
			ft_strlen(ft_strchr(buff, '\n'), '\0'));
	if (!(*line) || !current->buff)
		return (-1);
	return (1);
}

int	main(void)
{
	printf("Hello 42\n");
	return (0);
}
