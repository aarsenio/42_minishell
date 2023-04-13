#include <minishell.h>

void	add_cleannode(t_cleanlist *new, t_cleanlist *x)
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

t_cleanlist	*new_cleannode(int ac, char **av, int index, t_operator rdr)
{
	t_cleanlist	*new;

	new = malloc(sizeof(t_cleanlist));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->ac = ac;
	new->av = av;
	new->index = index;
	new->rdr = rdr;
	return (new);
}

void	destroy_cleanlist(void)
{
	t_cleanlist	*tmp;
	int			i;

	while (cleanlist()->next)
	{
		tmp = cleanlist()->next;
		cleanlist()->next = cleanlist()->next->next;
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

void	print_cleanlist(void)
{
	t_cleanlist *t;
	int			i;

	t = cleanlist()->next;
	while (t)
	{
		i = 0;
		printf("rdr: %i\n", t->rdr);
		printf("index: %i\n", t->index);
		printf("ac: %i\n", t->ac);
		printf("frase: ");
		while (t->av[i])
			printf("%s ", t->av[i++]);
		t = t->next;
		printf("\n\n");
	}
}