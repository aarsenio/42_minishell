#include <minishell.h>

int	arg_counter(t_toklist *x)
{
	int	result;

	result = 0;
	while (x)
	{
		if (x->operator != 0)
			break ;
		result++;
		x = x->next;	
	}
	return (result + 1);
}

void	token_handler(void)
{
	t_toklist	*x;
	t_operator	tmp;
	char		**av;
	int			i;
	int			ac;

	x = toklist()->next;
	tmp = x->operator;
	while (x)
	{
		i = 0;
		av = malloc(sizeof(char*) * arg_counter(x));
		while (x && x->operator != NONE)
		{
			av[i++] = x->token;
			ac++;
			x = x->next;
		}
		add_argnode(new_argnode(ac, av, tmp), arglist());
		if (x->operator != NONE)
			tmp = x->operator;
		x = x->next;
	}
	destroy_toklist();
}
