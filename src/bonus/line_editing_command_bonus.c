
#include <unistd.h>
#include <stdio.h>
#include "minishell_bonus.h"

static void	move_one_char(t_cursor *cur, int *idx, int dir, int offset)
{
	cur->col += dir;
	cur->idx += dir;
	(*idx) += offset;
}

static void	move_up(char *line, char *buff, t_cursor *cur, int *idx)
{
	int	i;

	if (*buff == 27 && !ft_strncmp(buff + 1, "[1;5A", 5) && cur->line > 0)
	{
		cur->idx -= cur->col;
		if (cur->idx > 0)
			cur->idx--;
		while (cur->idx - 1 == 0 || line[cur->idx - 1])
			cur->idx--;
		i = 0;
		while (i < cur->col && line[cur->idx + i])
			i++;
		cur->idx += i;
		cur->col = i;
		cur->line--;
		(*idx) += 5;
	}
}

static void	move_down(char *line, char *buff, t_cursor *cur, int *idx)
{
	int	i;

	if (*buff == 27 && !ft_strncmp(buff + 1, "[1;5B", 5) &&
cur->line < cur->line_max - 1)
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
		(*idx) += 5;
	}
}

int			make_term_command(char *line, char *buff, t_cursor *cur, t_env *env)
{
	int	idx;

	idx = 1;
	if (!ft_strcmp(buff, "\n") || (*buff == 4 && !cur->line_size))
		return (0);
	if (*buff == 127 && cur->idx > 0 && line[cur->idx - 1])
	{
		ft_memmove(line + cur->idx - 1, line + cur->idx,
cur->line_size - cur->idx + 1);
		move_one_char(cur, &idx, -1, 0);
		cur->line_size--;
	}
	else if (*buff == 27 && !ft_strncmp(buff + 1, "[D", 2) && cur->idx > 0 &&
line[cur->idx - 1])
		move_one_char(cur, &idx, -1, 2);
	else if (*buff == 27 && !ft_strncmp(buff + 1, "[C", 2) &&
line[cur->idx] != '\0')
		move_one_char(cur, &idx, 1, 2);
	else if (*buff == 27 && !ft_strncmp(buff + 1, "[A", 2))
	{
		move_cursor(0, 2);
		printf("HAUT           \n");
		move_cursor(cur->x, cur->y);
		idx += 2;
	}
	else if (*buff == 27 && !ft_strncmp(buff + 1, "[B", 2))
	{
		move_cursor(0, 2);
		printf("BAS            \n");
		move_cursor(cur->x, cur->y);
		idx += 2;
	}
	else if (*buff == 27 && !ft_strncmp(buff + 1, "[H", 2))
	{
		while (cur->idx > 0 && cur->col > 0 && line[cur->idx - 1])
			move_one_char(cur, &idx, -1, 0);
		idx += 2;
	}
	else if (*buff == 27 && !ft_strncmp(buff + 1, "[F", 2))
	{
		while (line[cur->idx])
			move_one_char(cur, &idx, 1, 0);
		idx += 2;
	}
	else if (*buff == 27 && !ft_strncmp(buff + 1, "[1;5D", 5))
	{
		while (cur->idx > 0 && cur->col > 0 && line[cur->idx - 1] &&
!ft_isalnum(line[cur->idx - 1]))
			move_one_char(cur, &idx, -1, 0);
		while (cur->idx > 0 && cur->col > 0 && ft_isalnum(line[cur->idx - 1]))
			move_one_char(cur, &idx, -1, 0);
		idx += 5;
	}
	else if (*buff == 27 && !ft_strncmp(buff + 1, "[1;5C", 5))
	{
		while (line[cur->idx] && line[cur->idx] && !ft_isalnum(line[cur->idx]))
			move_one_char(cur, &idx, 1, 0);
		while (ft_isalnum(line[cur->idx]))
			move_one_char(cur, &idx, 1, 0);
		idx += 5;
	}
	move_up(line, buff, cur, &idx);
	move_down(line, buff, cur, &idx);
	update_cursor_pos(cur);
	return (idx);
}
