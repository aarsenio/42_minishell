#include <minishell.h>

void	add_argnode(t_arglist *new, t_arglist *x)
{
	while (x)
	{
		if (!x->next)
		{
			x->next = new;
			break ;
		}
		x = x->next;
	}
}

t_arglist	*new_argnode(int ac, char **av, t_operator	prev_op, t_operator	next_op)
{
	t_arglist	*new;

	new = malloc(sizeof(t_arglist));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->ac = ac;
	new->av = av;
	new->prev_op = prev_op;
	new->next_op = next_op;
	return (new);
}

void	destroy_arglist(void)
{
	t_arglist	*tmp;
	int			i;

	while (arglist()->next)
	{
		tmp = arglist()->next;
		arglist()->next = arglist()->next->next;
		i = 0;
		if (tmp->av)
		{
			while (tmp->av[i])
				free (tmp->av[i++]);
			free (tmp->av);
		}
		free (tmp);
	}
}

void	print_arglist(void)
{
	t_arglist	*x;
	int			i;

	x = arglist()->next;
	while (x)
	{
		i = 0;
		printf("argc: %i\n", x->ac);
		printf("previous operator: %i\n", x->prev_op);
		printf("next operator: %i\n", x->next_op);
		printf("frase: ");
		while (x->av[i])
			printf("%s ", x->av[i++]);
		x = x->next;
		printf("\n\n");
	}
}
