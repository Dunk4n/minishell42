/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 20:57:55 by niduches          #+#    #+#             */
/*   Updated: 2019/12/16 18:40:49 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

int		ft_echo(size_t ac, char **av, t_env *env)
{
	size_t	i;
	char	*tmp;

	if (!av)
		return (1);
	i = 0;
	(void)env;
	if (ac > 0 && !ft_strcmp(av[0], "-n"))
		i = 1;
	while (i < ac)
	{
		tmp = av[i];
		ft_putstr_fd(tmp, 1);
		if (++i < ac && tmp)
			write(1, " ", 1);
	}
	if (ac == 0 || ft_strcmp(av[0], "-n"))
		write(1, "\n", 1);
	return (0);
}
