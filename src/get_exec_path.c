
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include "minishell.h"

int		is_binary(char *str)
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

void	get_total_path(char *total_name, char *name, t_env *env)
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

int		good_path(char *path)
{
	struct stat	statbuff;

	if (stat(path, &statbuff) == -1)
		return (0);
	return (1);
}

void	get_exec_path(char *path, char *name, t_env *env)
{
	char	total_name[PATH_MAX + 1];

	path[0] = '\0';
	total_name[0] = '\0';
	if (!is_binary(name))
	{
		get_total_path(path, name, env);
		if (!good_path(path))
			*path = '\0';
	}
	else
	{
		//PATH
	}
}
