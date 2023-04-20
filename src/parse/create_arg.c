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

static char	**create_arg_redirect(t_toklist *x, char **av)
{
	data()->op[0] = x->operator;
	x = x->next;
	av = malloc(sizeof(char *) * 2);
	if (!av)
		return (NULL);
	av[0] = ft_strcpy(x->token);
	av[1] = NULL;
	x = x->next;
	data()->i = data()->i + 2;
	data()->ac = 1;
	return (av);
}

static char	**create_arg_no_redirect(t_toklist *x, char **av, int i)
{
	av = malloc(sizeof(char *) * arg_counter(x));
	if (!av)
		return (NULL);
	while (x && x->operator == NONE)
	{
		if (x->token)
		{
			av[i++] = ft_strcpy(x->token);
			data()->ac++;
		}
		x = x->next;
		data()->i++;
	}
	av[i] = NULL;
	if (x && x->operator == PIPE)
	{
		data()->op[1] = x->operator;
		x = x->next;
		data()->i++;
	}
	return (av);
}

void	create_arglist(void)
{
	t_toklist	*x;
	int			i;
	char		**av;

	x = toklist()->next;
	i = 0;
	while (x)
	{
		data()->op[0] = NONE;
		data()->op[1] = NONE;
		i = 0;
		if (x->operator != NONE && x->operator != PIPE)
			av = create_arg_redirect(x, av);
		else
			av = create_arg_no_redirect(x, av, 0);
		while (x && data()->old_i <= data()->i)
			x = x->next;
		add_argnode(new_argnode(data()->ac, av, data()->op, i), arglist());
		if (x && x->operator == PIPE)
			i++;
	}
}
