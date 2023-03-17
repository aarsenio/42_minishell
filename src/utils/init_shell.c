#include <minishell.h>

void	init_shell(char **envp)
{
	(void)envp;

	init_envplist(envp);
	data()->argv = envp;
}
