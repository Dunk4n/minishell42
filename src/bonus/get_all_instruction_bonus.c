/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_instruction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 17:41:38 by niduches          #+#    #+#             */
/*   Updated: 2020/01/14 14:36:39 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell_bonus.h"
#include "execute_bonus.h"

void		get_sep_pipe(char *line, t_env *env)
{
	char	**instructions;
	size_t	i;

	tcsetattr(STDIN_FILENO, TCSADRAIN, &(env->termios_save));
	g_exec = 1;
	if (!(instructions = custom_split_sep_pipe(line)))
		return ;
	if (instructions[0] && instructions[1])
		execute_pipeline(instructions, env);
	else
		execute_standalone(instructions[0], env);
	g_exec = 0;
	tcsetattr(STDIN_FILENO, TCSADRAIN, &(env->termios));
	i = 0;
	while (instructions[i])
		free(instructions[i++]);
	free(instructions);
}

static void	pass_parenthesis(char **inst, size_t *idx)
{
	int	nb;

	free(inst[(*idx)++]);
	free(inst[(*idx)++]);
	nb = 1;
	while (nb)
	{
		if (!ft_strcmp("(", inst[*idx]))
			nb++;
		if (!ft_strcmp(")", inst[*idx]))
			nb--;
		if (nb)
			free(inst[(*idx)++]);
	}
}

static int	get_sep_logic_error(char **instructions)
{
	size_t	i;

	i = 0;
	if (!good_logic_syntax(instructions))
	{
		while (instructions[i])
			free(instructions[i++]);
		free(instructions);
		ft_printf("bash: syntax error\n");
		return (0);
	}
	return (1);
}

void		get_sep_logic(char *line, t_env *env)
{
	char	**instructions;
	size_t	i;

	if (!(instructions = custom_split_sep(line)))
		return ;
	env->ret = 0;
	if (!get_sep_logic_error(instructions))
		return ;
	i = 0;
	while (instructions[i])
	{
		if (!is_sep(instructions[i]))
			get_sep_pipe(instructions[i], env);
		else if ((!ft_strcmp(instructions[i], "&&") && env->ret) ||
(!ft_strcmp(instructions[i], "||") && !env->ret))
		{
			if (!ft_strcmp("(", instructions[i + 1]))
				pass_parenthesis(instructions, &i);
			else
				free(instructions[i++]);
		}
		free(instructions[i++]);
	}
	free(instructions);
}

void		get_all_instruction(char *line, t_env *env)
{
	char	**instructions;
	size_t	i;

	if (!line)
		return ;
	if (!(instructions = custom_split_instr(line)))
	{
		free(line);
		return ;
	}
	free(line);
	i = 0;
	while (instructions[i])
	{
		get_sep_logic(instructions[i], env);
		free(instructions[i++]);
	}
	free(instructions);
}
