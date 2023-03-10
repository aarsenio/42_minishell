#include <minishell.h>

int	builtins(void)
{
	t_arglist	*x;

	x = arglist()->next;
	if (ft_strcmp(x->av[0], "echo"))
		cmd_echo();
	else if (ft_strcmp(x->av[0], "cd"))
		cmd_cd();
	else if (ft_strcmp(x->av[0], "pwd"))
		cmd_pwd();
	else if (ft_strcmp(x->av[0], "export"))
		cmd_export();
	else if (ft_strcmp(x->av[0], "unset"))
		cmd_unset();
	else if (ft_strcmp(x->av[0], "env"))
		cmd_env();
	else if (ft_strcmp(x->av[0], "exit"))
		cmd_exit();
	else
		return (0);
	return (1);
}
