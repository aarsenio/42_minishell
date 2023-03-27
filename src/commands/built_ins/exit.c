#include <minishell.h>

void	cmd_exit(void)
{
	destroy_arglist();
	destroy_envplist();
	free(data()->input);
	data()->input = NULL;
	exit(0);
}
