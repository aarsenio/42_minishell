/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:59:53 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/04/24 19:59:54 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_valid(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			return (0);
	return (1);
}

void	destroy_node(char *var)
{
	t_envplist	*t;
	t_envplist	*f;

	t = envplist();
	while (t)
	{
		if (t->next && !ft_strcmp(t->next->var_name, var))
		{
			f = t->next;
			free(t->next->full);
			free(t->next->var_name);
			free(t->next->var_value);
			if (t->next->next)
				t->next = t->next->next;
			else
				t->next = NULL;
			free(f);
		}
		t = t->next;
	}
}

void	cmd_unset(t_cleanlist *node)
{
	int			i;

	i = 0;
	g_exit_status = 0;
	while (node->av[++i])
	{
		if (!is_valid(node->av[i]))
		{
			g_exit_status = 2;
			ft_putstr_fd("bash: unset: `", 2);
			ft_putstr_fd(node->av[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
		else
			destroy_node(node->av[i]);
	}
	update_envp();
}
