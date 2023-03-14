#include <minishell.h>

int	is_quote(char x)
{
	if (x == '"' || x == '\'')
		return (1);
	return (0);
}

int	is_pipe_rdr(char x)
{
	if (x == '|' || x == '>' || x == '<')
		return (1);
	return (0);
}

int	is_space(char x)
{
	if (x == ' ' || x == '\n' || x == '\t')
		return (1);
	return (0);
}

char	*parse_strjoin(char const *s1, char const *s2)
{
	char		*newstr;
	int			i;
	int			j;
	t_toklist	*x;

	j = -1;
	i = -1;
	if (!s1 || !s2)
		return (NULL);
	newstr = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	while (s1[++i])
		newstr[i] = s1[i];
	while (s2[++j])
		newstr[i++] = s2[j];
	newstr[i] = '\0';
	x = toklist()->next;
	while (x->next)
		x = x->next;
	free(x->token);
	x->token = NULL;
	return (newstr);
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
