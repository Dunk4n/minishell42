/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_edit_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 13:22:43 by niduches          #+#    #+#             */
/*   Updated: 2020/01/09 14:49:42 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "minishell_bonus.h"

static void	display_all_command_line(t_cursor *cur, char *line)
{
	int	i;
	int	j;
	int	tmp;

	move_cursor(cur->startx, cur->starty);
	cursor_exec("cd");
	write(1, "$> ", 3);
	j = 0;
	i = 0;
	while (i < cur->line_max)
	{
		tmp = write(1, line, ft_strlen(line));
		line += tmp + 1;
		j += 1 + (tmp + ((!cur->line) ? cur->startx : 0)) / cur->term_col;
		move_cursor(0, cur->starty + j);
		i++;
	}
}

static char	*get_good_line(t_cursor *cur, char *line)
{
	char	*new;
	int		i;

	if (!(new = malloc((cur->line_size + 1) * sizeof(char))))
		return (NULL);
	new[cur->line_size] = '\0';
	i = 0;
	while (i < cur->line_size)
	{
		if (line[i])
			new[i] = line[i];
		else
			new[i] = '\n';
		i++;
	}
	return (new);
}

static char	*parse_command(char *line, char *buff, t_cursor *cur, t_env *env)
{
	int		i;
	char	*tmp;

	tmp = buff;
	while (*buff)
	{
		i = 0;
		if (!is_term_command(buff, cur, line))
			add_char_in_line(line, buff++, cur);
		else if (!(i = make_term_command(line, buff, cur, env)))
		{
			if (*buff != 4)
			{
				display_all_command_line(cur, line);
				if (cur->y == cur->term_line - 1)
					write(1, "\n", 1);
			}
			else
				return (NULL);
			return (get_good_line(cur, line));
		}
		buff += i;
	}
	*tmp = '\0';
	return (NULL);
}

int			get_edit_line(t_env *env, char **new_line)
{
	t_cursor	cur;
	char		line[LINE_SIZE];
	char		buff[128];
	ssize_t		size;

	init_cursor(line, &cur, 0, env);
	if (cur.startx < 0 || cur.starty < 0)
		return (0);
	write(1, "$> ", 3);
	while (1)
	{
		move_cursor(0, 0);
		printf("[%d, %d], [%d, %d], [%d, %d] %d                                 \n",
cur.x, cur.y, cur.x - cur.startx, cur.y - cur.starty, cur.col, cur.line, cur.idx);
		move_cursor(cur.x, cur.y);
		if ((size = read(STDIN_FILENO, buff, 127)) <= 0)
			return (0);
		if (g_exit)
		{
			init_cursor(line, &cur, 3, env);
			ft_bzero(line, LINE_SIZE);
			g_exit = 0;
		}
		buff[size] = '\0';
		if (size > 0)
		{
			*new_line = parse_command(line, buff, &cur, env);
			if (*buff)
				return (1);
		}
		display_all_command_line(&cur, line);
		move_cursor(cur.x, cur.y);
	}
	return (0);
}
