/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:00:48 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/04/24 20:00:49 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	add_argnode(t_arglist *new, t_arglist *x)
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

t_arglist	*new_argnode(int ac, char **av, t_operator *op, int index)
{
	t_arglist	*new;

	new = malloc(sizeof(t_arglist));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->ac = ac;
	new->av = av;
	new->rdr = op[0];
	new->pipe = op[1];
	new->index = index;
	return (new);
}

void	destroy_arglist(void)
{
	t_arglist	*tmp;
	int			i;

	while (arglist()->next)
	{
		tmp = arglist()->next;
		arglist()->next = arglist()->next->next;
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

void print_arglist(void)
{
	int	i = -1;
	t_arglist *t;

	t = arglist()->next;
	while (t)
	{
		printf("ac = %i\n", t->ac);
		printf("index = %i\n", t->index);
		printf("pipe = %i\n", t->pipe);
		printf("rdr = %i\n", t->rdr);
		while (t->av[++i])
			printf("frase = %s", t->av[i]);
		printf("\n");
		t = t->next;
	}
}
