/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_instruction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 17:41:38 by niduches          #+#    #+#             */
/*   Updated: 2019/12/17 14:22:58 by niduches         ###   ########.fr       */
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

	//TODO change to custom split for "" case
	if (!(argv = ft_split(inst, " \n\t")))
	{
		free(inst);
		return (-1);
	}
	ret = 0;
	if ((indx = is_builtins(argv[0])) >= 0)
		ret = exec_builtins(argv, env, indx);
	free(inst);
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

	//TODO change to custom split for abc";"def case
	if (!(instructions = ft_split(line, ";")))
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
