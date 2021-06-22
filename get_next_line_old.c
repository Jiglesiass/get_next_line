/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joiglesi <joiglesi@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 10:12:11 by joiglesi          #+#    #+#             */
/*   Updated: 2021/06/18 14:43:52 by joiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int	ft_buff_init(char **buff, char **buff_cpy)
{
	int	i;

	if (!(*buff))
	{
		*buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!(*buff))
			return (0);
		*buff_cpy = *buff;
		printf("original buff addr: %p\n", *buff);
		i = 0;
		while(i <= BUFFER_SIZE)
			(*buff)[i++] = '\0';
	}
	return (1);
}

int	ft_strchr(const char *buff)
{
	int	i;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
		return (i);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	ft_buffcpy(char *buff_cpy, char **line, char **buff, int bytes, int *total)
{
	char	*tmp;
	int		i;

	printf("ft_buffcpy called: copying %d bytes from [%s]\nThen appending %d bytes from [%s](%p)\n", *total, *line, bytes, *buff, *buff);
	if (!bytes)
		return (0);
	tmp = *line;
	*line = (char *)malloc(sizeof(char) * (*total + bytes + 1));
	if (!(*line))
		return (-1);
	i = 0;
	while (i < *total && **buff != '\n')
	{
		(*line)[i] = tmp[i];
		i++;
	}
	while (i < *total + bytes && **buff != '\n')
	{
		(*line)[i++] = **buff;
		*buff += 1;
	}
	if (**buff != '\n')
		(*line)[i] = '\0';
	if (**buff == '\n')
		*buff += 1;
	if (**buff == '\0')
	{
		printf("end of buff reached\n");
		if (*(*buff - 1) == '\n')
		{	
			*buff = buff_cpy;
			printf("freeing buff (%p)\n", *buff);
			free(*buff);
			*buff = NULL;
		}
		*buff = buff_cpy;
	}
	*total += bytes;
	printf("buff after cpy: [%s] (%p)\nline after cpy: [%s]\n", *buff, *buff, *line);
	if (tmp)
		free(tmp);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*buff;
	static char	*buff_cpy;
	int			total_bytes;
	int			bytes_read;
	int			endl;

	if (!ft_buff_init(&buff, &buff_cpy))
		return (-1);
	*line = NULL;
	total_bytes = 0;
	endl = ft_strchr(buff);
	if (!endl)
	{
		if (ft_buffcpy(buff_cpy, line, &buff, ft_strlen(buff), &total_bytes) == -1)
			return (-1);
	}
	else
		return (ft_buffcpy(buff_cpy, line, &buff, endl, &total_bytes));
	bytes_read = 1;
	while ((bytes_read = read(fd, buff, BUFFER_SIZE)))
	{
		printf("%d bytes read: [%s] (%p)\n", bytes_read, buff, buff);
		endl = ft_strchr(buff);
		if (!endl)
		{
			if (ft_buffcpy(buff_cpy, line, &buff, ft_strlen(buff), &total_bytes) == -1)
				return (-1);
		}
		else
			return (ft_buffcpy(buff_cpy, line, &buff, endl, &total_bytes));
	}
	printf("trying to free addr: %p\n", buff);
	buff = buff_cpy;
	if (buff)
		free(buff);
	if (*line)
		**line = '\0';
	return (0);
}

int	main(int argc, char **argv)
{
	char	*line;
	int		bytes;
	int		fd;
	int		i;

	if (argc < 1)
		return (1);
	fd = open(argv[1], O_RDONLY);
	i = 1;
	while ((bytes = get_next_line(fd, &line)))
	{
		printf("\n\n---------- MAIN OUTPUT ----------\n");
		printf("line %d: %s\nreturn: %d\n", i++, line, bytes);
		printf("---------------------------------\n\n");
		free(line);
		if (bytes == -1)
			break ;
	}
	close(fd);
	return (0);
}
