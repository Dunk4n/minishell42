
#include "minishell.h"

static int		is_env_variable(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] != '\0' && !ft_isspace(line[i + 1]))
			return (1);
		i++;
	}
	return (0);
}

static size_t	env_len(char *env_var)
{
	size_t	i;

	i = 0;
	while (*env_var && *env_var != '=')
		env_var++;
	if (*env_var == '=')
		env_var++;
	while (env_var[i])
		i++;
	return (i);
}

static size_t	get_var_len(char *line, size_t *idx, t_env *env)
{
	size_t	i;
	char	tmp;
	char	**env_var;

	(*idx)++;
	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	if (!i)
		return (0);
	(*idx) += i;
	tmp = line[i];
	line[i] = '\0';
	if (!(env_var = get_env(env, line)))
	{
		line[i] = tmp;
		return (0);
	}
	line[i] = tmp;
	return (env_len(*env_var));
}

static size_t	get_len_envline(char *line, t_env *env)
{
	size_t	i;
	size_t	nb;

	nb = 0;
	i = 0;
	printf("[%s]\n", line);
	while (line[i])
	{
		while (line[i] && (line[i] != '$' || ft_isspace(line[i + 1]) ||
!line[i + 1]))
		{
			i++;
			nb++;
		}
		if (line[i] == '$')
			nb += get_var_len(line + i + 1, &i, env);
	}
	return (nb);
}

char			*to_line_env(char *line, t_env *env)
{
	char	*new_line;
	int		len;

	if (!is_env_variable(line))
		return (line);
	len = get_len_envline(line, env);
	printf("%d\n", len);
	if (!(new_line = malloc((len + 1) * sizeof(char))))
		return (line);
	new_line[len] = '\0';
	put_in_line(line, new_line, env);
	free(line);
	return (new_line);
}
