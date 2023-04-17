#include <minishell.h>

int	cmd_env(void)
{
	t_envplist	*x;

	x = envplist()->next;
	while (x)
	{
		if (x->var_value)
			printf("%s=%s\n", x->var_name, x->var_value);
		x = x->next;
	}
	return (0);
}
