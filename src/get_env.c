/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 21:22:44 by niduches          #+#    #+#             */
/*   Updated: 2020/01/11 16:14:04 by niduches         ###   ########.fr       */
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

int				good_logic_syntax(char **inst)
{
	size_t	i;
	int		nb;

	nb = 0;
	i = 0;
	while (inst[i] && nb >= 0)
	{
		if (!ft_strcmp("(", inst[i]) || !ft_strcmp(")", inst[i]))
		{
			if ((!ft_strcmp("(", inst[i]) && inst[i + 1] && !ft_strcmp(")",
inst[i + 1])) || (!ft_strcmp(")", inst[i]) && i > 0 && !ft_strcmp("(",
inst[i - 1])))
				return (0);
			nb += (!ft_strcmp("(", inst[i])) ? 1 : -1;
		}
		else if (!ft_strcmp("&&", inst[i]) || !ft_strcmp("||", inst[i]))
		{
			if (i == 0 || !ft_strcmp("(", inst[i - 1]) || !ft_strcmp("&&",
inst[i - 1]) || !ft_strcmp("||", inst[i - 1]) || !inst[i + 1] || !ft_strcmp(")",
inst[i + 1]) || !ft_strcmp("&&", inst[i + 1]) || !ft_strcmp("||", inst[i + 1]))
				return (0);
		}
		i++;
	}
	return (!nb);
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
