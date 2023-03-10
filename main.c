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
	char	*input;

	(void)ac;
	(void)av;
	(void)envp;
	while (1)
	{
		input = readline("minishell$ ");
		if (check_input(input) && input[0] != '\0')
		{
			tokenizer(input);
			token_handler();
			print_arglist();
			destroy_arglist();
		}
		free(input);
	}
}
