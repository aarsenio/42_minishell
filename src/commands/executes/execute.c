#include <minishell.h>

void	exec_commands(t_arglist *node)
{
	char	*bin_path;
	char	**splitted_paths;

	if (strchr(node->av[0], '/'))
	{
		if (execve(node->av[0], node->av, data()->envp) == -1)
		exit(0);
	}
	splitted_paths = get_paths(envplist()->next);
	bin_path = find_working_path(node->av[0], splitted_paths);
	if (!bin_path)
	{
		g_exit_status = 127;
		//printf("g_exit_status: %d\n", g_exit_status);
		cmd_not_found(node->av[0]);
		exit_free_matrix(splitted_paths, bin_path);
	}
	if (execve(bin_path, node->av, data()->envp) == -1)
		exit_free_matrix(splitted_paths, bin_path);
}

void	exec_executables(t_arglist *node)
{
	if (builtins(node))
		exit(0);
	exec_commands(node);
}

void	execute(void)
{
	int			wait_status;
	t_arglist	*temp;
	pid_t		pid;

	if (ft_lstsize(arglist()) == 1 && builtins(arglist()->next))
		return ;
	pid = fork();
	if (pid == -1)
		free_perror_exit("Error creating pipe");
	if (pid == 0)
	{
		temp = arglist()->next;
		while (temp)
		{
			if (temp->next_op == PIPE)
				exec_pipe(temp);
			else if (temp->next_op == NONE)
				exec_executables(temp);
			else
				exec_redirects(temp);
			temp = temp->next;
		}
	}
	else
	{
		waitpid(-1, &wait_status, 0);
		if (!WTERMSIG(wait_status))
			g_exit_status = wait_status;
	}
	return ;
}
