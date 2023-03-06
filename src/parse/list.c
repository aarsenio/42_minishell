/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:14:05 by aarsenio          #+#    #+#             */
/*   Updated: 2023/03/05 20:23:23 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_data *data(void)
{
	static t_data	data;

	return (&data);
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

void	destroy_list(t_toklist *x)
{
	t_toklist	*tmp;

	while (x->next)
	{
		tmp = x->next;
		x->next = x->next->next;
		if (tmp->token)
			free(tmp->token);
		free (tmp);
	}
}

void	print_toklist(void)
{
	t_toklist *tmp;

	tmp = data()->tok_list->next;
	while (tmp)
	{
		printf("%s\n", tmp->token);
		tmp = tmp->next;
	}
}
