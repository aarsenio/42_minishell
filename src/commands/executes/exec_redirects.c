#include <minishell.h>

static void redirect_input_until(t_arglist *node)
{
	(void)node;

	return ;
}

static void redirect_input(t_arglist *node)
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

static void redirect_output(t_arglist *node)
{

	if (node->rdr == RDR_OUT_REPLACE)
		open(node->av[0], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (node->rdr == RDR_OUT_APPEND)
		open(node->av[0], O_WRONLY | O_CREAT | O_APPEND, 0666);
}

void	exec_redirects(t_arglist *node)
{
	if (node->rdr == RDR_INPUT)
		redirect_input(node);
	else if (node->rdr == RDR_INPUT_UNTIL)
		redirect_input_until(node);
	else
		redirect_output(node);
	//exit(0);
}
