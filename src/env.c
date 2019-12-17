/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 23:37:37 by niduches          #+#    #+#             */
/*   Updated: 2019/12/16 16:45:35 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

int		ft_env(size_t ac, char **av, t_env *env)
{
	size_t	i;

	if (!env || !env->env)
		return (1);
	(void)ac;
	(void)av;
	i = 0;
	while (env->env[i])
	{
		ft_putstr_fd(env->env[i++], 1);
		write(1, "\n", 1);
	}
	return (0);
}
