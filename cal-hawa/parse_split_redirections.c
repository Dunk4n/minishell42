/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cal-hawa <cal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 15:45:27 by cal-hawa          #+#    #+#             */
/*   Updated: 2020/01/05 12:04:31 by cal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static char		*remove_redirection(char *str, char **redir, int i)
{
	char		c;

	c = str[i];
	str[i] = '\0';
	if (!(*redir = str_trim(str, ' ')))
		return (0);
	while (*str)
		*str++ = '\0';
	*str = c;
	return (str);
}

static int		duplicate_redirection(char *str, char **redir, int n)
{
	int			i;
	int			quote;

	i = n;
	quote = 0;
	if ((quote = process_quote(str[i], quote)))
	{
		i++;
		while ((quote = process_quote(str[i], quote)))
			i++;
		i++;
		if (!(str = remove_redirection(str, redir, i)))
			return (0);
		return (i);
	}
	while (str[i] == ' ')
		i++;
	while (str[i] && str[i] != '>' && \
		str[i] != '<' && str[i] != ' ')
		i++;
	if (!(str = remove_redirection(str, redir, i)))
		return (0);
	return (i);
}

static int		check_redirection(char *str, char redir)
{
	int			i;

	i = 0;
	while (str[i] == redir)
		i++;
	return (i <= 2 ? i : 0);
}

int				split_redirections(char *cmd, char **redirs)
{
	int			quote;
	int			n;
	int			nredirs;

	quote = 0;
	nredirs = 0;
	while (*cmd)
	{
		quote = process_quote(*cmd, quote);
		if (!quote && (*cmd == '<' || *cmd == '>'))
		{
			if (!(n = check_redirection(cmd, *cmd)))
				return (-1);
			if (!(n = duplicate_redirection(cmd, redirs + nredirs, n)))
				return (-1);
			cmd += n;
			nredirs++;
			if (nredirs == (MAX_REDIRS - 1))
				return (-1);
		}
		else
			cmd++;
	}
	redirs[nredirs] = 0;
	return (nredirs);
}
