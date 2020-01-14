/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cal-hawa <cal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 13:56:14 by cal-hawa          #+#    #+#             */
/*   Updated: 2020/01/14 08:35:57 by cal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "minishell.h"

int				is_built_in(char *filename);
int				execve_wrapper(char **argv, t_env *env);
int				launch_built_in(char **argv, t_env *env);

int				ft_cd(size_t ac, char **av, t_env *env);
int				ft_export(size_t ac, char **av, t_env *env);
int				ft_unset(size_t ac, char **av, t_env *env);
int				ft_exit(size_t ac, char **av, t_env *env);

int				ft_echo(size_t ac, char **av, t_env *env);
int				ft_env(size_t ac, char **av, t_env *env);
int				ft_pwd(size_t ac, char **av, t_env *env);

#endif
