/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_standalone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cal-hawa <cal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:22:57 by cal-hawa          #+#    #+#             */
/*   Updated: 2020/01/09 10:36:15 by cal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "minishell.h"
#include "execute.h"

static int		parent_process(pid_t child_pid, t_env *env)
{
	int			wstatus;

	if (waitpid(child_pid, &wstatus, 0) < 0)
		return (-1);
	if (WIFEXITED(wstatus))
		env->ret = WEXITSTATUS(wstatus);
	return (1);
}

static void		child_process(char **argv, char **redirs, t_env *env)
{
	char	path[PATH_MAX + 1];

	if (set_redirections(redirs) < 0)
		exit(1);
	get_exec_path(path, argv[0], env);
	if (!path[0])
		exit(1);
	if (execve(path, argv, env->env) < 0)
		exit(1);
}

int				standalone(char **arguments, char **redirections, t_env *env)
{
	pid_t		pid;

	pid = fork();
	if (pid == 0)
		child_process(arguments, redirections, env);
	else if (pid > 0)
		return (parent_process(pid, env));
	return (-1);
}
