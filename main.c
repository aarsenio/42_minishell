/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarsenio <aarsenio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:40:51 by aarsenio          #+#    #+#             */
/*   Updated: 2023/03/06 13:46:10 by aarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main()
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		tokenizer(input);
		print_toklist();
		destroy_toklist();
		free(input);
	}
}
