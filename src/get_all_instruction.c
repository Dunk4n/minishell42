/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_instruction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 17:41:38 by niduches          #+#    #+#             */
/*   Updated: 2019/12/19 02:38:51 by niduches         ###   ########.fr       */
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

static int	exec_builtins(char **av, t_env *env, int indx)
{
	size_t	ac;

	ac = 0;
	while (av[ac])
		ac++;
	if (ac < 1)
		return (0);
	return (g_builtins[indx](ac - 1, av + 1, env));
}

static int	exec_instruction(char *inst, t_env *env)
{
	char	**argv;
	int		ret;
	int		indx;

	if (!(argv = custom_split_arg(inst)))
	{
		free(inst);
		return (-1);
	}
	free(inst);
	ret = 0;
	if (argv[0] && (indx = is_builtins(argv[0])) >= 0)
		ret = exec_builtins(argv, env, indx);
	indx = 0;
	while (argv[indx])
		free(argv[indx++]);
	free(argv);
	return (ret);
}

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
		env->ret = exec_instruction(instructions[i++], env);
	free(instructions);
}
