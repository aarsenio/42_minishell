#include <minishell.h>

void	cmd_not_found(char *cmd_name)
{
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
}

void	free_perror_exit(char *msg)
{
	perror(msg);
	cmd_exit();
}

void	exit_free_matrix(char **matrix, char *str)
{
	free(str);
	str = NULL;
	free_matrix(matrix);
	cmd_exit();
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
}
