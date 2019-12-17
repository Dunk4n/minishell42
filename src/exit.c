/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 20:53:45 by niduches          #+#    #+#             */
/*   Updated: 2019/12/16 18:31:20 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

int		ft_exit(size_t ac, char **av, t_env *env)
{
	size_t	i;

	if (av)
		write(1, "exit\n", 5);
	if (!env->env)
		exit(0);
	(void)ac;
	i = 0;
	while (env->env[i])
		free(env->env[i++]);
	free(env->env);
	exit(0);
}
