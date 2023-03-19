#include <minishell.h>

void	exec_pipe(t_arglist *temp)
{
	int	pipe_fd[2];
	(void)temp;

	if (pipe(pipe_fd) == -1)
		{
			perror_exit("Error creating pipe");
		}
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
}
