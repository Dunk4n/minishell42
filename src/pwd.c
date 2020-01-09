/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cal-hawa <cal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 23:41:58 by niduches          #+#    #+#             */
/*   Updated: 2020/01/09 18:10:02 by cal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include "minishell.h"

int		ft_pwd(size_t ac, char **av, t_env *env)
{
	char	buff[PATH_MAX + 1];

	if (!env)
		return (1);
	(void)ac;
	(void)av;
	if (getcwd(buff, sizeof(buff)))
	{
		ft_putstr_fd(buff, 1);
		write(1, "\n", 1);
	}
	else
		return (1);
	return (0);
}
