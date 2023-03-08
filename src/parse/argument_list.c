#include <minishell.h>

t_arglist *arglist(void)
{
	static t_arglist arglist;

	return (&arglist);
}

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

t_arglist	*new_argnode(int ac, char **av, t_operator operator)
{
	t_arglist	*new;

	new = malloc(sizeof(t_arglist));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}