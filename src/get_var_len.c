/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 19:44:41 by niduches          #+#    #+#             */
/*   Updated: 2019/12/18 19:45:23 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_len_var_ret(size_t *idx, t_env *env)
{
	size_t	i;
	int		tmp;

	(*idx)++;
	tmp = env->ret;
	i = 0;
	if (tmp <= 0)
		i++;
	while (tmp)
	{
		tmp /= 10;
		i++;
	}
	return (i);
}

static size_t	env_len(char *env_var)
{
	size_t	i;

	i = 0;
	while (*env_var && *env_var != '=')
		env_var++;
	if (*env_var == '=')
		env_var++;
	while (env_var[i])
		i++;
	return (i);
}

size_t			get_var_len(char *line, size_t *idx, t_env *env)
{
	size_t	i;
	char	tmp;
	char	**env_var;

	(*idx)++;
	if (*line == '?')
		return (get_len_var_ret(idx, env));
	i = 0;
	while (line[i] && !ft_isspace(line[i]) && line[i] != '$' && line[i] !=
'\"' && line[i] != '\'')
		i++;
	if (!i)
		return (0);
	(*idx) += i;
	tmp = line[i];
	line[i] = '\0';
	if (!(env_var = get_env(env, line)))
	{
		line[i] = tmp;
		return (0);
	}
	line[i] = tmp;
	return (env_len(*env_var));
}
