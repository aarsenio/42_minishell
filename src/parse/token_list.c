/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarsenio <aarsenio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:00:56 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/04/26 14:31:56 by aarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	add_toknode(t_toklist *new, t_toklist *x)
{
	while (x)
	{
		if (!x->next)
		{
			x->next = new;
			break ;
		}
		x = x->next;
	}
}

t_toklist	*new_toknode(char *token, t_operator operator)
{
	t_toklist	*new;

	new = malloc(sizeof(t_toklist));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->token = token;
	new->operator = operator;
	return (new);
}

void	destroy_toklist(void)
{
	t_toklist	*tmp;

	while (toklist()->next)
	{
		tmp = toklist()->next;
		toklist()->next = toklist()->next->next;
		if (tmp->token)
			free(tmp->token);
		free (tmp);
	}
}

t_toklist	*lst_node(void)
{
	t_toklist	*t;

	t = toklist();
	while (t && t->next)
		t = t->next;
	return (t);
}
