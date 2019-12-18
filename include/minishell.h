/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 19:07:52 by niduches          #+#    #+#             */
/*   Updated: 2019/12/18 19:38:19 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

typedef struct	s_env
{
	char	**env;
	size_t	nb_env;
	int		ret;
}				t_env;

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
char			**custom_split(char const *str, char *set, char aptf);
char			*fill_in_no(char const *s, int *i, char *in, char *set);
int				in_str(char c, char const *charset);

#endif
