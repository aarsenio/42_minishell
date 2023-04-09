#include <minishell.h>

void	exec_pipe_before_output(void)
{
	printf("entrei pipe_before");
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		perror_exit("Error creating pipe");
	dup2(pipe_fd[0], STDIN_FILENO);
	write(pipe_fd[1], '\0', 0);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
}

void	exec_pipe(t_arglist *node)
{
	int		wait_status;
	int		pipe_fd[2];
	pid_t	pid;

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
		waitpid(0, &wait_status, 0);
	}
}
