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

t_arglist	*new_argnode(int ac, char **av, t_operator *op, int index)
{
	t_arglist	*new;

	new = malloc(sizeof(t_arglist));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->ac = ac;
	new->av = av;
	new->rdr = op[0];
	new->pipe = op[1];
	new->index = index;
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
		i = -1;
		if (tmp->av)
		{
			while (tmp->av[++i])
			{
				free (tmp->av[i]);
				tmp->av[i] = NULL;
			}
			free (tmp->av);
			tmp->av = NULL;
		}
		free (tmp);
		tmp = NULL;
	}
}
