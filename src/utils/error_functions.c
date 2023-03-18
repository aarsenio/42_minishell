#include <minishell.h>

void	cmd_not_found(char *cmd_name)
{
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
}

void	perror_exit(char *msg)
{
	perror(msg);
	exit(0);
}

void	exit_free_matrix(char **matrix, char *str)
{
	if (str)
		free(str);
	str = NULL;
	if (matrix)
		free_matrix(matrix);
	exit(0);
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
