#include <minishell.h>

void	cmd_exit(void)
{
	free(data()->envp);
	destroy_arglist();
	destroy_envplist();
	free(data()->input);
	data()->input = NULL;
	clear_history();
	exit(0);
}
