/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 20:53:45 by niduches          #+#    #+#             */
/*   Updated: 2020/01/05 11:41:05 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

static int	ft_is_number(char *str)
{
	while (ft_isspace(*str))
		str++;
	while (ft_isdigit(*str))
		str++;
	return (*str == '\0');
}

void		free_env(t_env *env)
{
	int	i;

	i = 0;
	while (env->env[i])
		free(env->env[i++]);
	free(env->env);
	env->env = NULL;
	i = 0;
	while (i < env->size)
	{
		free(env->hist[i]);
		env->hist[i] = NULL;
	}
	env->size = 0;
}

int			ft_exit(size_t ac, char **av, t_env *env)
{
	int		ret;

	write(1, "exit\n", 5);
	if (!env->env)
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &(env->termios_save));
		exit(0);
	}
	if (ac > 2)
	{
		write(1, "bash: exit: too many arguments\n", 31);
		return (1);
	}
	if (av && *av && !ft_is_number(*av))
	{
		ft_printf("bash: exit: %s: numeric argument required\n", *av);
		return (1);
	}
	ret = 0;
	if (av && *av)
		ret = ft_atoi(*av);
	free_env(env);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &(env->termios_save));
	exit(ret);
}
