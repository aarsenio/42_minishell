#include <minishell.h>

int	builtins(t_cleanlist *node)
{
	if (!node->av[0])
		return (0);
	if (!ft_strcmp(node->av[0], "echo"))
		g_exit_status = cmd_echo(node);
	else if (!ft_strcmp(node->av[0], "cd"))
		g_exit_status = cmd_cd(node);
	else if (!ft_strcmp(node->av[0], "pwd"))
		g_exit_status = cmd_pwd();
	else if (!ft_strcmp(node->av[0], "export"))
		g_exit_status = cmd_export(node);
	else if (!ft_strcmp(node->av[0], "unset"))
		g_exit_status = cmd_unset(node);
	else if (!ft_strcmp(node->av[0], "env"))
		g_exit_status = cmd_env();
	else if (!ft_strcmp(node->av[0], "exit"))
		g_exit_status = cmd_exit(node);
	else
		return (0);
	return (1);
}
