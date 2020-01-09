/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cal-hawa <cal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 19:07:13 by niduches          #+#    #+#             */
/*   Updated: 2020/01/09 14:05:47 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include "minishell.h"

void	sig_handler(int signal)
{
	if (signal == SIGINT)
		write(1, "\n$> ", 4);
	else if (signal == SIGQUIT)
		return ;
}

int		main(int ac, char **av, char **arg_env)
{
	t_env	env;
	char	*line;

	if (ac != 1)
		return (0);
	(void)av;
	if (signal(SIGINT, &sig_handler) == SIG_ERR || \
		signal(SIGQUIT, &sig_handler) == SIG_ERR)
		return (1);
	if (!((env = init(arg_env)).env))
		return (1);
	while (1)
	{
		write(1, "$> ", 3);
		if (!get_next_line(0, &line) && (!line || !line[0]))
		{
			free(line);
			ft_exit(0, NULL, &env);
		}
		if (!(line = to_line_env(line, &env)))
			free_env(&env);
		get_all_instruction(line, &env);
		free(line);
	}
	return (env.ret);
}
