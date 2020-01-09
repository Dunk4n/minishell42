/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cal-hawa <cal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 09:45:26 by niduches          #+#    #+#             */
/*   Updated: 2020/01/09 14:38:56 by cal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <unistd.h>
#include "minishell.h"

static int	get_home(size_t ac, char **av, char *path, t_env *env)
{
	char	*home;

	path[0] = '\0';
	if (ac != 0 && !(av[0][0] == '~' && (av[0][1] == '/' || !av[0][1])))
		return (1);
	if (!(home = (char*)get_env(env, "HOME")))
		return (0);
	home = *((char**)home);
	while (*home && *home != '=')
		home++;
	if (*home)
		home++;
	ft_strcpy(path, home);
	return (1);
}

int			ft_cd(size_t ac, char **av, t_env *env)
{
	char	path[PATH_MAX + 1];

	if (ac > 1)
		return (0);
	if (!get_home(ac, av, path, env))
		return (0);
	if (ac != 0)
	{
		if (av[0][0] == '~' && (av[0][1] == '/' || !av[0][1]))
			ft_strcat(path, "/");
		ft_strcat(path, av[0] + ((av[0][0] == '~' && (av[0][1] == '/' ||
!av[0][1])) ? 1 : 0));
	}
	if (chdir((const char*)path) == -1)
	{
		ft_printf("cd: no such file or directory: %s\n", av[0]);
		return (1);
	}
	return (0);
}
