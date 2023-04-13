#include <minishell.h>

char	*ft_strcpy(char *str)
{
	int		i;
	char	*s;

	i = -1;
	if (!str)
		return (NULL);
	s = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!s)
		return (NULL);
	while (str[++i])
		s[i] = str[i];
	s[i] = '\0';
	return (s);
}
