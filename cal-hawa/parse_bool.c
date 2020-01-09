/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cal-hawa <cal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 19:54:38 by cal-hawa          #+#    #+#             */
/*   Updated: 2020/01/09 20:19:50 by cal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char			*ft_strndup(const char *s, int n)
{
	char			*dup;

	if (!(dup = malloc((n + 1) * sizeof(char))))
		return (0);
	dup[n] = '\0';
	while (n--)
		dup[n] = s[n];
	return (dup);
}

static char			*iter_bool(char *str)
{
	int				stack;
	char			*cpy;

	stack = 0;
	while (*str)
	{
		if (*str == '(')
		{
			stack++;
			cpy = str;
		}
		else if (*str == ')')
		{
			stack--;
			if (stack == 0)
				return (ft_strndup(cpy, str - cpy));
			else if (stack < 0)
				return (0);
		}
		str++;
	}
	return (str);
}

char				*parse_bool(char *str)
{
	char			*ret;

	ret = iter_bool(str);
	if (ret == str || ret == 0)
		return (0);

}
