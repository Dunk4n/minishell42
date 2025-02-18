/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 14:19:16 by niduches          #+#    #+#             */
/*   Updated: 2020/01/14 09:53:02 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "minishell_bonus.h"

static int	is_newline_command(char *line, int idx)
{
	int		i;
	short	acc;

	if (idx == 0)
		return (1);
	if (line[idx - 1] == '\\')
		return (0);
	acc = 0;
	i = 0;
	while (i < idx)
	{
		if (line[i] == '\"' && !((char*)(&acc))[1] && (i == 0 || line[i - 1] !=
'\\'))
			((char*)(&acc))[0] = (((char*)(&acc))[0] + 1) % 2;
		else if (line[i] == '\'' && !((char*)(&acc))[0] && (i == 0 ||
(line[i - 1] != '\\' || ((char*)(&acc))[1])))
			((char*)(&acc))[1] = (((char*)(&acc))[1] + 1) % 2;
		i++;
	}
	if (acc == 0)
		return (1);
	return (0);
}

int			is_term_command(char *buff, t_cursor *cur, char *line)
{
	if (*buff == '\n')
	{
		if (is_newline_command(line, cur->idx))
			return (1);
		if (cur->y == cur->term_line - 1)
			cur->starty--;
		write(1, "\n", 1);
		cur->col = -1;
		cur->line++;
		cur->line_max++;
		return (0);
	}
	if (*buff == 23 || *buff == 5 || *buff == 18 || *buff == 20 || *buff == 21)
		return (1);
	if (*buff == 27 || *buff == 127)
		return (1);
	else if (*buff < ' ')
		return (1);
	return (0);
}

void		update_cursor_pos(t_cursor *cur, char *line)
{
	int	i;
	int	j;
	int	nb;

	nb = 0;
	j = 0;
	i = 0;
	while (i < cur->idx)
	{
		if (!line[i++])
		{
			nb += ((nb ? 0 : cur->startx + 3) + j) / cur->term_col;
			j = 0;
		}
		else
			j++;
	}
	nb += ((nb ? 0 : cur->startx + 3) + j) / cur->term_col;
	cur->y = cur->starty + cur->line + nb;
	cur->x = ((cur->line ? 0 : cur->startx + 3) + j) % cur->term_col;
}

void		init_cursor(char *line, t_cursor *cur, int nb_cur, t_env *env)
{
	g_exit = 0;
	ft_bzero(line, LINE_SIZE);
	get_cursor_position(&cur->startx, &cur->starty);
	cur->startx -= nb_cur;
	cur->x = cur->startx;
	cur->y = cur->starty;
	cur->idx = 0;
	cur->col = 0;
	cur->line = 0;
	cur->line_max = 1;
	cur->line_size = 0;
	cur->term_col = tgetnum("co");
	cur->term_line = tgetnum("li");
	update_cursor_pos(cur, line);
	env->idx = -1;
	ft_bzero(env->tmp, LINE_SIZE);
	cur->env = env;
}

void		add_char_in_line(char *line, char *buff, t_cursor *cur)
{
	if (cur->line_size + 1 >= LINE_SIZE)
		return ;
	ft_memmove(line + cur->idx + 1, line + cur->idx, cur->line_size -
cur->idx);
	line[cur->idx++] = (*buff != '\n') ? *buff : '\0';
	cur->col++;
	update_cursor_pos(cur, line);
	cur->line_size++;
	if (*buff == '\n')
		return ;
	add_all_line(line, cur);
}
