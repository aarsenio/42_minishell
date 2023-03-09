/*
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
				return (0);
		}
	}
	return (1);
}

int	main(int ac, char **av)
{
	char	*input;

	(void)ac;
	(void)av;
	while (1)
	{
		input = readline("minishell$ ");
		if (check_input(input))
		{
			tokenizer(input);
			print_toklist();
			destroy_toklist();
		}
		else
			printf("Syntax error\n");
		free(input);
	}
}
*/
