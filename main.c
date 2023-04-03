#include <minishell.h>

int	exit_status = 0;

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
		if (data()->input[0])
		{
			add_history(data()->input);
			if (check_input(data()->input) && tokenizer(data()->input))
			{
				print_arglist();
				execute();
				destroy_arglist();
			}
		}
		free(data()->input);
		data()->input = NULL;
	}
}
