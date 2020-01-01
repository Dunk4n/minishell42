/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_instruction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 17:41:38 by niduches          #+#    #+#             */
/*   Updated: 2019/12/19 17:46:11 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*g_builtins_name[] = {"echo", "cd", "pwd", "export", "unset", "env",
	"exit", NULL};

int			(*const g_builtins[])(size_t, char**, t_env*) = {ft_echo, NULL,
	ft_pwd, ft_export, ft_unset, ft_env, ft_exit};

static int	is_builtins(char *name)
{
	int	i;

	i = 0;
	while (g_builtins_name[i])
	{
		if (!ft_strcmp(g_builtins_name[i], name))
			return (i);
		i++;
	}
	return (-1);
}

static int	exec_builtins(char **av, t_env *env, int idx)
{
	size_t	ac;

	ac = 0;
	while (av[ac])
		ac++;
	if (ac < 1)
		return (0);
	return (g_builtins[idx](ac - 1, av + 1, env));
}

static int	exec_instruction(char *inst, t_env *env)
{
	char	**argv;
	int		ret;
	int		idx;

	if (!(argv = custom_split_arg(inst)))
	{
		free(inst);
		return (-1);
	}
	free(inst);
	ret = 0;
	if (argv[0] && (idx = is_builtins(argv[0])) >= 0)
		ret = exec_builtins(argv, env, idx);
	else if (argv[0])
		ret = exec_bin(argv, env);
	idx = 0;
	while (argv[idx])
		free(argv[idx++]);
	free(argv);
	return (ret);
}

// separate line by '|', '>', '>>', ...
void		get_all_sep(char *line, t_env *env)
{
	char	**instructions;
	size_t	i;

	if (!(instructions = custom_split_sep(line)))
	{
		free(line);
		return ;
	}
	free(line);
	i = 0;
//TODO pipe and redirection
	while (instructions[i])
	{
		// exec instruction if is not '|', '>', '>>', ...
		if (!is_sep(instructions[i]))
			env->ret = exec_instruction(instructions[i], env);
		free(instructions[i]);
		i++;
	}
	free(instructions);
}

// separate line by ';'
void		get_all_instruction(char *line, t_env *env)
{
	char	**instructions;
	size_t	i;

	if (!(instructions = custom_split_instr(line)))
	{
		free(line);
		return ;
	}
	free(line);
	i = 0;
	while (instructions[i])
		get_all_sep(instructions[i++], env);
	free(instructions);
}
