#include <minishell.h>

void	exit_destroy_free(void)
{
	destroy_arglist();
	destroy_envplist();
	destroy_cleanlist();
	free(data()->input);
	data()->input = NULL;
	rl_clear_history();
	exit(g_exit_status);
}

void	perror_exit(char *msg)
{
	perror(msg);
	exit_destroy_free();
}

void	exit_free_matrix(t_cleanlist *node, char **matrix, char *str)
{
	free(str);
	free_matrix(matrix);
	exit_destroy_free();
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
