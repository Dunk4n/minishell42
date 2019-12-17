/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 12:29:40 by niduches          #+#    #+#             */
/*   Updated: 2019/10/21 13:19:05 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "printf.h"

static size_t	pass_flags(const char *str, char *flag)
{
	size_t	i;

	*flag = 0;
	if (!*str || *str != '%')
		return (0);
	i = 1;
	while (ft_isflag(str[i]) || (str[i] > '0' && str[i] <= '9'))
		i++;
	if (!ft_isconv(str[i]))
		return (i);
	*flag = 1;
	return (i + 1);
}

int				ft_printf(const char *str, ...)
{
	va_list	list;
	int		i;
	int		to_print;
	size_t	nb_print;
	char	flag;

	if (!str)
		return (0);
	i = 0;
	nb_print = 0;
	va_start(list, str);
	while (str[i] && to_print != -1)
	{
		to_print = 0;
		while (str[i + to_print] && str[i + to_print] != '%')
			to_print++;
		nb_print += ft_putnstr(str + i, to_print);
		i += to_print;
		to_print = pass_flags(str + i, &flag);
		if (flag)
			nb_print += ft_makeconv(str + i, &to_print, list, nb_print);
		i += to_print;
	}
	va_end(list);
	return ((to_print != -1) ? (int)nb_print : -1);
}
