/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarsenio <aarsenio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:59:49 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/04/26 14:05:09 by aarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_num_long_long(char *s)
{
	int			i;

	i = 0;
	while (s[i] && is_space(s[i]))
		i++;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] && !is_space(s[i]))
		if ((s[i] < '0' || s[i++] > '9'))
			return (0);
	while (s[i] && is_space(s[i]))
		i++;
	if (s[i])
		return (0);
	return (1);
}

int	cmd_exit(t_cleanlist *node)
{
	int	status;

	status = 0;
	if (node->av[1] && !is_num_long_long(node->av[1]))
	{
		ft_putstr_fd("minishell: exit:", 2);
		ft_putstr_fd(node->av[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		status = 2;
	}
	else if (node->ac > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	else if (node->av[1])
		status = ft_atoll(node->av[1]);
	ft_putendl_fd("exit", STDOUT_FILENO);
	destroy_arglist();
	destroy_envplist();
	destroy_cleanlist();
	free(data()->input);
	rl_clear_history();
	exit((unsigned char)status);
}
