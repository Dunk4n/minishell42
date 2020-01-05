/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 19:07:13 by niduches          #+#    #+#             */
/*   Updated: 2020/01/05 11:41:07 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "minishell.h"

#include <curses.h>
#include <term.h>

int		main(int ac, char **av, char **arg_env)
{
	t_env	env;
//	char	*line;

	if (ac != 1)
		return (0);
	(void)av;
	if (!((env = init(arg_env)).env))
		return (1);
	/*
	while (1)
	{
		write(1, "$> ", 3);
		if (!get_next_line(0, &line) && (!line || !line[0]))
		{
			free(line);
			ft_exit(0, NULL, &env);
		}
		if (!(line = to_line_env(line, &env)))
			free_env(&env);
		get_all_instruction(line, &env);
	}
	return (env.ret);
	*/
	char	*term;

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

//clear
//	term = tgetstr("cl", NULL);
//	write(1, term, ft_strlen(term));
//move
//	term = tgetstr("cm", NULL);
//	term = tgoto(term, 5, 5);
//	write(1, term, ft_strlen(term));
//	write(1, "A", 1);
//	write(1, "\n", 1);
	#include <string.h>
	char	buff[4096];
	ssize_t	size;
	struct termios	termios;
	char	line[4096];

	bzero(line, 4096);
	tcgetattr(STDIN_FILENO, &termios);
	termios.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &(termios));
	*buff = '\0';
	while (1)
	{
		bzero(buff, 10);
		if ((size = read(STDIN_FILENO, buff, 10)) <= 0)
			return (1);
		buff[size] = '\0';
		//printf("buff [%s], %d, %d, %d, %d\n", buff, buff[0], buff[1], buff[2], buff[3]);
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
		//term = tgetstr("cd", NULL);
		//write(1, term, ft_strlen(term));
		term = tgetstr("cb", NULL);
		write(1, term, ft_strlen(term));
		strcat(line, buff);
		write(STDIN_FILENO, line, strlen(line));
	}
	return (0);
}
