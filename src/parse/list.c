/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarsenio <aarsenio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:14:05 by aarsenio          #+#    #+#             */
/*   Updated: 2023/03/06 17:06:45 by aarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_toklist	*toklist(void)
{
	static t_toklist	toklist;

	return (&toklist);
}

void	add_node(t_toklist *new, t_toklist *x)
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

t_toklist	*new_node(char *token)
{
	t_toklist	*new;

	new = malloc(sizeof(t_toklist));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->token = token;
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

void	print_toklist(void)
{
	t_toklist	*tmp;

	tmp = toklist()->next;
	while (tmp)
	{
		printf("%s\n", tmp->token);
		tmp = tmp->next;
	}
}
