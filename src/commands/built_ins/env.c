#include <minishell.h>

void	cmd_env()
{
	t_envplist	*temp;

	temp = envplist();
	while (temp != NULL)
	{
		printf("%s=%s\n", temp->var_name, temp->var_value);
		temp = temp->next;
	}
	return ;
}
