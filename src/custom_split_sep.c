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
	int	nb;

	nb = get_nb_sep(line);
	printf("nb = %d\n", nb);
	return (NULL);
}
