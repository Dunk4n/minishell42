/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 09:54:48 by niduches          #+#    #+#             */
/*   Updated: 2020/01/05 09:54:49 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include "minishell.h"

static void	display_error(char **av, int wst)
{
    if (!WIFSIGNALED(wst))
        return ;
    if (WTERMSIG(wst) == 8) {
        ft_putstr_fd("Floating exception\n", 1);
        return ;
    }
    if (WTERMSIG(wst) == 11) {
        ft_putstr_fd("Segmentation fault\n", 1);
        return ;
    }
    ft_printf("%s: ERROR.\n", av[0]);
}

static int	make_fork(char *path, char **av, t_env *env)
{
	int	id;
	int	w;
	int	wst;

	w = 0;
	wst = 0;
	if ((id = fork()) == -1)
		return (-1);
	if (id == 0)
	{
		execve(path, av, env->env);
		if (errno == ENOEXEC)
			ft_printf("%s: Exec format error. Wrong Architecture.\n", av[0]);
		exit(0);
	}
	else
	{
		while (wst == 0 && w != -1)
		{
			w = waitpid(id, &wst, WUNTRACED | WCONTINUED);
			display_error(av, wst);
		}
	}
	return (wst);
}

int			exec_bin(char **av, t_env *env)
{
	char	path[PATH_MAX + 1];

	if (!av || !av[0] || !av[0][0])
		return (0);
	get_exec_path(path, av[0], env);
	if (!av[0][0])
	{
		ft_printf("bash: %s: command not found\n", av[0]);
		return (0);
	}
	return (make_fork(path, av, env));
}
