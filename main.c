#include <minishell.h>

int	check_input(char *input)
{
	int		i;
	char	symbol;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			symbol = input[i];
			while (input[++i] && input[i] != symbol)
				;
			if (!input[i])
			{
				printf("Syntax error\n");
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
		if (check_input(data()->input) && data()->input[0])
		{
			add_history(data()->input);
			tokenizer(data()->input);
			token_handler();
			execute();
			destroy_arglist();
		}
		free(data()->input);
		data()->input = NULL;
	}
}
