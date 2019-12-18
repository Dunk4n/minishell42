/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 18:58:40 by niduches          #+#    #+#             */
/*   Updated: 2019/12/18 19:44:35 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			in_str(char c, char const *charset)
{
	size_t	i;

	i = 0;
	while (charset[i])
		if (charset[i++] == c)
			return (1);
	return (0);
}

static int	get_nb(char const *s, char *set)
{
	int		nb;
	int		i;
	char	sep;
	char	in[2];

	*((short*)in) = 0;
	sep = 1;
	nb = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] == '\"') && (i == 0 || s[i - 1] != '\\'))
			in[0] = (in[0] == 0) ? 1 : 0;
		if ((s[i] == '\'') && (i == 0 || s[i - 1] != '\\'))
			in[1] = (in[1] == 0) ? 1 : 0;
		if (in_str(s[i], set) && !*((short*)in) && !sep)
			sep = 1;
		if (!in_str(s[i], set) && sep == 1)
		{
			sep = 0;
			nb++;
		}
		i++;
	}
	return (nb);
}

static char	*fill_in(char const *s, int *i, char *in, char *set)
{
	int		j;
	int		tmp;
	char	*line;

	while (in_str(s[*i], set))
		(*i)++;
	j = 0;
	while (s[*i + j] && (!in_str(s[*i + j], set) || *((short*)in)))
	{
		if ((s[*i + j] == '\"') && (*i + j == 0 || s[*i + j - 1] != '\\'))
			in[0] = (in[0] == 0) ? 1 : 0;
		else if ((s[*i + j] == '\'') && (*i + j == 0 || s[*i + j - 1] != '\\'))
			in[1] = (in[1] == 0) ? 1 : 0;
		j++;
	}
	if (!(line = malloc((j + 1) * sizeof(char))))
		return (NULL);
	line[j] = '\0';
	tmp = j;
	while (--j >= 0)
		line[j] = s[*i + j];
	*i += tmp;
	return (line);
}

char		**custom_split(char const *str, char *set, char aptf)
{
	int		i;
	int		word;
	int		nb;
	char	in[2];
	char	**array;

	nb = get_nb(str, set);
	if (!(array = malloc((nb + 1) * sizeof(char*))))
		return (NULL);
	i = 0;
	word = 0;
	*((short*)in) = 0;
	while (word < nb)
	{
		if (!(array[word++] = (aptf) ?
fill_in(str, &i, in, set) : fill_in_no(str, &i, in, set)))
		{
			while (--word - 1 >= 0)
				free(array[word - 1]);
			free(array);
			return (NULL);
		}
	}
	array[word] = NULL;
	return (array);
}
