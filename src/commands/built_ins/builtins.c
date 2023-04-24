/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:59:33 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/04/24 19:59:34 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtins(t_cleanlist *node)
{
	if (!node->av[0])
		return (0);
	if (!ft_strcmp(node->av[0], "echo"))
		g_exit_status = cmd_echo(node);
	else if (!ft_strcmp(node->av[0], "cd"))
		g_exit_status = cmd_cd(node);
	else if (!ft_strcmp(node->av[0], "pwd"))
		g_exit_status = cmd_pwd();
	else if (!ft_strcmp(node->av[0], "export"))
		cmd_export(node);
	else if (!ft_strcmp(node->av[0], "unset"))
		cmd_unset(node);
	else if (!ft_strcmp(node->av[0], "env"))
		g_exit_status = cmd_env();
	else if (!ft_strcmp(node->av[0], "exit"))
		g_exit_status = cmd_exit(node);
	else
		return (0);
	return (1);
}
