/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarsenio <aarsenio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:01:16 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/04/26 12:54:16 by aarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_envplstsize(void)
{
	t_envplist	*temp;
	int			size;

	temp = envplist()->next;
	size = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		size++;
	}
	return (size);
}

void	update_envp(void)
{
	int			i;
	t_envplist	*t;

	i = 0;
	t = envplist()->next;
	if (data()->envp)
		free(data()->envp);
	data()->envp = malloc(sizeof(char *) * (ft_envplstsize() + 1));
	while (t)
	{
		data()->envp[i++] = t->full;
		t = t->next;
	}
	data()->envp[i] = NULL;
}

void	init_shell(char **envp)
{
	init_envplist(envp);
	update_envp();
}
