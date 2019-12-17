/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 19:07:52 by niduches          #+#    #+#             */
/*   Updated: 2019/12/16 17:46:07 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

typedef struct	s_env
{
	char	**env;
	int		ret;
}				t_env;

t_env	init(char **arg_env);
int		ft_exit(size_t ac, char **av, t_env *env);
int		ft_echo(size_t ac, char **av, t_env *env);
char	*get_env(t_env *env, char *to_find, char key);
int		ft_env(size_t ac, char **av, t_env *env);
int		ft_pwd(size_t ac, char **av, t_env *env);
void	get_all_instruction(char *line, t_env *env);

#endif
