/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:00:49 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/04/24 20:00:50 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	add_cleannode(t_cleanlist *new, t_cleanlist *x)
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

t_cleanlist	*new_cleannode(int ac, char **av, int index, t_operator rdr)
{
	t_cleanlist	*new;

	new = malloc(sizeof(t_cleanlist));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->ac = ac;
	new->av = av;
	new->index = index;
	new->rdr = rdr;
	return (new);
}

void	destroy_cleanlist(void)
{
	t_cleanlist	*tmp;
	int			i;

	while (cleanlist()->next)
	{
		tmp = cleanlist()->next;
		cleanlist()->next = cleanlist()->next->next;
		i = -1;
		if (tmp->av)
		{
			while (tmp->av[++i])
			{
				free (tmp->av[i]);
				tmp->av[i] = NULL;
			}
			free (tmp->av);
			tmp->av = NULL;
		}
		free (tmp);
		tmp = NULL;
	}
}
