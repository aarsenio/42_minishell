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

void	print_arglist(void)
{
	t_arglist	*x;
	int			i;

	printf("ARGLIST:\n");
	x = arglist()->next;
	while (x)
	{
		i = 0;
		printf("index: %i\n", x->index);
		printf("argc: %i\n", x->ac);
		printf("redirect: %i\n", x->rdr);
		printf("pipe: %i\n", x->pipe);
		printf("frase: ");
		while (x->av[i])
			printf("%s ", x->av[i++]);
		x = x->next;
		printf("\n\n");
	}
	printf("\n");
}

void	print_cleanlist(void)
{
	t_cleanlist	*t;
	int			i;

	printf("CLEANLIST:\n");
	t = cleanlist()->next;
	while (t)
	{
		i = 0;
		printf("index: %i\n", t->index);
		printf("ac: %i\n", t->ac);
		printf("frase: ");
		while (t->av[i])
			printf("%s ", t->av[i++]);
		t = t->next;
		printf("\n\n");
	}
	printf("\n");
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
			add_history(data()->input);
			if (check_input(data()->input) && tokenizer(data()->input))
			{
				print_arglist();
				print_cleanlist();
				execute();
				destroy_cleanlist();
				destroy_arglist();
			}
		}
		else if (!data()->input)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit_destroy_free();
		}
		free(data()->input);
		data()->input = NULL;
	}
}
