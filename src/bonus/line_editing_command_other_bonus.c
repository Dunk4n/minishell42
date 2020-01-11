/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing_command_other_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 15:48:18 by niduches          #+#    #+#             */
/*   Updated: 2020/01/11 15:55:20 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "minishell_bonus.h"

static int	move_history(char *line, char *buff, t_cursor *cur, t_env *env)
{
	int	i;

	if (*buff == 27 && !ft_strncmp(buff + 1, "[A", 2))
	{
		if (env->idx < HISTORY_SIZE && env->hist[env->idx + 1] != NULL)
		{
			i = -1;
			while (env->idx == -1 && ++i < cur->line_size)
				env->tmp[i] = (!line[i]) ? '\n' : line[i];
			env->idx++;
			charge_from_history(line, env->hist[env->idx], cur);
		}
		return (2);
	}
	if (*buff == 27 && !ft_strncmp(buff + 1, "[1;5D", 5))
	{
		while (cur->idx > 0 && cur->col > 0 && line[cur->idx - 1] &&
!ft_isalnum(line[cur->idx - 1]))
			move_one_char(cur, -1);
		while (cur->idx > 0 && cur->col > 0 && ft_isalnum(line[cur->idx - 1]))
			move_one_char(cur, -1);
		return (5);
	}
	return (0);
}

static int	term_past(char *line, char *buff, t_cursor *cur, t_env *env)
{
	int	i;

	if (!ft_strncmp("vv", buff, 2))
	{
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
		return (1);
	}
	return (0);
}

static int	term_cut(char *line, char *buff, t_cursor *cur, t_env *env)
{
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
		return (1);
	}
	if (!ft_strncmp("xx", buff, 2))
	{
		ft_bzero(env->copy, LINE_SIZE);
		ft_memcpy(env->copy, line + cur->idx, LINE_SIZE - cur->idx);
		ft_bzero(line + cur->idx, LINE_SIZE - cur->idx);
		env->copy_end = cur->line_size - cur->idx;
		cur->line_max = cur->line + 1;
		cur->line_size = cur->idx;
		return (1);
	}
	return (0);
}

int			term_copy(char *line, char *buff, t_cursor *cur, t_env *env)
{
	int	tmp;

	if (!ft_strncmp("CC", buff, 2))
	{
		ft_memcpy(env->copy, line, LINE_SIZE);
		env->copy_end = cur->line_size;
		return (1);
	}
	if (!ft_strncmp("cc", buff, 2))
	{
		ft_bzero(env->copy, LINE_SIZE);
		ft_memcpy(env->copy, line + cur->idx, LINE_SIZE - cur->idx);
		env->copy_end = cur->line_size - cur->idx;
		return (1);
	}
	tmp = 0;
	move_up(line, buff, cur, &tmp);
	move_down(line, buff, cur, &tmp);
	tmp += term_cut(line, buff, cur, env);
	tmp += term_past(line, buff, cur, env);
	tmp += move_cur(line, buff, cur, env);
	tmp += move_history(line, buff, cur, env);
	return (tmp);
}
