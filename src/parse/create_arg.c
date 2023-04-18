#include <minishell.h>

int	arg_counter(t_toklist *x)
{
	int	result;

	result = 0;
	while (x && x->operator == NONE)
	{
		result++;
		x = x->next;
	}
	return (result + 1);
}

void	create_arglist(void)
{
	t_toklist	*x;
	t_operator	op[2];
	int			i[2];
	char		**av;
	int			ac;

	x = toklist()->next;
	i[1] = 0;
	while (x)
	{
		op[0] = NONE;
		op[1] = NONE;
		ac = 0;
		if (x->operator != NONE && x->operator != PIPE)
		{
			op[0] = x->operator;
			x = x->next;
			av = malloc(sizeof(char *) * 2);
			av[0] = ft_strcpy(x->token);
			av[1] = NULL;
			x = x->next;
			ac = 1;
		}
		else
		{
			av = malloc(sizeof(char *) * arg_counter(x));
			if (!av)
				return ;
			i[0] = 0;
			while (x && x->operator == NONE)
			{
				if (x->token)
				{
					av[i[0]++] = ft_strcpy(x->token);
					ac++;
				}
				x = x->next;
			}
			av[i[0]] = NULL;
		}
		if (x && x->operator == PIPE)
		{
			op[1] = x->operator;
			x = x->next;
		}
		add_argnode(new_argnode(ac, av, op, i[1]), arglist());
		if (x && x->operator == PIPE)
			i[1]++;
	}
}
