#include <minishell.h>

static void	exe_cmds_rdir(void)
{
	return ;
}

void	execute(void)
{
	if (builtins())
		return ;
	else
		exe_cmds_rdir();
}
