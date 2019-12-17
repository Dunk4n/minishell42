/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 09:15:31 by niduches          #+#    #+#             */
/*   Updated: 2019/12/16 17:38:12 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	in_charset(char const *charset, char c)
{
	size_t	i;

	i = 0;
	while (charset[i])
		if (charset[i++] == c)
			return (1);
	return (0);
}

static int	get_nb(char const *s, char *charset)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (s[i])
	{
		if (!in_charset(charset, s[i]) && (i == 0 ||
in_charset(charset, s[i - 1])))
			nb++;
		i++;
	}
	return (nb);
}

static char	*fill_in(char **line, char const *s, int *i, char *charset)
{
	int	j;

	j = 0;
	while (in_charset(charset, s[*i]))
		(*i)++;
	j = 0;
	while (s[*i + j] && !in_charset(charset, s[*i + j]))
		j++;
	if (!(*line = malloc((j + 1) * sizeof(char))))
		return (NULL);
	j = 0;
	while (s[*i + j] && !in_charset(charset, s[*i + j]))
	{
		(*line)[j] = s[*i + j];
		j++;
	}
	(*line)[j] = '\0';
	*i += j;
	return (*line);
}

char		**ft_split(char const *s, char *charset)
{
	int		i;
	int		word;
	int		nb;
	char	**array;

	if (!s)
		return (NULL);
	nb = get_nb(s, charset);
	if (!(array = malloc((nb + 1) * sizeof(char*))))
		return (NULL);
	i = 0;
	word = 0;
	while (word < nb)
	{
		if (!(array[word] = fill_in(array + word, s, &i, charset)))
		{
			while (--word >= 0)
				free(array[word]);
			free(array);
			return (NULL);
		}
		word++;
	}
	array[word] = NULL;
	return (array);
}
