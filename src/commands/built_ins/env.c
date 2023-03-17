#include <minishell.h>

void	cmd_env(void)
{
	t_envplist	*x;

	x = envplist()->next;
	while (x)
	{
		printf("%s=%s\n", x->var_name, x->var_value);
		x = x->next;
	}
	return ;
}
