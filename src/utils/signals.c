/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarsenio <aarsenio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:54:19 by aarsenio          #+#    #+#             */
/*   Updated: 2023/04/26 13:04:22 by aarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	sig_handler_interactive(int signal)
{
	if (signal == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	sig_handler(int sig)
{
	if (sig == SIGQUIT)
		write(1, "Quit (core dumped)", 18);
	write(1, "\n", 1);
}

void	not_interactive(void)
{
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
}

void	interactive(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler_interactive);
}
