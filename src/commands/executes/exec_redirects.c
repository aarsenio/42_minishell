#include <minishell.h>

void exec_inputs_until(t_arglist *node)
{
	pid_t	fd[2];
	char	*buff;

	pipe(fd);
	while (1)
	{
		buff = readline("> ");
		if(!ft_strcmp(buff, node->av[0]))
			break ;
		ft_putendl_fd(buff, fd[1]);
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	free(buff);
	buff = NULL;
}

void exec_inputs(t_arglist *node)
{
	int infile;
	char *error_msg;

	if(access(node->av[0], F_OK) == 0)
	{
		infile = open(node->av[0], O_RDONLY, 0666);
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	else
	{
		g_exit_status = 1;
		error_msg = ft_strjoin("minishell: ", node->av[0]);
		perror(error_msg);
		free(error_msg);
		exit(1);
	}
}

void exec_outputs(t_arglist *node)
{
	int fd;
	if (node->rdr == R_OUT_REP)
		fd = open(node->av[0], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (node->rdr == R_OUT_APP)
		fd = open(node->av[0], O_WRONLY | O_CREAT | O_APPEND, 0666);
	dup2(fd, STDOUT_FILENO);
	close (fd);
}
