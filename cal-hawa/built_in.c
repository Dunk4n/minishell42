/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cal-hawa <cal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 14:17:03 by cal-hawa          #+#    #+#             */
/*   Updated: 2020/01/09 19:48:04 by cal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int				is_built_in(char *filename)
{
	if (ft_strcmp(filename, "echo") == 0)
		return (1);
	else if (ft_strcmp(filename, "env") == 0)
		return (2);
	else if (ft_strcmp(filename, "pwd") == 0)
		return (3);
	else if (ft_strcmp(filename, "cd") == 0)
		return (-1);
	else if (ft_strcmp(filename, "export") == 0)
		return (-1);
	else if (ft_strcmp(filename, "unset") == 0)
		return (-1);
	else if (ft_strcmp(filename, "exit") == 0)
		return (-1);
	return (0);
}

int				launch_built_in(char **argv, t_env *env)
{
	int			argc;
	int			n;
	char		*blt;

	blt = *argv++;
	argc = 0;
	while (argv[argc])
		argc++;
	n = -1;
	if (ft_strcmp(blt, "cd") == 0 && (n = 1))
		ft_cd(argc, argv, env);
	else if (ft_strcmp(blt, "export") == 0 && (n = 1))
		ft_export(argc, argv, env);
	else if (ft_strcmp(blt, "unset") == 0 && (n = 1))
		ft_unset(argc, argv, env);
	else if (ft_strcmp(blt, "exit") == 0 && (n = 1))
		ft_exit(argc, argv, env);
	return (n);
}
