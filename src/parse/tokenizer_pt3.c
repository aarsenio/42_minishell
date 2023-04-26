/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_pt3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarsenio <aarsenio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:00:59 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/04/26 15:19:36 by aarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int			i[3];

	if (quote == '"' && expander_checker(token))
		token = expander(token, NULL, i);
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

int	quotes(char *input, int i)
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
