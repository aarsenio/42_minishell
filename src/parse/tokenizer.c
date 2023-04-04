#include <minishell.h>

int	letter_count(char *input, int i)
{
	int	result;

	result = 0;
	while (input[i] && !is_space(input[i]) && !is_operator(input[i]) && \
	!is_quote(input[i]))
	{
		result++;
		i++;
	}
	return (result);
}

int	pipe_redirections(char *input, int i)
{
	char	*token;
	char	symbol;

	if (input[i] == '>' || input[i] == '<')
	{
		symbol = input[i];
		if (input[i + 1] == symbol)
		{
			token = malloc(sizeof(char) * 3);
			if (!token)
				return (0);
			token[0] = input[i];
			token[1] = input[i];
			token[2] = '\0';
			add_toknode(new_toknode(token, get_operator(token)), toklist());
			return (i + 2);
		}
	}
	token = malloc(sizeof(char) * 2);
	if (!token)
		return (0);
	token[0] = input[i];
	token[1] = '\0';
	add_toknode(new_toknode(token, get_operator(token)), toklist());
	return (i + 1);
}

int	alphanumeric(char *input, int i)
{
	char		*token;
	int			j;
	int			tmp;
	t_toklist	*x;

	j = 0;
	tmp = i;
	token = malloc(sizeof(char) * (letter_count(input, i) + 1));
	if (!token)
		return (0);
	while (input[i] && !is_space(input[i]) && !is_operator(input[i]) && \
	!is_quote(input[i]))
		token[j++] = input[i++];
	token[j] = '\0';
	if (expander_checker(token))
		token = expander(token);
	if (tmp != 0 && is_quote(input[tmp - 1]))
	{
		x = toklist()->next;
		while (x->next)
			x = x->next;
		x->token = parse_strjoin(x->token, token);
		free(token);
	}
	else
		add_toknode(new_toknode(token, NONE), toklist());
	return (i);
}

int	quote_count(char *input, int i)
{
	int		result;
	char	quote;

	quote = input[i];
	result = 0;
	while (input[++i] != quote)
		result++;
	return (result);
}

int	quotes(char *input, int i)
{
	char		*token;
	char		quote;
	int			j;
	int			t;
	t_toklist	*x;

	j = 0;
	t = i;
	quote = input[i];
	token = malloc(sizeof(char) * (quote_count(input, i) + 1));
	if (!token)
		return (0);
	while (input[++i] != quote)
		token[j++] = input[i];
	token[j] = '\0';
	if (quote == '"' && expander_checker(token))
		token = expander(token);
	if (t != 0 && !is_space(input[t - 1]) && !is_operator(input[t - 1]))
	{
		x = toklist()->next;
		while (x->next)
			x = x->next;
		x->token = parse_strjoin(x->token, token);
		free(token);
	}
	else
		add_toknode(new_toknode(token, NONE), toklist());
	return (i + 1);
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
	token_handler();
	return (1);
}
