/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarsenio <aarsenio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:14:05 by aarsenio          #+#    #+#             */
/*   Updated: 2023/03/03 11:11:33 by aarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list *list(void)
{
	static t_list	list;

	return (&list);
}

void	add_node(t_list *new, t_list *x)
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

t_list	*new_node(char *token)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->token = token;
	return (new);
}

void	destroy_list(t_list *x)
{
	t_list	*tmp;
	
	while (x->next)
	{
		tmp = x->next;
		x->next = x->next->next;
		free (tmp);
	}
}

void	print_list(void)
{
	t_list *tmp;

	tmp = list()->next;
	while (tmp)
	{
		printf("%s\n", tmp->token);
		tmp = tmp->next;
	}
}
