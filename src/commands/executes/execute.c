#include <minishell.h>
/*
static void	search_path_and_execute()
{
	return ;
}
*/
void	exec_executables(t_arglist *node)
{
	if(builtins(node->av))
		return ;

}

void	execute(void)
{
	t_arglist	*temp;

	temp = arglist()->next;
	while (temp)
	{
		if (temp->operator == PIPE)
			exec_pipe(temp);
		else if (temp->operator > 0 && temp->operator < 5)
			exec_redirects(temp);
		else if (temp->operator == NONE && fork() == 0)
		{
			if (!builtins(temp->av))
				exec_executables(temp);
		}
		waitpid(-1, 0, 0);
		temp = temp->next;
	}
}
