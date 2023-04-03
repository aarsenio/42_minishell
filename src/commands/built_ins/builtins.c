#include <minishell.h>

int	builtins(t_arglist *node)
{
	if (!ft_strcmp(node->av[0], "echo"))
		exit_status = cmd_echo(node);
	else if (!ft_strcmp(node->av[0], "cd"))
		exit_status = cmd_cd();
	else if (!ft_strcmp(node->av[0], "pwd"))
		exit_status = cmd_pwd();
	else if (!ft_strcmp(node->av[0], "export"))
		exit_status = cmd_export();
	else if (!ft_strcmp(node->av[0], "unset"))
		exit_status = cmd_unset();
	else if (!ft_strcmp(node->av[0], "env"))
		exit_status = cmd_env();
	else if (!ft_strcmp(node->av[0], "exit"))
		cmd_exit();
	else
		return (0);
	return (exit_status);
}
