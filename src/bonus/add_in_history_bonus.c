/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_in_history_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 14:17:35 by niduches          #+#    #+#             */
/*   Updated: 2020/01/14 10:03:21 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell_bonus.h"

void	add_all_line(char *line, t_cursor *cur)
{
	size_t	i;
	int		j;
	int		nb;

	i = 0;
	nb = 0;
	while (i < LINE_SIZE && line[i])
	{
		j = 0;
		while (i + j < LINE_SIZE && line[i + j] && line[i + j] != '\n')
			j++;
		nb += 1 + (j + (!nb ? cur->startx + 3 : 0)) / cur->term_col;
		i += j + 1;
	}
	j = 0;
	nb = nb - (cur->term_line - 1 - cur->starty) - 1;
	if (nb <= 0)
		return ;
	cur->starty -= nb;
	while (j < nb)
	{
		write(1, "\n", 1);
		j++;
	}
}

void	charge_from_history(char *line, char *src, t_cursor *cur)
{
	ft_strncpy(line, src, LINE_SIZE);
	add_all_line(line, cur);
	cur->x = cur->startx;
	cur->y = cur->starty;
	cur->col = 0;
	cur->line = 0;
	cur->idx = 0;
	while (line[cur->idx] && cur->idx < LINE_SIZE)
	{
		cur->col++;
		if (line[cur->idx] == '\n')
		{
			line[cur->idx] = '\0';
			cur->line++;
			cur->col = 0;
		}
		cur->idx++;
	}
	cur->line_max = cur->line + 1;
	cur->line_size = cur->idx;
	update_cursor_pos(cur, line);
}

int		add_in_history(t_env *env, char *line)
{
	char	*tmp;
	char	*tmp2;
	size_t	i;

	if (!line || !env || !ft_strcmp(line, env->hist[0]))
	{
		free(line);
		return (1);
	}
	tmp2 = line;
	i = 0;
	while (i < HISTORY_SIZE && tmp2)
	{
		tmp = env->hist[i];
		env->hist[i] = tmp2;
		tmp2 = tmp;
		i++;
		if (i >= HISTORY_SIZE)
		{
			free(tmp2);
			tmp2 = NULL;
		}
	}
	return (1);
}
