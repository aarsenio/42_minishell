/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:01:04 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/04/24 20:01:05 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	add_envpnode(t_envplist *new, t_envplist *x)
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

t_envplist	*new_envpnode(char *name, char *value, char *full)
{
	t_envplist	*new;

	new = malloc(sizeof(t_envplist));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->var_name = name;
	new->var_value = value;
	new->full = full;
	return (new);
}

void	destroy_envplist(void)
{
	t_envplist	*tmp;

	while (envplist()->next)
	{
		tmp = envplist()->next;
		envplist()->next = envplist()->next->next;
		if (tmp->var_name)
			free(tmp->var_name);
		if (tmp->var_value)
			free(tmp->var_value);
		if (tmp->full)
			free(tmp->full);
		free (tmp);
	}
	free(data()->envp);
}

void	order_envplist(void)
{
	t_envplist	*t1;
	t_envplist	*t2;
	int			counter;

	t1 = envplist()->next;
	while (t1)
	{
		counter = 0;
		t2 = envplist()->next;
		while (t2)
		{
			if (ft_strcmp(t1->var_name, t2->var_name) > 0)
				counter++;
			t2 = t2->next;
		}
		t1->pos = counter;
		t1 = t1->next;
	}
}

t_envplist	*fetch_node(char *str)
{
	t_envplist	*t;
	char		*name;

	t = envplist()->next;
	name = copy_name(str);
	while (t)
	{
		if (!ft_strcmp(name, t->var_name))
		{
			free(name);
			return (t);
		}
		t = t->next;
	}
	free(name);
	return (NULL);
}
