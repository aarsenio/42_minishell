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
		if (node->fdout == -1)
			dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		exec_executables(node);
	}
	else
	{
		if (node->fdin == -1)
			dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
}
