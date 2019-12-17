/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 19:07:13 by niduches          #+#    #+#             */
/*   Updated: 2019/12/16 18:45:33 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "minishell.h"

int		main(int ac, char **av, char **arg_env)
{
	t_env	env;
	char	*line;

	if (ac != 1)
		return (0);
	(void)av;
	if (!((env = init(arg_env)).env))
		return (1);
	while (1)
	{
		write(1, "$> ", 3);
		if (!get_next_line(0, &line) && (!line || !line[0]))
			ft_exit(1, NULL, &env);
		//TODO line -> line with env variable
		get_all_instruction(line, &env);
	}
	return (0);
}
