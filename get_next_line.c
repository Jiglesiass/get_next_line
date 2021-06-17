/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joiglesi <joiglesi@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 10:12:11 by joiglesi          #+#    #+#             */
/*   Updated: 2021/06/17 11:47:49 by joiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int	ft_buff_init(char **buff)
{
	int	i;

	if (!(*buff))
	{
		*buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!(*buff))
			return (0);
		printf("original buff addr: %p\n", *buff);
		//(*buff)[BUFFER_SIZE] = '\0';
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

int	ft_buffcpy(char **line, char **buff, int bytes, int *total)
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
	while (i < *total)
	{
		(*line)[i] = tmp[i];
		i++;
	}
	while (i < *total + bytes)
	{
		(*line)[i++] = **buff;
		*buff += 1;
	}
	(*line)[i] = '\0';
	if (**buff == '\n')
		*buff += 1;
	if (**buff == '\0' && bytes > 0)
	{
		printf("resetting buff address\n");
		*buff -= BUFFER_SIZE;
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
	int			total_bytes;
	int			bytes_read;
	int			endl;

	if (!ft_buff_init(&buff))
		return (-1);
	*line = NULL;
	total_bytes = 0;
	endl = ft_strchr(buff);
	if (!endl)
	{
		if (ft_buffcpy(line, &buff, ft_strlen(buff), &total_bytes) == -1)
			return (-1);
	}
	else
		return (ft_buffcpy(line, &buff, endl, &total_bytes));
	bytes_read = 1;
	while ((bytes_read = read(fd, buff, BUFFER_SIZE)))
	{
		printf("%d bytes read: [%s] (%p)\n", bytes_read, buff, buff);
		endl = ft_strchr(buff);
		if (!endl)
		{
			if (ft_buffcpy(line, &buff, ft_strlen(buff), &total_bytes) == -1)
				return (-1);
		}
		else
			return (ft_buffcpy(line, &buff, endl, &total_bytes));
	}
	printf("trying to free addr: %p\n", buff);
	free(buff);
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

/*int	main(void)
{
	char	*line;
	int		fd;
	int		r;

	fd = open("lines", O_RDONLY);
	if (fd == -1)
		return (1);
	r = get_next_line(fd, &line);
	printf("\n\n---------- MAIN OUTPUT ----------\n");
	printf("line: %s\nreturn: %d\n", line, r);
	printf("---------------------------------\n\n");
	free(line);
	r = get_next_line(fd, &line);
	printf("\n\n---------- MAIN OUTPUT ----------\n");
	printf("line: %s\nreturn: %d\n", line, r);
	printf("---------------------------------\n\n");
	free(line);
	r = get_next_line(fd, &line);
	printf("\n\n---------- MAIN OUTPUT ----------\n");
	printf("line: %s\nreturn: %d\n", line, r);
	printf("---------------------------------\n\n");
	free(line);
	r = get_next_line(fd, &line);
	printf("\n\n---------- MAIN OUTPUT ----------\n");
	printf("line: %s\nreturn: %d\n", line, r);
	printf("---------------------------------\n\n");
	free(line);
	close(fd);
	return (0);
}*/
