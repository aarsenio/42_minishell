#include <minishell.h>

void	cmd_exit(void)
{
	destroy_arglist();
	destroy_envplist();
	if (data()->input)
		free(data()->input);
	exit(0);
}
