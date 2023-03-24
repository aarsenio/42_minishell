#include <minishell.h>

int	expander_checker(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '$' && str[i + 1] && !is_space(str[i + 1]))
			return (1);
	return (0);
}

int	expendable_len(char *token, int i)
{
	int	len;

	len = 0;
	while (token[++i] && !is_space(token[i]) && token[i] != '$')
		len++;
	return (len);
}
