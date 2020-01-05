/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mpipeline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cal-hawa <cal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 08:55:04 by cal-hawa          #+#    #+#             */
/*   Updated: 2020/01/05 12:00:42 by cal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

static int		parent_process(pid_t child_pid, int nw_in, int nw_out)
{
	int			wstatus;

	if (waitpid(child_pid, &wstatus, 0) < 0)
		return (-1);
	if (WIFEXITED(wstatus))
		g_exit_status = WEXITSTATUS(wstatus);
	if (nw_in > 2 && close(nw_in) < 0)
		return (-1);
	if (nw_out > 2 && close(nw_out) < 0)
		return (-1);
	return (1);
}

static void		child_process(char **args, char **redirs, int nw_in, int nw_out)
{
	if (dup2(nw_in, 0) < 0)
		exit(1);
	if (dup2(nw_out, 1) < 0)
		exit(1);
	if (set_redirections(redirs) < 0)
		exit(1);
	if (execve(args[0], args, g_envp) < 0)
		exit(1);
}

static int		fork_process(char **args, char **redirs, int nw_in, int nw_out)
{
	pid_t		pid;

	pid = fork();
	if (pid == 0)
		child_process(args, redirs, nw_in, nw_out);
	else if (pid > 0)
		return (parent_process(pid, nw_in, nw_out));
	return (-1);
}

int				mpipeline(char **args, char **redirs, int last)
{
	static int	pipe_n = 0;
	static int	pipefd[4];
	static int	in = 0;
	int			nw_in;
	int			nw_out;

	if (last)
	{
		nw_in = in;
		nw_out = 1;
		in = 0;
	}
	else
	{
		if (pipe(pipefd + pipe_n) < 0)
			return (-1);
		nw_in = in;
		nw_out = pipefd[pipe_n + 1];
		in = pipefd[pipe_n + 0];
		pipe_n = (pipe_n == 0) ? 2 : 0;
	}
	return (fork_process(args, redirs, nw_in, nw_out));
}
