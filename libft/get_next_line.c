/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:27:24 by niduches          #+#    #+#             */
/*   Updated: 2019/12/16 17:22:22 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static void	to_nl(char *buff)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < BUFFER_SIZE && buff[i] && buff[i] != '\n')
		i++;
	j = 0;
	while (j < BUFFER_SIZE && buff[j])
	{
		if (i + 1 < BUFFER_SIZE && buff[i + 1] != '\0')
			buff[j] = buff[1 + i++];
		else if (j < BUFFER_SIZE)
			buff[j] = '\0';
		j++;
	}
	while (j < BUFFER_SIZE)
		buff[j++] = '\0';
}

static int	put_in_buff(char *line, char *tmp, ssize_t size, char *buff)
{
	size_t	i;
	int		ret;

	i = 0;
	ret = 1;
	if (size <= 0)
		ret = 0;
	while (i < BUFFER_SIZE && buff[i])
	{
		line[i] = buff[i];
		i++;
	}
	i = 0;
	while (tmp[i] && i < BUFFER_SIZE)
	{
		buff[i] = tmp[i];
		i++;
	}
	while (i < BUFFER_SIZE)
		buff[i++] = '\0';
	return (ret);
}

#include <string.h>
static char	*next_line(int fd, char *buff, size_t nb, int *rt)
{
	char	tmp[BUFFER_SIZE];
	char	*line;
	ssize_t	i;
	ssize_t	size;

	size = read(fd, tmp, BUFFER_SIZE);
	(size >= BUFFER_SIZE) ? 0 : (tmp[size] = '\0');
	i = 0;
	while (i < size && tmp[i] && tmp[i] != '\n')
		i++;
	if ((i < BUFFER_SIZE && tmp[i] == '\n') || size < 0 || nb + size == 0)
	{
		if (!(line = malloc((nb + i + 1) * sizeof(char))))
			return (NULL);
		line[nb + i] = '\0';
		*rt = put_in_buff(line, tmp, nb + size, buff);
		while (i-- > 0)
			line[nb + i] = tmp[i];
		return (line);
	}
	if (!(line = next_line(fd, buff, nb + size, rt)))
		return (NULL);
	while (size-- > 0)
		line[nb + size] = tmp[size];
	return (line);
}

int			get_next_line(int fd, char **line)
{
	static char	buff[BUFFER_SIZE] = "";
	size_t		i;
	int			rt;

	if (fd < 0 || !line)
		return (0);
	*line = NULL;
	i = 0;
	rt = 1;
	while (i < BUFFER_SIZE && buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
	{
		if (!(*line = malloc((i + 1) * sizeof(char))))
			return (0);
		(*line)[i] = '\0';
		while (i-- > 0)
			(*line)[i] = buff[i];
	}
	else if (buff[i] != '\n' && !(*line = next_line(fd, buff, i, &rt)))
		return (0);
	to_nl(buff);
	return (rt);
}
