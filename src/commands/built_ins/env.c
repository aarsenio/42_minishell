/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:59:43 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/04/24 19:59:44 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	cmd_env(void)
{
	t_envplist	*x;

	x = envplist()->next;
	while (x)
	{
		if (x->var_value)
			printf("%s=%s\n", x->var_name, x->var_value);
		x = x->next;
	}
	return (0);
}
