/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 14:00:10 by niduches          #+#    #+#             */
/*   Updated: 2019/12/17 14:59:15 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_char(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

static void	sort_env(t_env *env)
{
	size_t	i;
	char	c;

	c = 1;
	i = 1;
	while (c)
	{
		c = 0;
		while (i < env->nb_env)
		{
			if (!env->env[i - 1] && env->env[i])
			{
				c = 1;
				swap_char(&env->env[i - 1], &env->env[i]);
			}
			i++;
		}
	}
	i = 0;
	while (env->env[i])
		i++;
	env->nb_env = i;
}

int			ft_unset(size_t ac, char **av, t_env *env)
{
	size_t	i;
	char	**tmp;

	i = 0;
	while (i < ac)
		if ((tmp = get_env(env, av[i++])))
		{
			free(*tmp);
			*tmp = NULL;
		}
	sort_env(env);
	return (0);
}
