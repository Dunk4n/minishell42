/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredocs_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cal-hawa <cal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 10:52:18 by cal-hawa          #+#    #+#             */
/*   Updated: 2020/01/14 08:32:47 by cal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include <unistd.h>
#include <signal.h>

static void		sighandler(int signal)
{
	if (signal == SIGINT)
		exit(1);
}

static int		prompt(char *word, int stdin, int pipefd[2])
{
	char		*line;
	int			rd;

	ft_printf("> ");
	while ((rd = get_next_line(stdin, &line)) >= 0)
	{
		if (rd == 0)
		{
			free(line);
			write(2, "warning: here-document delimited by end-of-file\n", 49);
			return (1);
		}
		if (ft_strcmp(line, word) == 0)
			break ;
		write(pipefd[1], line, ft_strlen(line));
		free(line);
		write(pipefd[1], "\n", 1);
		ft_printf("> ");
	}
	return (1);
}

int				here_doc(char *word, int stdin)
{
	int			pipefd[2];

	if (pipe(pipefd) < 0)
		return (-1);
	if (*word == '\0')
	{
		write(2, "syntax error\n", 13);
		return (-1);
	}
	if (signal(SIGINT, &sighandler) == SIG_ERR)
		return (-1);
	if (prompt(word, stdin, pipefd) < 0)
		return (-1);
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		return (-1);
	if (close(pipefd[1]) < 0)
		return (-1);
	if (dup2(pipefd[0], 0) < 0)
		return (-1);
	return (1);
}
