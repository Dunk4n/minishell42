/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 19:50:01 by niduches          #+#    #+#             */
/*   Updated: 2019/12/17 14:23:47 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

static void	free_tab(char **tabl, size_t indice)
{
	if (indice > 0)
	{
		while (--indice > 0)
			free(tabl[indice]);
	}
	free(tabl);
}

static char	**copy_env(char **arg_env, size_t *nb_env)
{
	size_t	i;
	char	**env;

	i = 0;
	while (arg_env[i])
		i++;
	if (!(env = malloc((i + 1) * sizeof(char*))))
		return (NULL);
	env[i] = NULL;
	i = 0;
	while (arg_env[i])
	{
		if (!(env[i] = ft_strdup(arg_env[i])))
		{
			free_tab(env, i);
			return (NULL);
		}
		i++;
	}
	*nb_env = i;
	return (env);
}

static int	init_term(t_env *env)
{
	char	*term_name;

	if (!(term_name = (char*)get_env(env, "TERM")))
		return (0);
	term_name = *((char**)term_name);
	while (*term_name && *term_name != '=')
		term_name++;
	if (*term_name)
		term_name++;
	if (tgetent(NULL, term_name) < 1)
		return (0);
	tcgetattr(STDIN_FILENO, &(env->termios_save));
	tcgetattr(STDIN_FILENO, &(env->termios));
	env->termios.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &(env->termios));
	return (1);
}

t_env		init(char **arg_env)
{
	t_env	env;
	size_t	i;

	env.env = NULL;
	env.ret = 0;
	env.nb_env = 0;
	if (!(env.env = copy_env(arg_env, &env.nb_env)))
		return (env);
	if (!init_term(&env))
	{
		free_env(&env);
		return (env);
	}
	env.size = 0;
	env.idx = 0;
	ft_bzero(env.tmp, LINE_SIZE);
	i = 0;
	while (i < 500)
		env.hist[i++] = NULL;
	return (env);
}
