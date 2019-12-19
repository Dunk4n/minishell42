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

char	**custom_split_sep(char *line)
{
	int		i;
	int		word;
	int		nb;
	char	**array;

	nb = get_nb_sep(line);
	if (!(array = malloc((nb + 1) sizeof(char*))))
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
