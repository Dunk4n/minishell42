/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split_arguments.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cal-hawa <cal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 15:54:14 by cal-hawa          #+#    #+#             */
/*   Updated: 2020/01/14 08:33:27 by cal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int		quoted_argument(char *str, char **args, int nargs, int quote)
{
	char		*dup;
	char		c;

	dup = ++str;
	while (*str && (quote = process_quote(*str, quote)))
		str++;
	c = *str;
	*str = '\0';
	if (!(args[nargs] = str_trim(dup, ' ')))
		return (-1);
	nargs++;
	*str = c;
	if (!*str)
		return (split_args(str, args, nargs));
	return (split_args(str + 1, args, nargs));
}

static int		argument(char *str, char **args, int nargs, int quote)
{
	char		*dup;
	char		c;

	dup = str;
	while (*str && *str != ' ' && !(quote = process_quote(*str, quote)))
		str++;
	c = *str;
	*str = '\0';
	if (!(args[nargs] = str_trim(dup, ' ')))
		return (-1);
	nargs++;
	*str = c;
	return (split_args(str, args, nargs));
}

int				split_args(char *str, char **args, int nargs)
{
	int			quote;

	quote = 0;
	if (nargs == (MAX_ARGS - 1))
		return (-2);
	while (*str == ' ')
		str++;
	if (*str == '\0')
		return (nargs);
	if ((quote = process_quote(*str, quote)))
		return (quoted_argument(str, args, nargs, quote));
	else
		return (argument(str, args, nargs, quote));
}

int				split_arguments(char *cmd, int cmd_len, char **args)
{
	int			i;
	int			nargs;

	i = 0;
	nargs = 0;
	while (i < cmd_len)
	{
		if (cmd[i])
		{
			if ((nargs = split_args(cmd + i, args, nargs)) < 0)
				return (nargs);
			while (cmd[i])
				i++;
		}
		else
			i++;
	}
	args[nargs] = 0;
	return (nargs);
}
