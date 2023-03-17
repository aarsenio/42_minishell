#include <minishell.h>

char	*ft_strcpy(char *str)
{
	int		i;
	char	*s;

	i = -1;
	s = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[++i])
		s[i] = str[i];
	s[i] = '\0';
	return (s);
}
