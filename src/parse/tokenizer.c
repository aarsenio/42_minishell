/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:01:00 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/04/24 20:01:01 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	token_checker_pt2(t_toklist *t)
{
	char	*msg;

	msg = "minishell: syntax error near unexpected token `newline'";
	if (t->operator != NONE)
	{
		ft_putendl_fd(msg, 2);
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
	create_arglist(0, toklist()->next);
	create_cleanlist();
	destroy_toklist();
	return (1);
}
