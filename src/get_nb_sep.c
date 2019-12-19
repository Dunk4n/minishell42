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

static int		is_sep(char *line)
{
	if (!ft_strncmp(line, ">>", 2))
		return (2);
	if (!ft_strncmp(line, "||", 2))
		return (2);
	if (!ft_strncmp(line, "&&", 2))
		return (2);
	if (!ft_strncmp(line, ">", 1))
		return (1);
	if (!ft_strncmp(line, "<", 1))
		return (1);
	if (!ft_strncmp(line, "|", 1))
		return (1);
	return (0);
}

static size_t	pass_dcote(char *line)
{
	return (0);
}

static size_t	pass_cote(char *line)
{
	return (0);
}

static size_t	pass_normal(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && !is_sep(line + i))
	{
		if (line[i] == '\\')
		{
			if (line[++i])
				i++;
		}
		else if (line[i] == '\"')
			i += pass_dcote(line + i);
		else if (line[i] == '\'')
			i += pass_cote(line + i);
		else
		{
			while (line[i] && !is_sep(line + i))
				i++;
		}
	}
	return (i);
}

int				get_nb_sep(char *line)
{
	int		nb;
	int		tmp;
	size_t	i;

	printf("[%s]\n", line);
	nb = 0;
	i = 0;
	while (line[i])
	{
		if ((tmp = is_sep(line + i)))
			i += tmp;
		else
		{
			printf("normal\n");
			i += pass_normal(line + i);
		}
		printf("i = %zi\n", i);
		nb++;
	}
	return (nb);
}
