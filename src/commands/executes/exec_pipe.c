#include <minishell.h>

void	exec_pipe(t_arglist *node)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		free_perror_exit("Error creating pipe");
	pid = fork();
	if (pid == -1)
		free_perror_exit("Error forking in exec_pipe");
	if (pid == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		if (builtins(node->av))
			return ;
		exec_commands(node);
	}
	else
	{
		data()->stin_fd = dup(STDIN_FILENO);
		//printf("STDNIN: %d\n",data()->stin_fd);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
}
