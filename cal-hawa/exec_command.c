/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cal-hawa <cal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 11:30:32 by cal-hawa          #+#    #+#             */
/*   Updated: 2020/01/14 08:33:59 by cal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include <stdlib.h>

static void		destroy(char **redirs, char **args)
{
	int			n;

	n = 0;
	while (redirs[n])
	{
		free(redirs[n]);
		n++;
	}
	n = 0;
	while (args[n])
	{
		free(args[n]);
		n++;
	}
}

static int		execute_command(char *cmd, int flag, t_env *env)
{
	char		*redirections[MAX_REDIRS];
	char		*arguments[MAX_ARGS];
	int			n;
	int			i;

	if ((n = parse_cmd(cmd, redirections, arguments)) < 0)
	{
		destroy(redirections, arguments);
		return (n);
	}
	i = 0;
	while (redirections[i])
		i++;
	i = 0;
	while (arguments[i])
		i++;
	if (flag & 0x1)
		n = (mpipeline(arguments, redirections, 0, env));
	else if (flag & 0x2)
		n = (mpipeline(arguments, redirections, 1, env));
	else
		n = (standalone(arguments, redirections, env));
	destroy(redirections, arguments);
	return (n);
}

int				execute_pipeline(char **commands, t_env *env)
{
	int			n;

	n = 0;
	while (commands[n])
	{
		if (commands[n + 1] && commands[n + 1][0] == '|')
		{
			if (execute_command(commands[n], 0x1, env) < 0)
				return (-1);
			n += 2;
		}
		else
		{
			if (execute_command(commands[n], 0x2, env))
				return (-1);
			n++;
		}
	}
	return (1);
}

int				execute_standalone(char *command, t_env *env)
{
	return (execute_command(command, 0, env));
}
