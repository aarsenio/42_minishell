#include <minishell.h>

static int	ft_envplstsize(t_envplist *lst)
{
	t_envplist	*temp;
	int			size;

	temp = lst->next;
	size = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		size++;
	}
	return (size);
}

void	update_envp(void)
{
	int			i;
	t_envplist	*t;

	i = 0;
	t = envplist()->next;
	if (data()->envp)
		free(data()->envp);
	data()->envp = malloc(sizeof(char*) * (ft_envplstsize(envplist()) + 1));
	while (t)
	{
		data()->envp[i++] = t->full;
		t = t->next;
	}
	data()->envp[i] = NULL;
}

void	init_shell(char **envp)
{
	(void)envp;

	init_envplist(envp);
	update_envp();
}
