
#include "minishell.h"

static size_t	put_env_len(char *env_var, char *new_line)
{
	size_t	i;

	i = 0;
	while (*env_var && *env_var != '=')
		env_var++;
	if (*env_var == '=')
		env_var++;
	while (env_var[i])
	{
		new_line[i] = env_var[i];
		i++;
	}
	return (i);
}

static size_t	put_var_ret(char *line, size_t *idx, t_env *env)
{
	size_t	i;
	size_t	j;
	int		tmp;

	(*idx)++;
	tmp = env->ret;
	i = 0;
	if (tmp <= 0)
		line[i++] = (tmp < 0) ? '-' : '0';
	while (tmp)
	{
		tmp /= 10;
		i++;
	}
	j = i - 1;
	tmp = env->ret;
	while (tmp)
	{
		line[j] = ((tmp < 0) ? -(tmp % 10) : (tmp % 10)) + '0';
		tmp /= 10;
		j--;
	}
	return (i);
}

static size_t	put_var_in_line(char *line, char *new_line, size_t *idx,
t_env *env)
{
	size_t	i;
	char	tmp;
	char	**env_var;

	(*idx)++;
	if (*line == '?')
		return (put_var_ret(new_line, idx, env));
	i = 0;
	while (line[i] && !ft_isspace(line[i]) && line[i] != '$' && line[i] != '\"'
&& line[i] != '\'')
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
	return (put_env_len(*env_var, new_line));
}

size_t			put_in_line(char *line, char *new_line, t_env *env)
{
	size_t	i;
	size_t	nb;

	nb = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] && (line[i] != '$' || ft_isspace(line[i + 1]) || !line[i
+ 1] || line[i + 1] == '$' || line[i + 1] == '\"' || line[i + 1] == '\''))
			new_line[nb++] = line[i++];
		if (line[i] == '$')
			nb += put_var_in_line(line + i + 1, new_line + nb, &i, env);
	}
	return (nb);
}
