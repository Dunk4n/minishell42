/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_standalone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cal-hawa <cal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:22:57 by cal-hawa          #+#    #+#             */
/*   Updated: 2020/01/12 17:35:20 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "minishell.h"
#include "execute.h"
#include "built_in.h"

static int		parent_process(char **args, t_env *env, pid_t child_pid)
{
	int			wstatus;

	if (waitpid(child_pid, &wstatus, 0) < 0)
		return (-1);
	if (WIFEXITED(wstatus))
		env->ret = WEXITSTATUS(wstatus);
	if (is_built_in(args[0]) < 0)
		launch_built_in(args, env);
	return (1);
}

static void		child_process(char **argv, char **redirs, t_env *env)
{
	char	path[PATH_MAX + 1];

	if (set_redirections(redirs, env) < 0)
		exit(1);
	if (!(argv = set_arguments(argv)))
		exit(1);
	if (is_built_in(argv[0]) == 0)
	{
		get_exec_path(path, argv[0], env);
		if (!path[0])
		{
			write(2, argv[0], ft_strlen(argv[0]));
			write(2, ": command not found\n", 20);
			exit(127);
		}
		argv[0] = path;
	}
	if (execve_wrapper(argv, env) < 0)
		exit(1);
}

int				standalone(char **arguments, char **redirections, t_env *env)
{
	pid_t		pid;

	pid = fork();
	if (pid == 0)
		child_process(arguments, redirections, env);
	else if (pid > 0)
		return (parent_process(arguments, env, pid));
	return (-1);
}
