/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cal-hawa <cal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 12:18:32 by cal-hawa          #+#    #+#             */
/*   Updated: 2020/01/05 12:43:28 by cal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void		initialize(char **redirs, char **args)
{
	int			n;

	n = MAX_REDIRS;
	while (n--)
		redirs[n] = 0;
	n = MAX_ARGS;
	while (n--)
		args[n] = 0;
}

int				parse_cmd(char *cmd, char **redirs, char **args)
{
	int			cmd_len;
	int			nredirs;
	int			nargs;

	initialize(redirs, args);
	cmd_len = 0;
	while (cmd[cmd_len])
		cmd_len++;
	if ((nredirs = split_redirections(cmd, redirs)) < 0)
		return (nredirs);
	if ((nargs = split_arguments(cmd, cmd_len, args) < 0))
		return (nargs);
	return (1);
}
