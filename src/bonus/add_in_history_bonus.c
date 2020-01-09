
#include <unistd.h>
#include "minishell_bonus.h"

void	charge_from_history(char *line, t_cursor *cur, t_env *env)
{
	ft_strncpy(line, env->hist[env->idx], LINE_SIZE);
	cur->x = cur->startx;
	cur->y = cur->starty;
	cur->idx = 0;
	cur->col = 0;
	cur->line = 0;
	while (line[cur->idx] && cur->idx < LINE_SIZE)
	{
		cur->col++;
		if (line[cur->idx] == '\n')
		{
			line[cur->idx] = '\0';
			cur->line++;
			cur->col = 0;
		}
		cur->idx++;
	}
	cur->line_max = cur->line + 1;
	cur->line_size = cur->idx;
	update_cursor_pos(cur);
}

int		add_in_history(t_env *env, char *line)
{
	char	*tmp;
	char	*tmp2;
	size_t	i;

	if (!line || !env || !ft_strcmp(line, env->hist[0]))
		return (1);
	tmp2 = line;
	i = 0;
	while (i < HISTORY_SIZE && tmp2)
	{
		tmp = env->hist[i];
		env->hist[i] = tmp2;
		tmp2 = tmp;
		i++;
		if (i >= HISTORY_SIZE)
		{
			free(tmp2);
			tmp2 = NULL;
		}
	}
	return (1);
}
