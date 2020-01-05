/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cal-hawa <cal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 10:32:57 by cal-hawa          #+#    #+#             */
/*   Updated: 2020/01/05 11:37:54 by cal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int		is_quote(int c)
{
	if (c == '\"' || c == '\'')
		return (c);
	return (0);
}

static int		match_quote(int c, int quote)
{
	return (quote == c ? 0 : quote);
}

int				process_quote(int c, int quote)
{
	if (!quote)
		quote = is_quote(c);
	else
		quote = match_quote(c, quote);
	return (quote);
}
