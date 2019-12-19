/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 18:58:40 by niduches          #+#    #+#             */
/*   Updated: 2019/12/19 02:16:35 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_nb(char const *s, char *in)
{
	int		nb;
	int		i;
	char	sep;

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
		if (s[i] == ';' && (i == 0 || s[i - 1] != '\\') && !*((short*)in) &&
!sep)
			sep = 1;
		if ((s[i] != ';' || (i > 0 && s[i - 1] == '\\')) && sep == 1)
		{
			sep = 0;
			nb++;
		}
		i++;
	}
	return (nb);
}

static char	*fill_in(char const *s, int *i, char *in)
{
	int		j;
	int		tmp;
	char	*line;

	while (s[*i] == ';' && (*i == 0 || s[*i - 1] != '\\') && !*((short*)in))
		(*i)++;
	j = 0;
	while (s[*i + j] && (s[*i + j] != ';' || (*i + j != 0 && s[*i + j - 1] ==
'\\') || *((short*)in)))
	{
		if (!in[1] && s[*i + j] == '\"' && (*i + j == 0 || s[*i + j - 1] !=
'\\'))
			in[0] = (in[0] == 0) ? 1 : 0;
		else if (s[*i + j] == '\'' && (*i + j == 0 || s[*i + j - 1] != '\\'))
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

char		**custom_split_instr(char const *str)
{
	int		i;
	int		word;
	int		nb;
	char	in[2];
	char	**array;

	nb = get_nb(str, in);
	if (!(array = malloc((nb + 1) * sizeof(char*))))
		return (NULL);
	i = 0;
	word = 0;
	*((short*)in) = 0;
	while (word < nb)
	{
		if (!(array[word++] = fill_in(str, &i, in)))
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
