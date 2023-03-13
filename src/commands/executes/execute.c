#include <minishell.h>

/*
static void	search_path_and_execute()
{
	return ;
}

static void	exe_cmds_rdir(void)
{
	if (arglist()->operator == PIPE)
		exec_pipe();
	else if (arglist()->operator == NONE)
		exec_executables();
	else
		exec_redirects();
}
*/

void	execute(void)
{
	if (builtins())
		return ;
	/*else if (ft_lstsize(arglist()->next) == 1)
	{
		if (fork() == 0)
			search_path_and_execute();
	}
	else if (fork() == 0)
		exe_cmds_rdir();*/
}
