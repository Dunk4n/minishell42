/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 18:58:40 by niduches          #+#    #+#             */
/*   Updated: 2019/12/19 02:38:20 by niduches         ###   ########.fr       */
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
		if (in_str(s[i], " \t") && !*((short*)in) && !sep)
			sep = 1;
		if (!in_str(s[i], " \t") && sep == 1)
		{
			sep = 0;
			nb++;
		}
		i++;
	}
	return (nb);
}

static int	get_len_arg_no(char const *s, char *in, int *j, int *i)
{
	int		nb;

	nb = 0;
	*j = 0;
	while (s[*j] && (!in_str(s[*j], " \t") || *((short*)in)))
	{
		if (!in[1] && s[*j] == '\"' && (*i + *j == 0 || s[*j - 1] != '\\'))
			in[0] = (in[0] == 0) ? 1 : 0;
		else if (s[*j] == '\'' && (*i + *j == 0 || s[*j - 1] != '\\'))
			in[1] = (in[1] == 0) ? 1 : 0;
		else if (s[*j] != '\\' || (*i + *j != 0 && s[*j - 1] == '\\'))
			nb++;
		(*j)++;
	}
	return (nb);
}

static char	*fill_in_no(char *s, int *i, char *in)
{
	int		j;
	int		k;
	char	*line;

	while (in_str(s[*i], " \t"))
		(*i)++;
	s += *i;
	if (!(line = malloc((get_len_arg_no(s, in, &j, i) + 1) * sizeof(char))))
		return (NULL);
	j = 0;
	k = 0;
	*((short*)in) = 0;
	while (s[j] && (!in_str(s[j], " \t") || *((short*)in)))
	{
		if (!in[1] && s[j] == '\"' && (*i + j == 0 || s[j - 1] != '\\'))
			in[0] = (in[0] == 0) ? 1 : 0;
		else if (s[j] == '\'' && (j == 0 || s[j - 1] != '\\'))
			in[1] = (in[1] == 0) ? 1 : 0;
		else
			line[k++] = s[j];
		j++;
	}
	line[k] = '\0';
	*i += j;
	return (line);
}

char		**custom_split_arg(char const *str)
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
		if (!(array[word++] = fill_in_no((char*)str, &i, in)))
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
