/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joiglesi <joiglesi@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 14:22:24 by joiglesi          #+#    #+#             */
/*   Updated: 2021/06/29 11:22:39 by joiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
		free((char *)s);
	i = 0;
	while (i < len && start < ft_strlen(s, '\0'))
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}

int	ft_lstadd_front(t_buff **alst, t_buff *new)
{
	if (!new)
		return (1);
	new->next = *alst;
	*alst = new;
	return (0);
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


