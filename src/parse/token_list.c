#include <minishell.h>

void	add_toknode(t_toklist *new, t_toklist *x)
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

t_toklist	*new_toknode(char *token, t_operator operator)
{
	t_toklist	*new;

	new = malloc(sizeof(t_toklist));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->token = token;
	new->operator = operator;
	return (new);
}

void	destroy_toklist(void)
{
	t_toklist	*tmp;

	while (toklist()->next)
	{
		tmp = toklist()->next;
		toklist()->next = toklist()->next->next;
		if (tmp->token)
			free(tmp->token);
		free (tmp);
	}
}

void	print_toklist(void)
{
	t_toklist	*tmp;

	tmp = toklist()->next;
	while (tmp)
	{
		printf("%s\n", tmp->token);
		tmp = tmp->next;
	}
}
