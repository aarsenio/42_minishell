#include <minishell.h>

void	add_envpnode(t_envplist *new, t_envplist *x)
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

t_envplist	*new_envpnode(char *name, char *value, char *full)
{
	t_envplist	*new;

	new = malloc(sizeof(t_envplist));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->var_name = name;
	new->var_value = value;
	new->full = full;
	return (new);
}

void	destroy_envplist(void)
{
	t_envplist	*tmp;

	while (envplist()->next)
	{
		tmp = envplist()->next;
		envplist()->next = envplist()->next->next;
		if (tmp->var_name)
			free(tmp->var_name);
		if (tmp->var_value)
			free(tmp->var_value);
		free (tmp);
	}
}
