#include <minishell.h>

static void	exec_commands(t_arglist *node)
{
	char	*bin_path;
	char	**splitted_paths;

	splitted_paths = get_paths(envplist()->next);
	bin_path = find_working_path(node->av[0], splitted_paths);
	if (!bin_path)
	{
		cmd_not_found(node->av[0]);
		exit_free_matrix(splitted_paths, bin_path);
	}
	if (execve(bin_path, node->av, data()->argv) == -1)
		exit_free_matrix(splitted_paths, bin_path);
}

static void	exec_executables(t_arglist *node)
{
	pid_t	pid;

	if (builtins(node->av))
		return ;
	pid = fork();
	if (pid == -1)
		perror("Error forking");
	if (pid == 0)
		exec_commands(node);
}

void	execute(void)
{
	int			wait_status;
	t_arglist	*temp;

	temp = arglist()->next;
	while (temp)
	{
		if (temp->operator == PIPE)
			exec_pipe(temp);			//Redirecciona output para
		else if (temp->operator == NONE)
			exec_executables(temp);	//Builtins e exec_path_commands
		else
			exec_redirects(temp);		//Redirecciona input ou output
		waitpid(-1, &wait_status, 0);	//para o que corresponda
		if (!WIFEXITED(wait_status))
			cmd_exit();
		temp = temp->next;
	}
}
