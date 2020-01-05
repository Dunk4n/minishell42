/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_trim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cal-hawa <cal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 16:41:25 by cal-hawa          #+#    #+#             */
/*   Updated: 2020/01/05 12:04:38 by cal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char			*str_trim(char *str, char c)
{
	char		*trimed;
	int			min;
	int			max;
	int			len;

	min = 0;
	while (str[min] && str[min] == c)
		min++;
	max = min;
	while (str[max])
		max++;
	max--;
	while ((min < max) && str[max] == c)
		max--;
	len = (max - min) + 1;
	if (!(trimed = malloc((len + 1) * sizeof(char))))
		return (0);
	trimed[len] = '\0';
	while (len--)
		trimed[len] = str[min + len];
	return (trimed);
}
