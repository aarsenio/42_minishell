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
	t_operator	prev_op;
	t_operator	next_op;
	char		**av;
	int			i;
	int			j;
	int			ac;

	x = toklist()->next;
	prev_op = NONE;
	while (x)
	{
		next_op = NONE;
		if (x->operator != NONE)
		{
			prev_op = x->operator;
			x = x->next;
		}
		av = malloc(sizeof(char*) * arg_counter(x));
		if (!av)
			return ;
		i = 0;
		ac = 0;
		while (x && x->operator == NONE)
		{
			if (x->token)
			{
				av[i] = malloc(sizeof(char) * (ft_strlen(x->token) + 1));
				j = -1;
				while (x->token[++j])
					av[i][j] = x->token[j];
				av[i++][j] = '\0';
				ac++;
			}
			x = x->next;
		}
		av[i] = NULL;
		if (x)
			next_op = x->operator;
		add_argnode(new_argnode(ac, av, prev_op, next_op), arglist());
	}
	destroy_toklist();
}
