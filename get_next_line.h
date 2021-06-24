/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joiglesi <joiglesi@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 14:25:23 by joiglesi          #+#    #+#             */
/*   Updated: 2021/06/24 15:39:42 by joiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

typedef struct s_buff {
	int				fd;
	char			*buff;
	int				last;
	struct s_buff	*next;
}					t_buff;

int		get_next_line(int fd, char **line);
size_t	ft_strlen(const char *s, char c);
char	*ft_strchr(const char *s, int c);
int		ft_fd_finish(t_buff *current, t_buff **buffers);
char	*ft_read_line(int fd);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_substr(const char *s, unsigned int start, size_t len);
int		ft_lstadd_front(t_buff **alst, t_buff *new);
t_buff	*ft_fd_search(t_buff *lst, int fd);
t_buff	*ft_lstnew(int fd);

#endif
