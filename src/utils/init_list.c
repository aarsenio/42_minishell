/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:01:14 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/04/24 20:01:15 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_envplist	*envplist(void)
{
	static t_envplist	envplist;

	return (&envplist);
}

t_arglist	*arglist(void)
{
	static t_arglist	arglist;

	return (&arglist);
}

t_toklist	*toklist(void)
{
	static t_toklist	toklist;

	return (&toklist);
}

t_cleanlist	*cleanlist(void)
{
	static t_cleanlist	cleanlist;

	return (&cleanlist);
}

t_data	*data(void)
{
	static t_data		data;

	return (&data);
}
