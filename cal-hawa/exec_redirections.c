/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cal-hawa <cal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 11:20:40 by cal-hawa          #+#    #+#             */
/*   Updated: 2020/01/09 17:47:05 by cal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "execute.h"

static char		*set_filename(char *file, int *oflag)
{
	char		*file_name;
	char		redir;
	char		quote;
	int			i;

	i = 0;
	redir = file[i];
	while (file[i] == redir || file[i] == ' ')
		i++;
	if (file[i] != '\"' && file[i] != '\'')
		file_name = file + i;
	else
	{
		quote = file[i++];
		file_name = file + i;
		while (file[i] != quote)
			i++;
		file[i] = '\0';
	}
	if (redir == '<')
		*oflag = ft_strncmp(file, "<<", 2) ? O_RDONLY : -1;
	else
		*oflag = (ft_strncmp(file, ">>", 2)) ? O_WRONLY | O_CREAT | O_TRUNC :
O_WRONLY | O_CREAT | O_APPEND;
	return (file_name);
}

static int		redirect_output(char *file_name, int oflag)
{
	int			fd;

	if ((fd = open(file_name, oflag, 0664)) < 0)
		return (-1);
	if (dup2(fd, 1) < 0)
		return (-1);
	return (1);
}

static int		here_doc(char *word, int stdin)
{
	char		*line;
	int			pipefd[2];

	if (pipe(pipefd) < 0)
		return (-1);
	ft_printf("> ");
	while (get_next_line(stdin, &line))
	{
		if (ft_strcmp(line, word) == 0)
			break;
		write(pipefd[1], line, ft_strlen(line));
		free(line);
		write(pipefd[1], "\n", 1);
		ft_printf("> ");
	}
	if (close(pipefd[1]) < 0)
		return (-1);
	if (dup2(pipefd[0], 0) < 0)
		return (-1);
	return (1);
}

static int		redirect_intput(char *file_name, int oflag, int stdin)
{
	int			fd;

	if (oflag == -1)
		return (here_doc(file_name, stdin));
	if ((fd = open(file_name, oflag)) < 0)
		return (-1);
	if (dup2(fd, 0) < 0)
		return (-1);
	return (1);
}

int				set_redirections(char **redirs)
{
	int			i;
	char		*file_name;
	int			oflag;
	int			fd;
	int			stdin;

	if ((stdin = dup(0)) < 0)
		return (-1);
	i = 0;
	while (redirs[i])
	{
		file_name = set_filename(redirs[i], &oflag);
		if (oflag == O_RDONLY || oflag == -1)
			fd = redirect_intput(file_name, oflag, stdin);
		else
			fd = redirect_output(file_name, oflag);
		if (fd < 0)
			return (fd);
		i++;
	}
	return (1);
}
