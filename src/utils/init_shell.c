/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:01:16 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/04/24 20:01:17 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}

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
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	init_envplist(envp);
	update_envp();
}
