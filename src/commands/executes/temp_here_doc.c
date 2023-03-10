/*#include <minishell.h>

static void	child_here_doc(int *pipe_fd, char *limiter)
{
	char	*line;

	line = NULL;
	close(pipe_fd[0]);
	while (ft_strncmp(limiter, line, ft_strlen(limiter)))
	{
		if (line)
			free(line);
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);		//verificar como fazer
		write(pipe_fd[1], line, ft_strlen(line));
	}
	free(line);
	close(pipe_fd[1]);
	exit(EXIT_SUCCESS);
}

void	here_doc(int argc, char *limiter)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (argc < 6)
		end_and_error_message("With here_doc minimum number of arguments is 6");
	if (pipe (pipe_fd) == -1)
		end_and_error_message("error creating pipe for here_doc");
	pid = fork();
	if (pid < 0)
		end_and_error_message("error forking for here_doc");
	if (pid == 0)
		child_here_doc(pipe_fd, limiter);
	else
	{
		close (pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close (pipe_fd[0]);
		waitpid(pid, NULL, 0);
	}
}
*/
