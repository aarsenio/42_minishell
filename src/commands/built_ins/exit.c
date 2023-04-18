#include <minishell.h>

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}
// TODO: Arranjar exit 
static int	is_num_long_long(char *s)
{
	long long	n;
	int			sig;
	int			i;

	i = 0;
	while ((s[i] && s[i] == ' ') || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		sig = (s[i] != '-') - (s[i] == '-');
		i++;
	}
	while (s[i] && ft_isdigit(s[i]))
		n = n * 10 + sig * (s[i++] - '0');
	if (s[i] && !ft_isdigit(s[i]))
		return (0);
	if (n >= -9223372036854775807 || n <= 9223372036854775806)
		return (1);
	else
		return (0);
}

int	cmd_exit(t_cleanlist *node)
{
	int	status;

	if (node->av[1] && is_num_long_long(node->av[1]))
	{
		ft_putendl_fd("minishell: exit:", 1);
		ft_putendl_fd(node->av[1], 1);
		ft_putendl_fd(": numeric argument required", 1);
		status = 2;
	}
	ft_putendl_fd("exit", STDOUT_FILENO);
	destroy_arglist();
	destroy_envplist();
	free(data()->envp);
	free(data()->input);
	data()->input = NULL;
	clear_history();
	exit(status);
}
