/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 10:01:41 by niduches          #+#    #+#             */
/*   Updated: 2020/01/14 10:19:33 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include "minishell.h"

static int	is_direct_path(char *str)
{
	if (str[0] == '~' && (str[1] == '/' || !str[1]))
		return (0);
	while (*str)
	{
		if (*str == '/')
			return (0);
		str++;
	}
	return (1);
}

static void	get_total_path(char *total_name, char *name, t_env *env,
char *env_path)
{
	size_t	i;
	char	*path;

	if (name[0] == '~' && (name[1] == '/' || !name[1]))
	{
		while (*env_path && *env_path != '=')
			env_path++;
		if (*env_path)
			env_path++;
		ft_strcpy(total_name, env_path);
		name++;
	}
	else
	{
		if (!(path = (char*)get_env(env, "PWD")))
			return ;
		path = *((char**)path);
		i = 0;
		while (path[i] && path[i] != '=')
			i++;
		ft_strcpy(total_name, path + i + 1);
		ft_strcat(total_name, "/");
	}
	ft_strcat(total_name, name);
}

static int	good_path(char *path)
{
	struct stat	statbuff;

	if (stat(path, &statbuff) == -1)
		return (0);
	return (1);
}

static void	get_env_path(char *new_path, char *name, char *path)
{
	int	i;

	while (*path && *path != '=')
		path++;
	if (*path)
		path++;
	while (*path)
	{
		i = 0;
		while (path[i] && path[i] != ':')
			i++;
		ft_strncpy(new_path, path, i);
		ft_strcat(new_path, "/");
		ft_strcat(new_path, name);
		if (good_path(new_path))
			return ;
		*new_path = '\0';
		path += i;
		if (*path == ':')
			path++;
	}
}

void		get_exec_path(char *path, char *name, t_env *env)
{
	char	*env_path;

	path[0] = '\0';
	if (ft_strlen(name) >= 255)
		return ;
	if (!is_direct_path(name))
	{
		if (*name != '/')
		{
			if (!(env_path = (char*)get_env(env, "HOME")))
				return ;
			get_total_path(path, name, env, *((char**)env_path));
		}
		else
			ft_strcpy(path, name);
		if (!good_path(path))
			*path = '\0';
	}
	else
	{
		if (!(env_path = (char*)get_env(env, "PATH")))
			return ;
		get_env_path(path, name, *((char**)env_path));
	}
}
