/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_instruction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 17:41:38 by niduches          #+#    #+#             */
/*   Updated: 2020/01/09 13:20:26 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"

// separate line by '|'
void		get_sep_pipe(char *line, t_env *env)
{
	char	**instructions;
	size_t	i;

	if (!(instructions = custom_split_sep_pipe(line)))
		return ;
	if (instructions[0] && instructions[1])
		execute_pipeline(instructions, env);
	else
		execute_standalone(instructions[0], env);
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

static int	good_logic_syntax(char **inst)
{
	size_t	i;
	int		nb;

	nb = 0;
	i = 0;
	while (inst[i] && nb >= 0)
	{
		if (!ft_strcmp("(", inst[i]) || !ft_strcmp(")", inst[i]))
		{
			if ((!ft_strcmp("(", inst[i]) &&inst[i + 1] && !ft_strcmp(")", inst[
i + 1])) || (!ft_strcmp(")", inst[i]) && i > 0 && !ft_strcmp("(", inst[i - 1])))
				return (0);
			nb += (!ft_strcmp("(", inst[i])) ? 1 : -1;
		}
		else if (!ft_strcmp("&&", inst[i]) || !ft_strcmp("||", inst[i]))
		{
			if (i == 0 || !ft_strcmp("(", inst[i - 1]) || !ft_strcmp("&&",
inst[i - 1]) || !ft_strcmp("||", inst[i - 1]) || !inst[i + 1] || !ft_strcmp(")",
inst[i + 1]) || !ft_strcmp("&&", inst[i + 1]) || !ft_strcmp("||", inst[i + 1]))
				return (0);
		}
		i++;
	}
	return (!nb);
}

// separate line by '(', ')', '&&', '||'
void		get_sep_logic(char *line, t_env *env)
{
	char	**instructions;
	size_t	i;

	if (!(instructions = custom_split_sep(line)))
		return ;
	env->ret = 0;
	i = 0;
	if (!good_logic_syntax(instructions))
	{
		while (instructions[i])
			free(instructions[i++]);
		ft_printf("bash: syntax error\n");
		return ;
	}
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

// separate line by ';'
void		get_all_instruction(char *line, t_env *env)
{
	char	**instructions;
	size_t	i;

	if (!line)
		return ;
	if (!(instructions = custom_split_instr(line)))
		return ;
	i = 0;
	while (instructions[i])
	{
		get_sep_logic(instructions[i], env);
		free(instructions[i++]);
	}
	free(instructions);
}
