/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarsenio <aarsenio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:01:06 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/04/26 14:18:46 by aarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	close_fds(void)
{
	t_cleanlist	*t;

	t = cleanlist()->next;
	while (t)
	{
		if (t->fdin != -1)
			close(t->fdin);
		if (t->fdout != -1)
			close(t->fdout);
		t = t->next;
	}
}

void	exit_destroy_free(void)
{
	close_fds();
	destroy_arglist();
	destroy_envplist();
	destroy_cleanlist();
	free(data()->input);
	data()->input = NULL;
	rl_clear_history();
	exit(g_exit_status);
}

void	perror_exit(char *msg)
{
	perror(msg);
	exit_destroy_free();
}

void	exit_free_matrix(t_cleanlist *node, char **matrix, char *str)
{
	free(str);
	free_matrix(matrix);
	exit_destroy_free();
	if (node->fdin != -1)
		close(node->fdin);
	if (node->fdout != -1)
		close(node->fdout);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}
