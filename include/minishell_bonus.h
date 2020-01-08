/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 19:07:52 by niduches          #+#    #+#             */
/*   Updated: 2020/01/05 11:40:00 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <curses.h>
# include <term.h>
# include "../libft/libft.h"

# define LINE_SIZE 4096

typedef struct	s_env
{
	char			**env;
	size_t			nb_env;
	char			ret;
	struct termios	termios;
	struct termios	termios_save;
	char			*hist[500];
	char			tmp[LINE_SIZE];
	int				size;
	int				idx;
}				t_env;

typedef struct	s_cursor
{
	int		startx;
	int		starty;
	int		x;
	int		y;
	int		idx;
	int		col;
	int		line;
	int		line_max;
	int		line_size;
	int		term_col;
	int		term_line;
}				t_cursor;

t_env			init(char **arg_env);
int				ft_exit(size_t ac, char **av, t_env *env);
int				ft_echo(size_t ac, char **av, t_env *env);
char			**get_env(t_env *env, char *to_find);
int				ft_env(size_t ac, char **av, t_env *env);
int				ft_pwd(size_t ac, char **av, t_env *env);
void			get_all_instruction(char *line, t_env *env);
int				ft_export(size_t ac, char **av, t_env *env);
int				ft_unset(size_t ac, char **av, t_env *env);
char			*to_line_env(char *line, t_env *env);
size_t			put_in_line(char *line, char *new_line, t_env *env);
size_t			get_var_len(char *line, size_t *idx, t_env *env);
int				in_str(char c, char const *charset);
char			**custom_split_arg(char const *str);
char			**custom_split_instr(char const *str);
char			**custom_split_sep(char *line);
int				get_nb_sep(char *line);
int				is_only_space(char *line, size_t end);
size_t			pass_normal(char *line);
size_t			is_sep(char *line);
int				exec_bin(char **av, t_env *env);
void			get_exec_path(char *path, char *name, t_env *env);
char			**custom_split_sep_pipe(char *line);
int				get_nb_sep_pipe(char *line);
size_t			pass_normal_pipe(char *line);
size_t			is_sep_pipe(char *line);
int				ft_cd(size_t ac, char **av, t_env *env);
void			free_env(t_env *env);

//cursor
void			get_cursor_position(int *col, int *row);
void			move_cursor(int col, int row);
void			cursor_exec(char *cmd);
void			cursor_exec_at(char *cmd, int x, int y);

int				get_edit_line(t_env *env, char **line);

#endif
