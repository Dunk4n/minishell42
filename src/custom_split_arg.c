/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 18:58:40 by niduches          #+#    #+#             */
/*   Updated: 2019/12/19 17:05:01 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_nb(char const *s, char *in)
{
	int		nb;
	int		i;
	char	sep;

	sep = 1;
	nb = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\"' && !in[1])
			in[0] = (in[0] == 0) ? 1 : 0;
		if ((s[i] == '\'') && !in[0])
			in[1] = (in[1] == 0) ? 1 : 0;
		if (in_str(s[i], " \t\n") && !*((short*)in) && !sep)
			sep = 1;
		if (!in_str(s[i], " \t\n") && sep == 1)
		{
			sep = 0;
			nb++;
		}
		i += (((!in[1] || (in[0] && (s[i + 1] == '\\' || s[i + 1] == '\"'))) &&
s[i] == '\\') && s[i + 1]) ? 2 : 1;
	}
	return (nb);
}

static int	get_len_arg_no(char const *s, char *in, int *tabl)
{
	int		nb;

	nb = 0;
	tabl[1] = 0;
	while (s[tabl[1]] && (!in_str(s[tabl[1]], " \t\n") || *((short*)in)))
	{
		if (!in[1] && s[tabl[1]] == '\"')
			in[0] = (in[0] == 0) ? 1 : 0;
		else if (s[tabl[1]] == '\'' && !in[0])
			in[1] = (in[1] == 0) ? 1 : 0;
		else if (s[tabl[1]] != '\\' || (*tabl + tabl[1] != 0 && s[tabl[1] - 1]
					== '\\'))
			nb++;
		if ((!in[1] || (in[0] && (s[tabl[1] + 1] == '\\' || s[tabl[1] + 1] ==
'\"'))) && s[tabl[1]] == '\\')
		{
			if (s[tabl[1] + 1])
				tabl[1]++;
		}
		tabl[1]++;
	}
	tabl[1] = 0;
	tabl[2] = 0;
	*((short*)in) = 0;
	return (nb);
}

static void	put_in_line_no(char *s, char *in, char *line, int *tabl)
{
	if (!in[1] && s[tabl[1]] == '\"')
		in[0] = (in[0] == 0) ? 1 : 0;
	else if (s[tabl[1]] == '\'' && !in[0])
		in[1] = (in[1] == 0) ? 1 : 0;
	else if ((!*((short*)in) || (in[0] && s[tabl[1] + 1] == '\"')) &&
s[tabl[1]] == '\\')
	{
		if (s[tabl[1] + 1])
			line[tabl[2]++] = s[tabl[1] + 1];
	}
	else
		line[tabl[2]++] = s[tabl[1]];
	if ((!in[1] || (in[0] && (s[tabl[1] + 1] == '\\' || s[tabl[1] + 1] ==
'\"'))) && s[tabl[1]] == '\\')
	{
		if (s[tabl[1] + 1])
			tabl[1]++;
	}
	tabl[1]++;
}

static char	*fill_in_no(char *s, int *i, char *in)
{
	int		tabl[3];
	char	*line;

	while (in_str(s[*i], " \t\n"))
		(*i)++;
	s += *i;
	tabl[0] = *i;
	if (!(line = malloc((get_len_arg_no(s, in, tabl) + 1) * sizeof(char))))
		return (NULL);
	while (s[tabl[1]] && (!in_str(s[tabl[1]], " \t\n") || *((short*)in)))
		put_in_line_no(s, in, line, tabl);
	line[tabl[2]] = '\0';
	*i += tabl[1];
	return (line);
}

char		**custom_split_arg(char const *str)
{
	int		i;
	int		word;
	int		nb;
	char	in[2];
	char	**array;

	*((short*)in) = 0;
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
