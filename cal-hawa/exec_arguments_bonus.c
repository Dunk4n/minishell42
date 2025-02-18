/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_arguments_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cal-hawa <cal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 14:59:14 by cal-hawa          #+#    #+#             */
/*   Updated: 2020/01/13 10:40:32 by cal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include "execute.h"

char			**set_arguments(char **args)
{
	glob_t		globbuf;
	int			i;

	i = 0;
	if (glob(args[i], GLOB_NOCHECK, 0, &globbuf))
		return (0);
	while (args[++i])
	{
		if (glob(args[i], GLOB_NOCHECK | GLOB_APPEND, 0, &globbuf))
		{
			globfree(&globbuf);
			return (0);
		}
	}
	i = 0;
	while (args[i])
		free(args[i++]);
	return (globbuf.gl_pathv);
}
