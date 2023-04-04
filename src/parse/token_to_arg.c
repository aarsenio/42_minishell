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

void	token_handler(void)
{
	t_toklist	*x;
	t_operator	rdr;
	t_operator	pipe;
	char		**av;
	int			i;
	int			ac;

	x = toklist()->next;
	while (x)
	{
		rdr = NONE;
		pipe = NONE;
		ac = 0;
		if (x->operator != NONE && x->operator != PIPE)
		{
			rdr = x->operator;
			x = x->next;
			av = malloc(sizeof(char*) * 2);
			av[0] = ft_strcpy(x->token);
			av[1] = NULL;
			x = x->next;
			ac = 1;
		}
		else
		{
			av = malloc(sizeof(char*) * arg_counter(x));
			if (!av)
				return ;
			i = 0;
			while (x && x->operator == NONE)
			{
				if (x->token)
				{
					av[i++] = ft_strcpy(x->token);
					ac++;
				}
				x = x->next;
			}
			av[i] = NULL;
		}
		if (x && x->operator == PIPE)
		{
			pipe = x->operator;
			x = x->next;
		}
		add_argnode(new_argnode(ac, av, rdr, pipe), arglist());
	}
	destroy_toklist();
}
