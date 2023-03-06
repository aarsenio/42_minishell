/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarsenio <aarsenio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:37:42 by aarsenio          #+#    #+#             */
/*   Updated: 2023/03/06 17:10:00 by aarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	letter_count(char *input, int i)
{
	int	result;

	result = 0;
	while (input[i] && input[i] != ' ' && input[i] != '\n' && input[i] != '\t' \
	&& input[i] != '|' && input[i] != '"' && input[i] != '\'')
	{
		result++;
		i++;
	}
	return (result);
}

int	pipe_redirections(char *input, int i)
{
	char	*token;

	token = malloc(sizeof(char) * 2);
	if (!token)
		return (0);
	token[0] = input[i];
	token[1] = '\0';
	add_node(new_node(token), toklist());
	return (i + 1);
}

int	alphanumeric(char *input, int i)
{
	char	*token;
	int		j;

	j = 0;
	token = malloc(sizeof(char) * (letter_count(input, i) + 1));
	if (!token)
		return (0);
	while (input[i] && input[i] != ' ' && input[i] != '\n' && input[i] != '\t' \
	&& input[i] != '|' && input[i] != '"' && input[i] != '\'')
		token[j++] = input[i++];
	token[j] = '\0';
	add_node(new_node(token), toklist());
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
	if (input[t - 1] != ' ' && input[t - 1] != '\n' && input[t - 1] != '\t')
	{
		x = toklist()->next;
		while (x->next)
			x = x->next;
		x->token = ft_strjoin(x->token, token);
	}
	else
		add_node(new_node(token), toklist());
	return (i + 1);
}

void	tokenizer(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
			i = pipe_redirections(input, i);
		else if (input[i] == '"' || input[i] == '\'')
			i = quotes(input, i);
		else if (input[i] != ' ' && input[i] != '\n' && input[i] != '\t')
			i = alphanumeric(input, i);
		else
			i++;
	}
}
