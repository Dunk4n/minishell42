
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

static void	get_total_path(char *total_name, char *name, t_env *env)
{
	size_t	i;
	char	*path;

	if (name[0] == '~' && (name[1] == '/' || !name[1]))
	{
		ft_strcpy(total_name, "/home/dnicolas/");
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
	if (!is_direct_path(name))
	{
		if (*name != '/')
			get_total_path(path, name, env);
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
