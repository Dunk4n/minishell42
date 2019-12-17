/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 21:22:44 by niduches          #+#    #+#             */
/*   Updated: 2019/12/17 14:05:35 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	env_len(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

char			**get_env(t_env *env, char *to_find)
{
	size_t	i;
	size_t	tmp;

	if (!env->env || !to_find)
		return (NULL);
	i = 0;
	while (env->env[i])
	{
		if (!(tmp = env_len(env->env[i])))
			return (NULL);
		if (tmp != ft_strlen(to_find))
		{
			i++;
			continue ;
		}
		if (!(ft_strncmp(env->env[i], to_find, tmp)))
			return (&env->env[i]);
		i++;
	}
	return (NULL);
}
