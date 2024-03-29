/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:59:40 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/04/24 19:59:41 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_n_flag(char *str)
{
	if (*str == '-')
		str++;
	else
		return (0);
	while (*str == 'n')
		str++;
	if (!*str)
		return (1);
	else
		return (0);
}

int	cmd_echo(t_cleanlist *node)
{
	int	i;

	i = 1;
	if (node->ac > 2 && is_n_flag(node->av[1]))
		i++;
	while (node->av[i])
	{
		printf("%s", node->av[i]);
		if (node->av[i + 1])
			printf(" ");
		i++;
	}
	if (node->ac >= 2 && !is_n_flag(node->av[1]))
		printf("\n");
	return (0);
}
