/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joiglesi <joiglesi@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 14:22:24 by joiglesi          #+#    #+#             */
/*   Updated: 2021/06/29 13:26:44 by joiglesi         ###   ########.fr       */
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

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;

	s2 = malloc(ft_strlen(s1, '\0') + 1);
	if (!s2 || !s1)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
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
