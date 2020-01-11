/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_mpipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cal-hawa <cal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 08:55:04 by cal-hawa          #+#    #+#             */
/*   Updated: 2020/01/11 16:43:11 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include "minishell.h"
#include "execute.h"
#include "built_in.h"

static int		parent_process(pid_t child_pid, int nw_in, int nw_out, t_env *env)
{
	int			wstatus;

	if (waitpid(child_pid, &wstatus, 0) < 0)
		return (-1);
	if (WIFEXITED(wstatus))
		env->ret = WEXITSTATUS(wstatus);
	if (nw_in > 2 && close(nw_in) < 0)
		return (-1);
	if (nw_out > 2 && close(nw_out) < 0)
		return (-1);
	return (1);
}

static void		child_process(char **args, char **redirs, int *nw, t_env *env)
{
	char	path[PATH_MAX + 1];

	if (dup2(nw[0], 0) < 0)
		exit(1);
	if (dup2(nw[1], 1) < 0)
		exit(1);
	if (set_redirections(redirs, env) < 0)
		exit(1);
	if (!(args = set_arguments(args)))
		exit(1);
	if (!(is_built_in(args[0])))
	{
		get_exec_path(path, args[0], env);
		if (!path[0])
		{
			write(2, args[0], ft_strlen(args[0]));
			write(2, ": command not found\n", 20);
			exit(1);
		}
		args[0] = path;
	}
	if (execve_wrapper(args, env) < 0)
		exit(1);
}

static int		fork_process(char **args, char **redirs, int *nw, t_env *env)
{
	pid_t		pid;

	pid = fork();
	if (pid == 0)
		child_process(args, redirs, nw, env);
	else if (pid > 0)
		return (parent_process(pid, nw[0], nw[1], env));
	return (-1);
}

int				mpipeline(char **args, char **redirs, int last, t_env *env)
{
	static int	pipe_n = 0;
	static int	pipefd[4];
	static int	in = 0;
	int			nw[2];

	if (last)
	{
		nw[0] = in;
		nw[1] = 1;
		in = 0;
	}
	else
	{
		if (pipe(pipefd + pipe_n) < 0)
			return (-1);
		nw[0] = in;
		nw[1] = pipefd[pipe_n + 1];
		in = pipefd[pipe_n + 0];
		pipe_n = (pipe_n == 0) ? 2 : 0;
	}
	return (fork_process(args, redirs, nw, env));
}
