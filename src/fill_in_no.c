/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_in_no.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 19:30:21 by niduches          #+#    #+#             */
/*   Updated: 2019/12/18 19:40:30 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_len_arg_no(char const *s, char *in, char *set, int *nb)
{
	int		j;
	int		tmp;

	tmp = *nb;
	*nb = 0;
	j = 0;
	while (s[j] && (!in_str(s[j], set) || *((short*)in)))
	{
		if (s[j] == '\"' && (tmp + j == 0 || s[j - 1] != '\\'))
			in[0] = (in[0] == 0) ? 1 : 0;
		else if (s[j] == '\'' && (tmp + j == 0 || s[j - 1] != '\\'))
			in[1] = (in[1] == 0) ? 1 : 0;
		else
			(*nb)++;
		j++;
	}
	return (j);
}

char		*fill_in_no(char const *s, int *i, char *in, char *set)
{
	int		j;
	int		k;
	int		tmp;
	char	*line;

	while (in_str(s[*i], set))
		(*i)++;
	k = *i;
	j = get_len_arg_no((char*)s + *i, in, set, &k);
	if (!(line = malloc((k + 1) * sizeof(char))))
		return (NULL);
	line[k--] = '\0';
	tmp = j;
	while (--j >= 0)
	{
		line[k] = s[*i + j];
		if (!((s[*i + j] == '\"' || s[*i + j] == '\'') &&
(*i + j == 0 || s[*i + j - 1] != '\\')))
			k--;
	}
	*i += tmp;
	return (line);
}
