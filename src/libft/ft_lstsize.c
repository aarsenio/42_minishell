#include <minishell.h>

size_t	ft_lstsize(t_arglist *lst)
{
	t_arglist	*temp;
	size_t		size;

	temp = lst;
	size = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		size++;
	}
	return (size);
}
