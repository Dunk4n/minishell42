/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:14:22 by niduches          #+#    #+#             */
/*   Updated: 2020/01/12 17:45:32 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	good_arg(char *str, t_env *env, int same)
{
	size_t	i;
	char	**tmp;
	char	*tmp2;

	i = 0;
	while (str[i] && str[i] != '=')
		if (ft_isspace(str[i++]))
			return (0);
	if (!i || str[i] != '=')
		return (0);
	str[i] = '\0';
	if ((tmp = get_env(env, str)))
	{
		str[i] = '=';
		tmp2 = *tmp;
		if (same)
			(!(*tmp = ft_strdup(str))) ?
*tmp = tmp2 : free(tmp2);
		return (0);
	}
	str[i] = '=';
	return (1);
}

static char	**get_new_env(int *nb, size_t ac, char **av, t_env *env)
{
	char	**new_env;
	size_t	i;

	*nb = 0;
	i = 0;
	while (i < ac)
		if (good_arg(av[i++], env, 1))
			(*nb)++;
	if (!(new_env = malloc((env->nb_env + *nb + 1) * sizeof(char*))))
		return (NULL);
	return (new_env);
}

static int	put_new_in_env(char **av, char **new_env, size_t index, t_env *env)
{
	size_t	i;
	size_t	tmp;

	tmp = index;
	i = 0;
	while (av[i])
	{
		if (good_arg(av[i], env, 0))
		{
			if (!(new_env[index] = ft_strdup(av[i])))
			{
				while (--index >= tmp)
					free(new_env[index]);
				free(new_env);
				return (0);
			}
			index++;
		}
		i++;
	}
	return (1);
}

int			ft_export(size_t ac, char **av, t_env *env)
{
	size_t	i;
	int		nb;
	char	**new_env;

	if (ac == 0)
		return (0);
	if (!(new_env = get_new_env(&nb, ac, av, env)))
		return (-1);
	new_env[env->nb_env + nb] = NULL;
	i = 0;
	while (i < (size_t)env->nb_env)
	{
		new_env[i] = env->env[i];
		i++;
	}
	if (!put_new_in_env(av, new_env, i, env))
		return (-1);
	env->nb_env += nb;
	free(env->env);
	env->env = new_env;
	return (0);
}
