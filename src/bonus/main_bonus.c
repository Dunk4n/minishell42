/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 13:41:06 by niduches          #+#    #+#             */
/*   Updated: 2020/01/09 14:12:59 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include "minishell_bonus.h"

void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n$> ", 4);
		g_exit = 1;
	}
	else if (signal == SIGQUIT)
		return ;
}

int		main(int ac, char **av, char **arg_env)
{
	t_env	env;
	char	*line;

	if (ac != 1 || signal(SIGINT, &sig_handler) == SIG_ERR || \
signal(SIGQUIT, &sig_handler) == SIG_ERR || !((env = init(arg_env)).env))
		return (0);
	(void)av;
	while (1)
	{
		g_exit = 0;
		line = NULL;
		if ((!get_edit_line(&env, &line) || !line))
		{
			free(line);
			ft_exit(0, NULL, &env);
		}
		if (!(line = to_line_env(line, &env)))
		{
			free_env(&env);
			return (0);
		}
		get_all_instruction(line, &env);
		add_in_history(&env, line);
	}
	return (env.ret);
}
