#include <minishell.h>

/*
static void	search_path_and_execute()
{
	return ;
}

static void	exec_commands(t_arglist *node, char *input)
{
	paths = get_paths()
}
*/

static void	exec_executables(t_arglist *node)
{
	if (builtins(node->av))
		return ;
	/*exec_commands(node, input);*/
}

void	execute(void)
{
	int			wait_status;
	t_arglist	*temp;

	temp = arglist()->next;
	while (temp)
	{
		if (fork() == 0)
		{
			if (temp->operator == PIPE)
				exec_pipe(temp);				//Redirecciona output para
			else if (temp->operator == NONE)
				exec_executables(temp);	//Builtins e exec_path_commands
			else
				exec_redirects(temp);			//Redirecciona input ou output para o que corresponda
		}
		waitpid(-1, &wait_status, 0);
		if (!WIFEXITED(wait_status))
			cmd_exit();
		temp = temp->next;
	}
}
