/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split_sep.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 17:21:30 by niduches          #+#    #+#             */
/*   Updated: 2019/12/19 17:46:33 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_len_sep(char *line, size_t *index)
{
	size_t	nb;

	if ((nb = is_sep(line)))
	{

	}
	else
	{
		nb = pass_normal(line);
		if (is_only_space(line, nb))
		{
			*index += nb;
			return (0);
		}
	}
	return (nb);
}

static char	*fill_in(char *line, size_t *index)
{
	char	*str;
	size_t	i;
	size_t	nb;

	while (!(nb = get_len_sep(line + *index, index)) && *line);
	if (!(str = malloc((nb + 1) * sizeof(char))))
		return (NULL);
	str[nb] = '\0';
	i = 0;
	while (i < nb)
	{
		str[i] = line[i + *index];
		i++;
	}
	*index += nb;
	return (str);
}

char		**custom_split_sep(char *line)
{
	size_t	i;
	int		word;
	int		nb;
	char	**array;

	nb = get_nb_sep(line);
	if (!(array = malloc((nb + 1) * sizeof(char*))))
		return (NULL);
	i = 0;
	word = 0;
	while (word < nb)
	{
		if (!(array[word] = fill_in(line, &i)))
		{
			while(--word >= 0)
				free(array[word]);
			free(array);
			return (NULL);
		}
		word++;
	}
	array[word] = NULL;
	return (array);
}
