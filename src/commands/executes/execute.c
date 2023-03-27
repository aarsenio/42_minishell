#include <minishell.h>

void	exec_commands(t_arglist *node)
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

void	exec_executables(t_arglist *node)
{
	pid_t	pid;

	if (builtins(node->av))
		exit(0);
	pid = fork();
	if (pid == -1)
		free_perror_exit("Error forking in exe_executables");
	if (pid == 0)
		exec_commands(node);
	else
		wait(NULL);
}

void	execute(void)
{
	int			wait_status;
	t_arglist	*temp;
	pid_t		pid;
	int	i = 0;

	temp = arglist()->next;
	while (i++ < 3 && temp)
	{
		printf("%s\n", temp->av[0]);
		pid = fork();
		if (pid == -1)
			free_perror_exit("Error creating pipe");
		if (pid == 0)
		{
			if (temp->next_op == PIPE)
				exec_pipe(temp);
			else if (temp->next_op == NONE)
				exec_executables(temp);
			else
				exec_redirects(temp);
		}
		else
		{
			waitpid(-1, &wait_status, 0);
			temp = temp->next;
		}
	}
	return ;
}
