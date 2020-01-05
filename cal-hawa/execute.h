/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cal-hawa <cal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 11:38:10 by cal-hawa          #+#    #+#             */
/*   Updated: 2020/01/05 12:42:22 by cal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# define MAX_ARGS	32
# define MAX_REDIRS	16

/*
** === Not implemented ===
** +) finding executable path
** +) evironnement variables
** +) built-in execution
*/

int				g_exit_status;
char			**g_envp;

/*
** Execute
*/
int					execute_pipeline(char **commands);
int					execute_standalone(char *command);

/*
** Parse
*/
int				process_quote(int c, int quote);
char			*str_trim(char *str, char c);

int				parse_cmd(char *cmd, char **redirs, char **args);
int				split_redirections(char *cmd, char **redirs);
int				split_arguments(char *cmd, int cmd_len, char **args);
int				split_args(char *str, char **args, int nargs);

/*
** Pipeline
*/
int				mpipeline(char **args, char **redirs, int last);

/*
** Standalone
*/
int				standalone(char **arguments, char **redirections);

/*
** Redirections
*/
int				set_redirections(char **redirs);

#endif
