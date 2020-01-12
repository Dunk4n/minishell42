/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 19:50:01 by niduches          #+#    #+#             */
/*   Updated: 2020/01/12 18:52:46 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_tab(char **tab, size_t indice)
{
	if (indice > 0)
	{
		while (--indice > 0)
			free(tab[indice]);
	}
	free(tab);
}

static char	**copy_env(char **arg_env, size_t *nb_env)
{
	size_t	i;
	char	**env;

	i = 0;
	while (arg_env[i])
		i++;
	if (!(env = malloc((i + 1) * sizeof(char*))))
		return (NULL);
	env[i] = NULL;
	i = 0;
	while (arg_env[i])
	{
		if (!(env[i] = ft_strdup(arg_env[i])))
		{
			free_tab(env, i);
			return (NULL);
		}
		i++;
	}
	*nb_env = i;
	return (env);
}

t_env		init(char **arg_env)
{
	t_env	env;

	g_exit = 0;
	env.env = NULL;
	env.ret = 0;
	env.nb_env = 0;
	if (!(env.env = copy_env(arg_env, &env.nb_env)))
		return (env);
	return (env);
}
