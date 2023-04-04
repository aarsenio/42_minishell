#include <minishell.h>

int	builtins(t_arglist *node)
{
	if (!ft_strcmp(node->av[0], "echo"))
		cmd_echo(node);
	else if (!ft_strcmp(node->av[0], "cd"))
		cmd_cd();
	else if (!ft_strcmp(node->av[0], "pwd"))
		cmd_pwd();
	else if (!ft_strcmp(node->av[0], "export"))
		cmd_export();
	else if (!ft_strcmp(node->av[0], "unset"))
		cmd_unset();
	else if (!ft_strcmp(node->av[0], "env"))
		cmd_env();
	else if (!ft_strcmp(node->av[0], "exit"))
		cmd_exit();
	else
		return (0);
	return (1);
}
