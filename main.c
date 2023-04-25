/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:01:56 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/04/24 20:01:57 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_exit_status = 0;

static int	white_spaces(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
		if (input[i] != ' ' || input[i] != '\t' || input[i] != '\n')
			return (0);
	return (1);
}

static int	check_input(char *input)
{
	int		i;
	char	symbol;

	i = -1;
	if (white_spaces(input))
		return (0);
	while (input && input[++i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			symbol = input[i];
			while (input[++i] && input[i] != symbol)
				;
			if (!input[i])
			{
				g_exit_status = 1;
				ft_putendl_fd("minishell: Syntax error: unclosed quotes", 2);
				return (0);
			}
		}
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	init_shell(envp);
	while (1)
	{
		data()->input = readline("minishell$ ");
		if (data()->input && data()->input[0])
		{
			signal(SIGINT, SIG_IGN);
			add_history(data()->input);
			if (check_input(data()->input) && tokenizer(data()->input))
			{
				print_arglist();
				execute();
				destroy_cleanlist();
				destroy_arglist();
			}
			signal(SIGINT, sig_handler);
		}
		else if (!data()->input)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit_destroy_free();
		}
		free(data()->input);
	}
}
