#include <minishell.h>

static int	quote_count(char *input, int i)
{
	int		result;
	char	quote;

	quote = input[i];
	result = 0;
	while (input[++i] != quote)
		result++;
	return (result);
}

static void	quotes_pt2(char *input, int *k, char *token, char quote)
{
	t_toklist	*x;

	if (quote == '"' && expander_checker(token))
		token = expander(token);
	if (k[1] != 0 && !is_space(input[k[1] - 1]) && \
	!is_operator(input[k[1] - 1]))
	{
		x = toklist()->next;
		while (x->next)
			x = x->next;
		x->token = parse_strjoin(x->token, token);
		free(token);
	}
	else
		add_toknode(new_toknode(token, NONE), toklist());
}

static int	quotes(char *input, int i)
{
	char		*token;
	char		quote;
	int			k[2];

	k[0] = 0;
	k[1] = i;
	quote = input[i];
	token = malloc(sizeof(char) * (quote_count(input, i) + 1));
	if (!token)
		return (0);
	while (input[++i] != quote)
		token[k[0]++] = input[i];
	token[k[0]] = '\0';
	quotes_pt2(input, k, token, quote);
	return (i + 1);
}

static int	token_checker_pt2(t_toklist *t)
{
	if (t->operator != NONE)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
		return (0);
	}
	return (1);
}

static int	token_checker(void)
{
	t_toklist	*t;

	t = toklist()->next;
	if (t->operator == PIPE)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		return (0);
	}
	while (t->next)
	{
		if (t->operator != NONE && t->operator \
			!= PIPE && t->next->operator == PIPE)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(t->next->token, 2);
			ft_putendl_fd("'", 2);
			return (0);
		}
		t = t->next;
	}
	if (!token_checker_pt2(t))
		return (0);
	return (1);
}

int	tokenizer(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (is_operator(input[i]))
			i = pipe_redirections(input, i);
		else if (is_quote(input[i]))
			i = quotes(input, i);
		else if (!is_space(input[i]))
			i = alphanumeric(input, i);
		else
			i++;
	}
	if (!token_checker())
	{
		destroy_toklist();
		return (0);
	}
	create_arglist();
	create_cleanlist();
	destroy_toklist();
	return (1);
}
