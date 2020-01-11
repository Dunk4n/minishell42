/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing_command_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 11:15:21 by niduches          #+#    #+#             */
/*   Updated: 2020/01/11 15:57:55 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "minishell_bonus.h"

void	move_one_char(t_cursor *cur, int dir)
{
	cur->col += dir;
	cur->idx += dir;
}

void	move_up(char *line, char *buff, t_cursor *cur, int *idx)
{
	int	i;

	if (*buff == 27 && !ft_strncmp(buff + 1, "[1;5A", 5))
	{
		if (cur->line > 0)
		{
			cur->idx -= cur->col;
			if (cur->idx > 0)
				cur->idx--;
			while (cur->idx - 1 == 0 || (cur->idx - 1 > 0 &&
line[cur->idx - 1]))
				cur->idx--;
			i = 0;
			while (i < cur->col && line[cur->idx + i])
				i++;
			cur->idx += i;
			cur->col = i;
			cur->line--;
		}
		(*idx) += 5;
	}
}

void	move_down(char *line, char *buff, t_cursor *cur, int *idx)
{
	int	i;

	if (*buff == 27 && !ft_strncmp(buff + 1, "[1;5B", 5))
	{
		if (cur->line < cur->line_max - 1)
		{
			i = 0;
			while (cur->idx < cur->line_size && line[cur->idx])
				cur->idx++;
			if (cur->idx < cur->line_size)
				cur->idx++;
			while (i < cur->col && line[cur->idx + i])
				i++;
			cur->idx += i;
			cur->col = i;
			cur->line++;
		}
		(*idx) += 5;
	}
}

int		move_cur(char *line, char *buff, t_cursor *cur, t_env *env)
{
	if (*buff == 27 && !ft_strncmp(buff + 1, "[D", 2) && cur->idx > 0 &&
line[cur->idx - 1])
		move_one_char(cur, -1);
	if (*buff == 27 && !ft_strncmp(buff + 1, "[C", 2) && line[cur->idx] != '\0')
		move_one_char(cur, 1);
	if (*buff == 27 && !ft_strncmp(buff + 1, "[B", 2) && env->idx >= 0)
	{
		charge_from_history(line,
!env->idx ? env->tmp : env->hist[env->idx], cur);
		env->idx--;
	}
	if (*buff == 27 && !ft_strncmp(buff + 1, "[H", 2))
		while (cur->idx > 0 && cur->col > 0 && line[cur->idx - 1])
			move_one_char(cur, -1);
	if (*buff == 27 && !ft_strncmp(buff + 1, "[F", 2))
		while (line[cur->idx])
			move_one_char(cur, 1);
	if (*buff == 27 && (!ft_strncmp(buff + 1, "[D", 2) || !ft_strncmp(buff + 1,
"[C", 2) || !ft_strncmp(buff + 1, "[B", 2) || !ft_strncmp(buff + 1, "[H", 2) ||
!ft_strncmp(buff + 1, "[F", 2)))
		return (2);
	return (0);
}

int		make_term_command(char *line, char *buff, t_cursor *cur, t_env *env)
{
	int	idx;

	idx = 1;
	if (*buff == '\n' || (*buff == 4 && !cur->line_size))
		return (0);
	if (*buff == 127 && cur->idx > 0 && line[cur->idx - 1])
	{
		ft_memmove(line + cur->idx - 1, line + cur->idx,
cur->line_size - cur->idx + 1);
		move_one_char(cur, -1);
		cur->line_size--;
		if (!cur->line_size)
			env->idx = -1;
	}
	else if (*buff == 27 && !ft_strncmp(buff + 1, "[1;5C", 5))
	{
		while (line[cur->idx] && line[cur->idx] && !ft_isalnum(line[cur->idx]))
			move_one_char(cur, 1);
		while (ft_isalnum(line[cur->idx]))
			move_one_char(cur, 1);
		idx += 5;
	}
	idx += term_copy(line, buff, cur, env);
	update_cursor_pos(cur, line);
	return (idx);
}
