/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 23:29:50 by nnuno-ca          #+#    #+#             */
/*   Updated: 2023/03/06 11:17:31 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cmd_env()
{
	t_envplist	*temp;

	temp = data()->envp_list;
	while (temp != NULL)
	{
		printf("%s=%s\n", temp->var_name, temp->var_value);
		temp = temp->next;
	}
	return ;
}
