#include <minishell.h>

int	expander_checker(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '$')
			return (1);
	return (0);
}

int	expendable_len(char *token, int i)
{
	int	len;

	len = 0;
	while (token[++i] && !is_space(token[i]))
		len++;
	return (len);
}

char	*expander(char *token)
{
	int		i;
	char	*tmp;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$')
	}
}
