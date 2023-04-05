#include <minishell.h>

void	cmd_env(void)
{
	t_envplist	*x;

	x = envplist()->next;
	g_exit_status = 0;
	while (x)
	{
		if (x->var_value)
			printf("%s=%s\n", x->var_name, x->var_value);
		x = x->next;
	}
}
