
#include "minishell.h"

static int	in_set(char c, char const *charset)
{
	size_t	i;

	i = 0;
	while (charset[i])
		if (charset[i++] == c)
			return (1);
	return (0);
}

static int	get_nb(char const *s, char *set)
{
	int		nb;
	int		i;
	char	sep;
	char	in[2];

	*((short*)in) = 0;
	sep = 1;
	nb = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] == '\"') && (i == 0 || s[i - 1] != '\\'))
			in[0] = (in[0] == 0) ? 1 : 0;
		if ((s[i] == '\'') && (i == 0 || s[i - 1] != '\\'))
			in[1] = (in[1] == 0) ? 1 : 0;
		if (in_set(s[i], set) && !*((short*)in) && !sep)
			sep = 1;
		if (!in_set(s[i], set) && sep == 1)
		{
			sep = 0;
			nb++;
		}
		i++;
	}
	return (nb);
}

static char	*fill_in(char const *s, int *i, char *in, char *set)
{
	int		j;
	int		tmp;
	char	*line;

	j = 0;
	while (in_set(s[*i], set))
		(*i)++;
	j = 0;
	while (s[*i + j] && (!in_set(s[*i + j], set) || *((short*)in)))
	{
		if ((s[*i + j] == '\"') && (*i + j == 0 || s[*i + j - 1] != '\\'))
			in[0] = (in[0] == 0) ? 1 : 0;
		if ((s[*i + j] == '\'') && (*i + j == 0 || s[*i + j - 1] != '\\'))
			in[1] = (in[1] == 0) ? 1 : 0;
		j++;
	}
	if (!(line = malloc((j + 1) * sizeof(char))))
		return (NULL);
	line[j] = '\0';
	tmp = j;
	while (--j >= 0)
		line[j] = s[*i + j];
	*i += tmp;
	return (line);
}

char	**custom_split(char const *str, char *set)
{
	int		i;
	int		word;
	int		nb;
	char	in[2];
	char	**array;

	nb = get_nb(str, set);
	if (!(array = malloc((nb + 1) * sizeof(char*))))
		return (NULL);
	i = 0;
	word = 0;
	*((short*)in) = 0;
	while (word < nb)
	{
		if (!(array[word] = fill_in(str, &i, in, set)))
		{
			while (--word >= 0)
				free(array[word]);
			free(array);
			return (NULL);
		}
		word++;
	}
	array[word] = NULL;
	return (array);
}
