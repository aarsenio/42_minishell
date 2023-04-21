#include <minishell.h>

static void	exec_commands(t_cleanlist *node)
{
	char	*bin_path;
	char	**splitted_paths;

	if (!*node->av)
		exit(1);
	splitted_paths = get_paths(envplist()->next);
	bin_path = find_working_path(node->av[0], splitted_paths);
	if (ft_strchr(node->av[0], '/'))
	{
		if (access(node->av[0], F_OK) != 0)
			no_such_file_or_dir(node->av[0]);
		if (execve(node->av[0], node->av, data()->envp) == -1)
			exit_free_matrix(node, splitted_paths, bin_path);
	}
	if (!bin_path)
	{
		g_exit_status = 127;
		cmd_not_found(node->av[0]);
		exit_free_matrix(node, splitted_paths, bin_path);
	}
	if (execve(bin_path, node->av, data()->envp) == -1)
		exit_free_matrix(node, splitted_paths, bin_path);
}

void	exec_executables(t_cleanlist *node)
{
	if (node->fdin != -1)
	{
		dup2(node->fdin, STDIN_FILENO);
		close(node->fdin);
	}
	if (node->fdout != -1)
	{
		dup2(node->fdout, STDOUT_FILENO);
		close(node->fdout);
	}
	if (builtins(node))
		exit(g_exit_status);
	exec_commands(node);
}

static void	loop_cleanlist_execute(void)
{
	t_cleanlist	*t;
	int			wait_status;

	t = cleanlist()->next;
	while (t && t->next)
	{
		exec_pipe(t);
		t = t->next;
	}
	if (t && !t->next)
		exec_executables(t);
	while (t && t->index-- > -1)
		wait(&wait_status);
}
/*Loops first all arglist nodes and where there is a heredoc it executes
 it (pipe, execute and store fd in writting and of pipe and reading end is
 stored in ->fdin of each node). Than second loop where there is exec_input
 or output, opens files and stores file discriptor in ->fdou of each node*/
static void	loop_arglist_redirects(void)
{
	t_arglist	*t;
	/*
	t = arglist()->next;
	while (t)
	{
		if (t->rdr == R_IN_UNT)
			heredoc(t);
		t = t->next;
	}
	*/
	t = arglist()->next;
	while (t)
	{
		if (t->rdr == R_IN_UNT)
			heredoc(t);
		else if (t->rdr == R_IN)
			exec_input(t);
		else if (t->rdr == R_OUT_REP || t->rdr == R_OUT_APP)
			exec_outputs(t);
		t = t->next;
	}
}
/*Starts executing process, initiate fds, forks, the child starts the
 redirections and executions functions, the parets keeps the original
 stdin and out for when when minisheel starts again in a new prompt,
 and waits for the child, gets the wait status and passes it to
 g_exit_status*/
void	execute(void)
{
	int		wait_status;
	int		pid;

	if (ft_lstsize(arglist()) == 1 && builtins(cleanlist()->next))
		return ;
	initiate_fd();
	pid = fork();
	if (pid == -1)
		perror_exit("Error creating pipe");
	if (pid == 0)
	{
		loop_arglist_redirects();
		loop_cleanlist_execute();
	}
	else
	{
		waitpid(-1, &wait_status, 0);
		if (WIFEXITED(wait_status))
			g_exit_status = wait_status >> 8;
	}
	return ;
}
