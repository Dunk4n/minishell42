/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nb_sep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 17:24:21 by niduches          #+#    #+#             */
/*   Updated: 2019/12/19 17:53:15 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t			is_sep(char *line)
{
	if (!ft_strncmp(line, "||", 2))
		return (2);
	if (!ft_strncmp(line, "&&", 2))
		return (2);
	if (!ft_strncmp(line, "(", 1))
		return (1);
	if (!ft_strncmp(line, ")", 1))
		return (1);
	return (0);
}

static size_t	pass_dcote(char *line)
{
	size_t	i;

	i = 1;
	while (line[i] && line[i] != '\"')
	{
		if (line[i] == '\\' && (line[i] == '\"' || line[i] == '\\'))
			i++;
		i++;
	}
	if (line[i] == '\"')
		i++;
	return (i);
}

size_t			pass_normal(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && !is_sep(line + i))
	{
		if (line[i] == '\\')
			i += (line[i + 1]) ? 2 : 1;
		else if (line[i] == '\"')
			i += pass_dcote(line + i);
		else if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
			if (line[i] == '\'')
				i++;
		}
		else
		{
			while (line[i] && line[i] != '\\' && line[i] != '\"' && line[i] !=
'\'' && !is_sep(line + i))
				i++;
		}
	}
	return (i);
}

int				is_only_space(char *line, size_t end)
{
	size_t	j;

	j = 0;
	while (j < end)
	{
		if (!in_str(line[j], " \t\n"))
			return (0);
		j++;
	}
	return (1);
}

int				get_nb_sep(char *line)
{
	size_t	nb;
	size_t	i;
	size_t	tmp;

	nb = 0;
	i = 0;
	while (line[i])
	{
		if ((tmp = is_sep(line + i)))
			i += tmp;
		else
		{
			tmp = pass_normal(line + i);
			if (is_only_space(line + i, tmp))
			{
				i += tmp;
				continue ;
			}
			i += tmp;
		}
		nb++;
	}
	return (nb);
}
