#include <minishell.h>

void	cmd_not_found(char *cmd_name)
{
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
}

void	perror_exit(char *msg)
{
	perror(msg);
	cmd_exit();
}

void	exit_free_matrix(t_cleanlist *node, char **matrix, char *str)
{
	free(str);
	free_matrix(matrix);
	cmd_exit();
	if (node->fdin != -1)
		close(node->fdin);
	if (node->fdout != -1)
		close(node->fdout);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}
