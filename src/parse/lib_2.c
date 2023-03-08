#include <minishell.h>

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	if (s1[i] != s2[i])
	{
		return ((s1[i]) - (s2[i]));
	}
	return (0);
}

t_operator	get_operator(char *op)
{
	if (ft_strcmp(op, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(op, "<") == 0)
		return (RDR_INPUT);
	else if (ft_strcmp(op, "<<") == 0)
		return (RDR_INPUT_UNTIL);
	else if (ft_strcmp(op, ">") == 0)
		return (RDR_OUT_REPLACE);
	else if (ft_strcmp(op, ">>") == 0)
		return (RDR_OUT_APPEND);
	return (NONE);
}