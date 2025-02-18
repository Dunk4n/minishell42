/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_line_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 19:46:54 by niduches          #+#    #+#             */
/*   Updated: 2020/01/09 13:21:06 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		is_env_variable(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && (i == 0 || line[i - 1] != '\\') &&
line[i + 1] != '\0' && !ft_isspace(line[i + 1]))
			return (1);
		i++;
	}
	return (0);
}

static size_t	get_len_envline(char *line, t_env *env)
{
	size_t	i;
	size_t	nb;
	char	in;

	nb = 0;
	i = 0;
	in = 0;
	while (line[i])
	{
		while (line[i] && (in || line[i] != '$' || (i > 0 && line[i - 1] ==
'\\') || ft_isspace(line[i + 1]) || !line[i + 1] || line[i + 1] == '$' ||
line[i + 1] == '\"' || line[i + 1] == '\''))
		{
			if (line[i++] == '\'')
				in = (in + 1) % 2;
			nb++;
		}
		if (line[i] == '$')
			nb += get_var_len(line + i + 1, &i, env);
	}
	return (nb);
}

char			*to_line_env(char *line, t_env *env)
{
	char	*new_line;
	int		len;

	if (!line)
		return (NULL);
	if (!is_env_variable(line))
		return (line);
	len = get_len_envline(line, env);
	if (!(new_line = malloc((len + 1) * sizeof(char))))
		return (line);
	new_line[len] = '\0';
	put_in_line(line, new_line, env);
	free(line);
	return (new_line);
}
