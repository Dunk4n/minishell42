/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing_command_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 11:15:21 by niduches          #+#    #+#             */
/*   Updated: 2020/01/09 12:20:24 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "minishell_bonus.h"

static void	move_one_char(t_cursor *cur, int dir)
{
	cur->col += dir;
	cur->idx += dir;
}

static void	move_up(char *line, char *buff, t_cursor *cur, int *idx)
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

static void	move_down(char *line, char *buff, t_cursor *cur, int *idx)
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

int			make_term_command(char *line, char *buff, t_cursor *cur, t_env *env)
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
	else if (*buff == 27 && !ft_strncmp(buff + 1, "[D", 2))
	{
		if (cur->idx > 0 && line[cur->idx - 1])
			move_one_char(cur, -1);
		idx += 2;
	}
	else if (*buff == 27 && !ft_strncmp(buff + 1, "[C", 2))
	{
		if (line[cur->idx] != '\0')
			move_one_char(cur, 1);
		idx += 2;
	}
	else if (*buff == 27 && !ft_strncmp(buff + 1, "[A", 2))
	{
		idx += 2;
		if (env->idx < HISTORY_SIZE && env->hist[env->idx + 1] != NULL)
		{
			if (env->idx == -1)
			{
				int	i;

				i = 0;
				while (i < cur->line_size)
				{
					env->tmp[i] = (!line[i]) ? '\n' : line[i];
					i++;
				}
			}
			env->idx++;
			charge_from_history(line, env->hist[env->idx], cur);
		}
	}
	else if (*buff == 27 && !ft_strncmp(buff + 1, "[B", 2))
	{
		idx += 2;
		if (!env->idx)
		{
			env->idx--;
			charge_from_history(line, env->tmp, cur);
		}
		if (env->idx > 0)
		{
			env->idx--;
			charge_from_history(line, env->hist[env->idx], cur);
		}
	}
	else if (*buff == 27 && !ft_strncmp(buff + 1, "[H", 2))
	{
		while (cur->idx > 0 && cur->col > 0 && line[cur->idx - 1])
			move_one_char(cur, -1);
		idx += 2;
	}
	else if (*buff == 27 && !ft_strncmp(buff + 1, "[F", 2))
	{
		while (line[cur->idx])
			move_one_char(cur, 1);
		idx += 2;
	}
	else if (*buff == 27 && !ft_strncmp(buff + 1, "[1;5D", 5))
	{
		while (cur->idx > 0 && cur->col > 0 && line[cur->idx - 1] &&
!ft_isalnum(line[cur->idx - 1]))
			move_one_char(cur, -1);
		while (cur->idx > 0 && cur->col > 0 && ft_isalnum(line[cur->idx - 1]))
			move_one_char(cur, -1);
		idx += 5;
	}
	else if (*buff == 27 && !ft_strncmp(buff + 1, "[1;5C", 5))
	{
		while (line[cur->idx] && line[cur->idx] && !ft_isalnum(line[cur->idx]))
			move_one_char(cur, 1);
		while (ft_isalnum(line[cur->idx]))
			move_one_char(cur, 1);
		idx += 5;
	}
	move_up(line, buff, cur, &idx);
	move_down(line, buff, cur, &idx);
	if (!ft_strncmp("CC", buff, 2))
	{
		ft_memcpy(env->copy, line, LINE_SIZE);
		env->copy_end = cur->line_size;
		idx++;
	}
	if (!ft_strncmp("XX", buff, 2))
	{
		ft_memcpy(env->copy, line, LINE_SIZE);
		env->copy_end = cur->line_size;
		ft_bzero(line, LINE_SIZE);
		cur->x = cur->startx;
		cur->y = cur->starty;
		cur->idx = 0;
		cur->col = 0;
		cur->line = 0;
		cur->line_max = 1;
		cur->line_size = 0;
		idx++;
	}
	if (!ft_strncmp("cc", buff, 2))
	{
		ft_bzero(env->copy, LINE_SIZE);
		ft_memcpy(env->copy, line + cur->idx, LINE_SIZE - cur->idx);
		env->copy_end = cur->line_size - cur->idx;
		idx++;
	}
	if (!ft_strncmp("xx", buff, 2))
	{
		ft_bzero(env->copy, LINE_SIZE);
		ft_memcpy(env->copy, line + cur->idx, LINE_SIZE - cur->idx);
		ft_bzero(line + cur->idx, LINE_SIZE - cur->idx);
		env->copy_end = cur->line_size - cur->idx;
		cur->line_max = cur->line + 1;
		cur->line_size = cur->idx + 1;
		idx++;
	}
	if (!ft_strncmp("vv", buff, 2))
	{
		int	i;

		i = 0;
		while (i < env->copy_end)
		{
			if (!env->copy[i])
			{
				add_char_in_line(line, "\n", cur);
				if (cur->y == cur->term_line - 1)
					cur->starty--;
				write(1, "\n", 1);
				cur->col = -1;
				cur->line++;
				cur->line_max++;
			}
			else
				add_char_in_line(line, env->copy + i, cur);
			i++;
		}
		idx++;
	}
	update_cursor_pos(cur, line);
	return (idx);
}
