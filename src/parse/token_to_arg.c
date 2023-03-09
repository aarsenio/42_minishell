#include <minishell.h>

int	arg_counter(t_toklist *x)
{
	int	result;

	result = 0;
	while (x && x->operator == 0)
	{
		result++;
		x = x->next;	
	}
	return (result + 1);
}

void	token_handler(void)
{
	t_toklist	*x;
	t_operator	op;
	char		**av;
	int			i;
	int			j;
	int			ac;

	x = toklist()->next;
	op = NONE;
	while (x)
	{
		if (x->operator != NONE)
		{
			op = x->operator;
			x = x->next;
		}
		av = malloc(sizeof(char*) * arg_counter(x));
		i = 0;
		ac = 0;
		while (x && x->operator == NONE)
		{
			av[i] = malloc(sizeof(char) * (ft_strlen(x->token) + 1));
			j = -1;
			while (x->token[++j])
				av[i][j] = x->token[j];
			av[i++][j] = '\0';
			ac++;
			x = x->next;
		}
		av[i] = NULL;
		add_argnode(new_argnode(ac, av, op), arglist());
	}
	destroy_toklist();
}
