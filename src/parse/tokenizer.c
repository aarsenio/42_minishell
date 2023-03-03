/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarsenio <aarsenio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:37:42 by aarsenio          #+#    #+#             */
/*   Updated: 2023/03/03 17:53:57 by aarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	letter_count(char *input , int i)
{
	int result;

	result = 0;
	while (input[i] && input[i] != ' ' && input[i] != '\n' && input[i] != '\t' && input[i] != '|')
	{
		result++;
		i++;
	}
	return (result);
}

void	pipe_redirections(char *input, int i)
{
	char	*token;
	
	token = malloc(sizeof(char) * 2);
	if (!token)
			return ;
	token[0] = input[i];
	token[1] = '\0';
	add_node(new_node(token), list());
}

int	alphanumeric(char *input, int i)
{
	char	*token;
	int		j;
	
	j = 0;
	token = malloc(sizeof(char) * (letter_count(input, i) + 1));
	if (!token)
		return (0);
	while (input[i] && input[i] != ' ' && input[i] != '\n' && input[i] != '\t' && input[i] != '|')
		token[j++] = input[i++];
	token[j] = '\0';
	add_node(new_node(token), list());
	return (i);
}

void	tokenizer(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
			pipe_redirections(input, i++);
		else if (input[i] != ' ' && input[i] != '\n' && input[i] != '\t' )
			i = alphanumeric(input, i);
		else
			i++;
	}
}
