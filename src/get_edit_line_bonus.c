
#include <unistd.h>
#include <stdio.h>
#include "minishell.h"

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
		if (line[i] == '\"' && !((char*)(&acc))[1] && (i > 0 || line[i - 1] !=
'\\'))
			((char*)(&acc))[0] = (((char*)(&acc))[0] + 1) % 2;
		else if (line[i] == '\'' && !((char*)(&acc))[0] && (i > 0 ||
(line[i - 1] != '\\' && !((char*)(&acc))[1])))
			((char*)(&acc))[1] = (((char*)(&acc))[1] + 1) % 2;
		i++;
	}
	if (acc == 0)
		return (1);
	return (0);
}

static int	is_term_command(char *buff, t_cursor *cur, char *line)
{
	if (*buff == '\n' && !buff[1])
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
	if (*buff == 27 || *buff == 127)
		return (1);
	else if (*buff < ' ' && !buff[1])
		return (1);
	return (0);
}

static void	update_cursor_pos(t_cursor *cur)
{
	cur->y = cur->starty + ((cur->line_size - (cur->col + ((!cur->line) ?
cur->startx : 0)) - cur->line) / cur->term_col) + cur->line +
(cur->col + ((!cur->line) ? cur->startx + 3 : 0)) / cur->term_col;
	if (cur->y >= cur->term_line)
	{
		cur->starty -= cur->y - (cur->term_line - 1);
		cur->y = cur->term_line - 1;
	}
	cur->x = (cur->col + ((!cur->line) ? cur->startx + 3 : 0)) % cur->term_col;
}

static void	init_cursor(t_cursor *cur)
{
	get_cursor_position(&cur->startx, &cur->starty);
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
}

static void	add_char_in_line(char *line, char *buff, t_cursor *cur)
{
	int	i;

//	if (!line[cur->idx])
//		line[cur->idx++] = (*buff != '\n') ? *buff : '\0';
//	else
//	{
		ft_memmove(line + cur->idx + 1, line + cur->idx,
cur->line_size - cur->idx);
		line[cur->idx++] = (*buff != '\n') ? *buff : '\0';
//	}
	cur->col++;
	update_cursor_pos(cur);
	cur->line_size++;
	if (*buff == '\n')
		return ;
	i = 0;
	while (line[cur->idx + i])
		i++;
	i = (i + cur->col + (!cur->line ? cur->startx + 3 : 0)) % cur->term_col;
	if (!i)
		write(1, "\n", 1);
}

static int	make_term_command(char *line, char *buff, t_cursor *cur)
{
	int	i;

	move_cursor(0, 1);
	printf("[%s], %d, %d, %d, %d, %d, %d, %d, %d\n",
buff + 1, buff[0], buff[1], buff[2], buff[3], buff[4], buff[5], buff[6], buff[7]);
	move_cursor(cur->x, cur->y);
	if (!ft_strcmp(buff, "\n"))
	{
		return (0);
	}
	if (*buff == 127 && !buff[1] && cur->idx > 0 && line[cur->idx - 1])
	{
		ft_memmove(line + cur->idx - 1, line + cur->idx,
cur->line_size - cur->idx + 1);
		cur->col--;
		cur->idx--;
		cur->line_size--;
	}
	else if (*buff == 27 && !ft_strcmp(buff + 1, "[D") && cur->idx > 0 &&
line[cur->idx - 1])
	{
		cur->col--;
		cur->idx--;
	}
	else if (*buff == 27 && !ft_strcmp(buff + 1, "[C") &&
line[cur->idx] != '\0')
	{
		cur->col++;
		cur->idx++;
	}
	else if (*buff == 27 && !ft_strcmp(buff + 1, "[A"))
	{
		move_cursor(0, 2);
		printf("HAUT           \n");
		move_cursor(cur->x, cur->y);
	}
	else if (*buff == 27 && !ft_strcmp(buff + 1, "[B"))
	{
		move_cursor(0, 2);
		printf("BAS            \n");
		move_cursor(cur->x, cur->y);
	}
	else if (*buff == 27 && !ft_strcmp(buff + 1, "[1;5D"))
	{
		while (cur->idx > 0 && cur->col > 0 && line[cur->idx - 1] &&
!ft_isalnum(line[cur->idx - 1]))
		{
			cur->idx--;
			cur->col--;
		}
		while (cur->idx > 0 && cur->col > 0 && ft_isalnum(line[cur->idx - 1]))
		{
			cur->idx--;
			cur->col--;
		}
	}
	else if (*buff == 27 && !ft_strcmp(buff + 1, "[1;5C"))
	{
		while (line[cur->idx] && line[cur->idx] && !ft_isalnum(line[cur->idx]))
		{
			cur->idx++;
			cur->col++;
		}
		while (ft_isalnum(line[cur->idx]))
		{
			cur->idx++;
			cur->col++;
		}
	}
	else if (*buff == 27 && !ft_strcmp(buff + 1, "[F"))
	{
		while (line[cur->idx])
		{
			cur->idx++;
			cur->col++;
		}
	}
	else if (*buff == 27 && !ft_strcmp(buff + 1, "[H"))
	{
		while (cur->idx > 0 && cur->col > 0 && line[cur->idx - 1])
		{
			cur->idx--;
			cur->col--;
		}
	}
	else if (*buff == 27 && !ft_strcmp(buff + 1, "[1;5A") && cur->line > 0)
	{
	int x = 0;
	int y = 0;
	get_cursor_position(&x, &y);
		cur->idx -= cur->col;
		if (cur->idx > 0)
			cur->idx--;
		while (cur->idx - 1 == 0 || line[cur->idx - 1])
			cur->idx--;
		i = 0;
		while (i < cur->col && line[cur->idx + i])
			i++;
	move_cursor(0, 2);
	printf("col %d, idx %d      \n", cur->col, cur->idx);
		cur->idx += i;
		cur->col = i;
		cur->line--;
	move_cursor(x, y);
	}
	else if (*buff == 27 && !ft_strcmp(buff + 1, "[1;5B") &&
cur->line < cur->line_max - 1)
	{
	int x = 0;
	int y = 0;
	get_cursor_position(&x, &y);
	move_cursor(0, 2);
		i = 0;
	printf("%d, %d %d      \n", i, cur->col, cur->idx);
		while (cur->idx < cur->line_size && line[cur->idx])
			cur->idx++;
		if (cur->idx < cur->line_size)
			cur->idx++;
		while (i < cur->col && line[cur->idx + i])
			i++;
		cur->idx += i;
		cur->col = i;
	move_cursor(0, 3);
	printf("[%s] %d          \n", line + cur->idx - 1, cur->idx);
	move_cursor(x, y);
		cur->line++;
	}
	update_cursor_pos(cur);
	return (1);
}

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

