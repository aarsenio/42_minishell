/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:36:04 by nuno              #+#    #+#             */
/*   Updated: 2023/03/06 11:43:31 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cmd_echo(t_arglist	*arg)
{
	int i;

	i = 1;
	if (arg->argc >= 2 && strcmp(arg->argv[1], "-n")) //adicionar strcmp à libft
		i++;
	while (arg->argv[i])
	{
		printf(arg->argv[i]);
			if (arg->argv[i + 1])
				print(" ");
		i++;
	}
	if (arg->argc >= 2 && strcmp(arg->argv[1], "-n"))
		printf("\n");
	return ;
}
