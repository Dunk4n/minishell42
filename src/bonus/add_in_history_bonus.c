
#include <unistd.h>
#include "minishell_bonus.h"

int		add_in_history(t_env *env, char *line)
{
	char	*tmp;
	char	*tmp2;
	size_t	i;

	if (!line || !env || !ft_strcmp(line, env->hist[0]))
		return (1);
	if (!(tmp2 = ft_strdup(line)))
		return (0);
	i = 0;
	while (i < HISTORY_SIZE && tmp2)
	{
		tmp = env->hist[i];
		env->hist[i] = tmp2;
		tmp2 = NULL;
		if (i + 1 < HISTORY_SIZE)
		{
			tmp2 = env->hist[i + 1];
			env->hist[i + 1] = tmp;
		}
		else
			free(tmp);
		i++;
	}
	return (1);
}
