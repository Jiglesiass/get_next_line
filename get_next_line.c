/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joiglesi <joiglesi@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 08:41:36 by joiglesi          #+#    #+#             */
/*   Updated: 2021/06/22 12:30:32 by joiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE = 32
#endif

typedef struct	s_buff {
	int				fd;
	char			**lines;
	int				index;
	struct s_buff	*next;
}					t_buff;

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	ft_strnchr(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		substr = (char *)malloc(sizeof(char));
	else
		substr = (char *)malloc(len * sizeof(char) + 1);
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (i < len && start < ft_strlen(s))
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}

static int	ft_split_count(const char *s, char c)
{
	int	c_index;
	int	count;
	int	i;

	count = 0;
	i = ft_strlen(s);
	while (i > 0)
	{
		c_index = ft_strnchr(s, c);
		if (c_index > 0)
			count++;
		s += c_index + 1;
		i -= (c_index + 1);
	}
	return (count);
}

static int	ft_null_case(char **split, int index)
{
	split[index + 1] = NULL;
	if (!split[index])
	{
		while (*split)
			free(*(split++));
		free(split);
		return (1);
	}
	return (0);
}

char	**ft_split(const char *s, char c)
{
	char	**split;
	int		c_index;
	int		split_index;
	int		count;

	if (!s)
		return (NULL);
	count = ft_split_count(s, c);
	split = (char **)malloc(sizeof(char *) * (count + 1));
	if (!split)
		return (NULL);
	*split = NULL;
	split_index = 0;
	while (split_index < count)
	{
		c_index = ft_strnchr(s, c);
		if (c_index > 0)
		{
			split[split_index++] = ft_substr(s, 0, c_index);
			if (ft_null_case(split, split_index - 1))
				return (NULL);
		}
		s += c_index + 1;
	}
	return (split);
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
	new->index = 0;
	new->next = NULL;
	return (new);
}

char	*ft_read_file(int fd)
{
	char	*buff;
	char	*tmp;
	int		b_read;
	int		b_total;

	b_total = BUFFER_SIZE;
	buff = (char *)malloc(sizeof(char) * b_total);
	while (b_read)
	{
		b_read = read(fd, buff, BUFFER_SIZE);
		b_total += b_read;
		buff = (char *)malloc(sizeof(char) * b_total);
		b_total += b_read;
	}
}

int	get_next_line(int fd, char **line)
{
	static t_buff	*buffers;
	t_buff			*current;
	char			*buff;

	if (fd == -1)
		return (-1);
	if (!ft_fd_search(buffers, fd))
		if(ft_lstadd_front(&buffers, ft_lstnew(fd)))
			return (-1);
	current = ft_fd_search(buffers, fd);
	if (current && current->lines && current->lines[current->index])
	{
		*line = current->lines[current->index];
		free(current->lines[current->index]);
		current->lines[current->index] = NULL;
		return (1);
	}
	buff = ft_read_file(fd);
	return (0);
}

int	main(void)
{
	return (0);
}
