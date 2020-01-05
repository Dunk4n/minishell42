/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standalone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cal-hawa <cal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:22:57 by cal-hawa          #+#    #+#             */
/*   Updated: 2020/01/05 12:24:37 by cal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

static int		parent_process(pid_t child_pid)
{
	int			wstatus;

	if (waitpid(child_pid, &wstatus, 0) < 0)
		return (-1);
	if (WIFEXITED(wstatus))
		g_exit_status = WEXITSTATUS(wstatus);
	return (1);
}

static void		child_process(char **argv, char **redirs)
{
	if (set_redirections(redirs) < 0)
		exit(1);
	if (execve(argv[0], argv, redirs) < 0)
		exit(1);
}

int				standalone(char **arguments, char **redirections)
{
	pid_t		pid;

	pid = fork();
	if (pid == 0)
		child_process(arguments, redirections);
	else if (pid > 0)
		return (parent_process(pid));
	return (-1);
}
