/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cal-hawa <cal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 11:20:40 by cal-hawa          #+#    #+#             */
/*   Updated: 2020/01/08 14:59:10 by cal-hawa         ###   ########.fr       */
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
		*oflag = O_RDONLY;
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

static int		redirect_intput(char *file_name, int oflag)
{

	int			fd;

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

	i = 0;
	if (!redirs[i])
		return (1);
	while (redirs[i + 1])
	{
		file_name = set_filename(redirs[i], &oflag);
		if ((fd = open(file_name, oflag, 0664)) < 0)
			return (-1);
		i++;
	}
	file_name = set_filename(redirs[i], &oflag);
	if (oflag == O_RDONLY)
		return (redirect_intput(file_name, oflag));
	else
		return (redirect_output(file_name, oflag));
	return (1);
}
