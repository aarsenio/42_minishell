/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_lib.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarsenio <aarsenio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:00:11 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/04/26 14:35:55 by aarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	expander_checker(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] && \
		!is_space(str[i + 1]) && !is_quote(str[i + 1]))
			return (1);
	}
	return (0);
}

int	expendable_len(char *token, int i)
{
	int	len;

	len = 0;
	while (token[++i] && !is_space(token[i]) && \
	!is_quote(token[i]) && token[i] != '$')
		len++;
	return (len);
}
