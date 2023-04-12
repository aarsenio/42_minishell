#include <minishell.h>

int	g_exit_status = 0;

int	check_input(char *input)
{
	int		i;
	char	symbol;

	i = -1;
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
		if (data()->input[0])
		{
			add_history(data()->input);
			if (check_input(data()->input) && tokenizer(data()->input))
			{
				//print_arglist();
				print_cleanlist();
				execute();
				destroy_cleanlist();
				destroy_arglist();
			}
		}
		free(data()->input);
		data()->input = NULL;
	}
}
