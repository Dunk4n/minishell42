/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_arguments_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cal-hawa <cal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 14:59:14 by cal-hawa          #+#    #+#             */
/*   Updated: 2020/01/11 17:31:10 by cal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include "execute.h"

char			**set_arguments(char **args)
{
	glob_t		globbuf;
	int			i;

	globbuf.gl_offs = 1;
	i = 1;
	if (args[i] == 0)
		return (args);
	if (glob(args[i], GLOB_DOOFFS | GLOB_NOCHECK, 0, &globbuf))
		return (0);
	while (args[++i])
	{
		if (glob(args[i], GLOB_DOOFFS | GLOB_NOCHECK \
					| GLOB_APPEND, 0, &globbuf))
		{
			globfree(&globbuf);
			return (0);
		}
	}
	globbuf.gl_pathv[0] = args[0];
	i = 1;
	while (args[i])
		free(args[i++]);
	return (globbuf.gl_pathv);
}
