/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cal-hawa <cal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 11:30:32 by cal-hawa          #+#    #+#             */
/*   Updated: 2020/01/05 12:43:49 by cal-hawa         ###   ########.fr       */
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

static int			execute_command(char *cmd, int flag)
{
	char			*redirections[MAX_REDIRS];
	char			*arguments[MAX_ARGS];
	int				n;

	if ((n = parse_cmd(cmd, redirections, arguments)) < 0)
	{
		destroy(redirections, arguments);
		return (n);
	}
	if (flag & 0x1)
		n = (mpipeline(arguments, redirections, 0));
	else if (flag & 0x2)
		n = (mpipeline(arguments, redirections, 1));
	else
		n = (standalone(arguments, redirections));
	destroy(redirections, arguments);
	return (n);
}

int					execute_pipeline(char **commands)
{
	int				n;

	n = 0;
	while (commands[n])
	{
		if (commands[n + 1][0] == '|')
		{
			if (execute_command(commands[n], 0x1) < 0)
				return (-1);
			n += 2;
		}
		else
		{
			if (execute_command(commands[n], 0x2))
				return (-1);
			n++;
		}
	}
	return (1);
}

int					execute_standalone(char *command)
{
	return (execute_command(command, 0));
}
