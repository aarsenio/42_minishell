#include <minishell.h>

static void	exec_commands(t_arglist *node)
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

static void loop_execute_nodes(void)
{
	t_arglist	*t;
	size_t		i;

	t = arglist()->next;
	i = -1;
	while (t)
	{
		if (++i < ft_lstsize(t) && (t->next->rdr \
			== R_OUT_REP || t->next->rdr == R_OUT_APP))
			exec_outputs(t->next);
		if (++i < ft_lstsize(t) && t->pipe == PIPE \
			&& (t->next->rdr == R_OUT_REP \
			|| t->next->rdr == R_OUT_APP))
			exec_pipe_before_output();
		if (t->rdr == R_IN)
			exec_inputs(t);
		else if (t->rdr == R_IN_UNT)
			exec_inputs_until(t);
		else if (t->pipe == PIPE && t->next->rdr == NONE)
			exec_pipe(t);
		else if (t->pipe == NONE && t->rdr == NONE)
			exec_executables(t);
		t = t->next;
	}
}

void	execute(void)
{
	int			wait_status;
	pid_t		pid;

	if (ft_lstsize(arglist()) == 1 && builtins(arglist()->next))
		return ;
	pid = fork();
	if (pid == -1)
		perror_exit("Error creating pipe");
	if (pid == 0)
	{
		loop_execute_nodes();
		exit(0);
	}
	else
	{
		waitpid(-1, &wait_status, 0);
		if (!WTERMSIG(wait_status))
			g_exit_status = wait_status;
	}
	return ;
}
