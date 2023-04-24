/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:59:57 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/04/24 19:59:58 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	sig_handler_heredoc(int signal)
{
	if (signal == SIGQUIT)
		return ;
	if (signal == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
		exit_destroy_free();
	}
}

void	foward_list_index_close(int fd, int index, t_cleanlist *c_list)
{
	while (c_list && index != c_list->index)
		c_list = c_list->next;
	if (c_list)
		c_list->fdin = fd;
	else
		close(fd);
}

void	heredoc(t_arglist *arg_node)
{
	t_cleanlist	*t_clean;
	int			fd[2];
	char		*buff;

	signal(SIGQUIT, sig_handler_heredoc);
	signal(SIGINT, sig_handler_heredoc);
	t_clean = cleanlist()->next;
	pipe(fd);
	while (1)
	{
		buff = readline("> ");
		if (!buff)
			break ;
		if (!ft_strcmp(buff, arg_node->av[0]))
			break ;
		if (expander_checker(buff))
			buff = expander(buff);
		ft_putendl_fd(buff, fd[1]);
	}
	foward_list_index_close(fd[0], arg_node->index, t_clean);
	close(fd[1]);
	free(buff);
}

void	exec_input(t_arglist *arg_node)
{
	int			infile;
	char		*error_msg;
	t_cleanlist	*t_clean;

	t_clean = cleanlist()->next;
	if (access(arg_node->av[0], F_OK) == 0)
	{
		infile = open(arg_node->av[0], O_RDONLY, 0666);
		foward_list_index_close(infile, arg_node->index, t_clean);
	}
	else
	{
		g_exit_status = 1;
		error_msg = ft_strjoin("minishell: ", arg_node->av[0]);
		perror(error_msg);
		free(error_msg);
		exit_destroy_free();
	}
}

void	exec_outputs(t_arglist *arg_node)
{
	int			fd;
	t_cleanlist	*t_clean;

	t_clean = cleanlist()->next;
	if (arg_node->rdr == R_OUT_REP)
		fd = open(arg_node->av[0], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (arg_node->rdr == R_OUT_APP)
		fd = open(arg_node->av[0], O_WRONLY | O_CREAT | O_APPEND, 0666);
	while (t_clean && arg_node->index != t_clean->index)
		t_clean = t_clean->next;
	if (t_clean)
		t_clean->fdout = fd;
	else
		close(fd);
}
