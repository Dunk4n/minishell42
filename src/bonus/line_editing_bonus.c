
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
(line[i - 1] != '\\' && !((char*)(&acc))[1])))
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
	if (!ft_strncmp("cc", buff, 2) || !ft_strncmp("vv", buff, 2) ||
!ft_strncmp("xx", buff, 2) || !ft_strncmp("CC", buff, 2) ||
!ft_strncmp("XX", buff, 2))
		return (1);
	if (*buff == 27 || *buff == 127)
		return (1);
	else if (*buff < ' ')
		return (1);
	return (0);
}

void		update_cursor_pos(t_cursor *cur)
{
	cur->y = cur->starty + ((cur->line_size - (cur->col + ((!cur->line) ?
cur->startx : 0)) - cur->line) / cur->term_col) + cur->line +
(cur->col + ((!cur->line) ? cur->startx + 3 : 0)) / cur->term_col;
	if (cur->y > cur->term_line)
	{
		cur->starty -= cur->y - (cur->term_line);
		cur->y = cur->term_line - 1;
	}
	cur->x = (cur->col + ((!cur->line) ? cur->startx + 3 : 0)) % cur->term_col;
}

void		init_cursor(char *line, t_cursor *cur, int nb_cur, t_env *env)
{
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
	update_cursor_pos(cur);
	env->idx = -1;
	ft_bzero(env->tmp, LINE_SIZE);
}

void		add_char_in_line(char *line, char *buff, t_cursor *cur)
{
	int	i;

	if (cur->line_size + 1 >= LINE_SIZE)
		return ;
	ft_memmove(line + cur->idx + 1, line + cur->idx, cur->line_size -
cur->idx);
	line[cur->idx++] = (*buff != '\n') ? *buff : '\0';
	cur->col++;
	update_cursor_pos(cur);
	cur->line_size++;
	if (*buff == '\n')
		return ;
	i = 0;
	while (cur->idx + i < LINE_SIZE && line[cur->idx + i])
		i++;
	i = (i + cur->col + (!cur->line ? cur->startx + 3 : 0)) %
		cur->term_col;
	if (!i)
	{
		write(1, "\n", 1);
		cur->starty--;
	}
}
