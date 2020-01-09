/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_wrapper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cal-hawa <cal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 14:19:31 by cal-hawa          #+#    #+#             */
/*   Updated: 2020/01/09 18:12:37 by cal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include <unistd.h>

static void		launch_regular_bltin(char **argv, t_env *env, int n)
{
	int			argc;

	argc = 0;
	while (argv[argc])
		argc++;
	if (n == 1)
		ft_echo(argc, argv, env);
	else if (n == 2)
		ft_env(argc, argv, env);
	else if (n == 3)
		ft_pwd(argc, argv, env);
	exit(env->ret);
}

int				execve_wrapper(char **argv, t_env *env)
{
	int			n;

	n = is_built_in(argv[0]);
	if (n > 0)
		launch_regular_bltin(argv, env, n);
	else if (n == 0)
		execve(argv[0], argv, env->env);
	return (-1);
}
