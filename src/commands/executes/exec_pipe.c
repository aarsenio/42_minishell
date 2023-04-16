#include <minishell.h>

void	exec_pipe(t_cleanlist *node)
{
	int		pipe_fd[2];
	int		pid;

	if (pipe(pipe_fd) == -1)
		perror_exit("Error creating pipe");
	pid = fork();
	if (pid == -1)
		perror_exit("Error forking in exec_pipe");
	if (pid == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		exec_executables(node);
	}
	else
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
}

void	initiate_fd(void)
{
	t_cleanlist	*t;

	t = cleanlist()->next;
	while(t)
	{
		t->fdin = -1;
		t->fdout = -1;
		t = t->next;
	}
}
