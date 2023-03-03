/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarsenio <aarsenio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:37:42 by aarsenio          #+#    #+#             */
/*   Updated: 2023/03/03 13:03:01 by aarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	letter_count(char *input , int i)
{
	int result;

	result = 0;
	while (input[i] && input[i] != ' ' && input[i] != '\n' && input[i] != '\t')
	{
		result++;
		i++;
	}
	return (result);
}

void	tokenizer(char *input)
{
	int		i;
	int		j;
	char	*token;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\n' && input[i] != '\t')
		{
			token = malloc(sizeof(char) * (letter_count(input, i) + 1));
			if (!token)
				return ;
			j = 0;
			while (input[i] && input[i] != ' ' && input[i] != '\n' && input[i] != '\t')
				token[j++] = input[i++];
			token[j] = '\0';
			add_node(new_node(token), list());
		}
		else
			i++;
	}
}
