
#include <unistd.h>
#include <stdio.h>
#include <curses.h>
#include <term.h>
#include "minishell.h"

void	get_cursor_position(int *col, int *row)
{
    char	buff[16];
	char	*term;
    size_t	i;

	term = tgetstr("u7", NULL);
	write(1, term, ft_strlen(term));
    read(1, buff, 16);
	*col = 0;
	*row = 0;
	i = 2;
	*row = ft_atoi(&buff[i]) - 1;
	while (buff[i] >= '0' && buff[i] <= '9')
		i++;
	if (buff[i])
		i++;
	*col = ft_atoi(&buff[i]) - 1;
}

void	move_cursor(int col, int row)
{
	char	*term;

	if (col < 0)
		col = 0;
	if (row < 0)
		row = 0;
	term = tgoto(tgetstr("cm", NULL), col, row);
	write(1, term, ft_strlen(term));
}

void	cursor_exec(char *cmd)
{
	char	*tmp;

	tmp = tgetstr(cmd, NULL);
	write(1, tmp, ft_strlen(tmp));
}

void	cursor_exec_at(char *cmd, int x, int y)
{
	char	*tmp;
	int		col;
	int		line;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	get_cursor_position(&col, &line);
	move_cursor(x, y);
	tmp = tgetstr(cmd, NULL);
	write(1, tmp, ft_strlen(tmp));
	move_cursor(col, line);
}
