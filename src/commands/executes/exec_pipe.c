/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:59:56 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/04/24 19:59:57 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exec_pipe(t_cleanlist *node)
{
	int		pipe_fd[2];
	int		pid;

	if (pipe(pipe_fd) == -1)
		perror_exit("Error creating pipe");
	pid = fork();
	if (pid == -1)
		perror_exit("Error forking in exec_pipe");
	if (pid == 0)
	{
		if (node->fdout == -1)
			dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		exec_executables(node);
	}
	else
	{
		if (node->next->fdin == -1)
			dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
}