int			get_edit_line(t_env *env, char **new_line)
{
	t_cursor	cur;
	char		line[LINE_SIZE];
	char		buff[16];

	*new_line = NULL;
	init_cursor(&cur);
	if (cur.startx < 0 || cur.starty < 0)
		return (0);
	write(1, "$> ", 3);
	ft_bzero(line, LINE_SIZE);
	while (1)
	{
	move_cursor(0, 0);
	printf("xy = [%d, %d], colline = [%d, %d], term = [%d, %d] start = [%d, %d] idx = %d              \n",
cur.x, cur.y, cur.col, cur.line, cur.term_col, cur.term_line, cur.startx, cur.starty, cur.idx);
	move_cursor(cur.x, cur.y);
		ft_bzero(buff, 16);
		if ((read(STDIN_FILENO, buff, 10)) <= 0)
			return (0);
		if (!is_term_command(buff, &cur, line))
			add_char_in_line(line, buff, &cur);
		else if (!make_term_command(line, buff, &cur))
		{
			move_cursor(cur.startx, cur.starty);
			cursor_exec("cd");
			display_all_command_line(&cur, line);
			write(1, "\n", 1);
			*new_line = ft_strdup(line);
			return (1);
		}
		display_all_command_line(&cur, line);
		move_cursor(cur.x, cur.y);
	}
	return (1);
}

/*	char	*term;

	if (!(term = (char*)get_env(&env, "TERM")))
		return (1);
	term = *((char**)term);
	while (*term && *term != '=')
		term++;
	if (*term)
		term++;

	if (tgetent(NULL, term) < 1)
		return (1);
//	printf("nb col = %d, nb line = %d\n", tgetnum("co"), tgetnum("li"));

	cursor_exec("cl");
	#include <string.h>
	char	buff[128];
	ssize_t	size;
	char	line[4096];

	bzero(line, 4096);

	int	x = 0;
	int y = 0;
	get_cursor_position(&x, &y);
	move_cursor(0, 0);
	printf("[%d, %d]\n", x, y);
	move_cursor(x, y);

	*buff = '\0';
	while (1)
	{
//		write(1, "$> ", 3);
		bzero(buff, 10);
		if ((size = read(STDIN_FILENO, buff, 10)) <= 0)
			return (1);
		buff[size] = '\0';
		//printf("buff [%s], %d, %d, %d, %d\n", buff, buff[0], buff[1], buff[2], buff[3]);
		if (*buff == 4 && buff[1] == '\0')
			return (0);
		if (*buff == 27 && !ft_strcmp(buff + 1, "[C"))
		{
			term = tgetstr("nd", NULL);
			write(1, term, ft_strlen(term));
			continue ;
		}
		if (*buff == 27 && !ft_strcmp(buff + 1, "[D"))
		{
			term = tgetstr("le", NULL);
			write(1, term, ft_strlen(term));
			continue ;
		}
		//term = tgetstr("cd", NULL); //efface jusqu'a la fin de l'ecrant
		//write(1, term, ft_strlen(term));
//		move_cursor(0, 0);
//		term = tgetstr("cb", NULL); //efface jusqu'au curseur
//		write(1, term, ft_strlen(term));
//		move_cursor(x, y);
		strcat(line, buff);
		write(STDIN_FILENO, line, strlen(line));
	}
	return (0);
*/
