#include <minishell.h>

void	destroy_node(char *var)
{
	t_envplist	*t;
	t_envplist	*f;

	t = envplist();
	while (t)
	{
		if (t->next && !ft_strcmp(t->next->var_name, var))
		{
			f = t->next;
			free(t->next->full);
			free(t->next->var_name);
			free(t->next->var_value);
			if (t->next->next)
				t->next = t->next->next;
			else
				t->next = NULL;
			free(f);
		}
		t = t->next;
	}
}

int	cmd_unset(t_cleanlist *node)
{
	int			i;

	i = 0;
	while (node->av[++i])
		destroy_node(node->av[i]);
	update_envp();
	return (0);
}
