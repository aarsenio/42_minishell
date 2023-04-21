#include <minishell.h>

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	is_num_long_long(char *s)
{
	long long	n;
	int			sig;
	int			i;

	i = 0;
	if (ft_strcmp(s, "-9223372036854775809") <= 0 || \
	ft_strcmp(s, "9223372036854775808") <= 0)
		return (0);
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
	return (1);
}

int	cmd_exit(t_cleanlist *node)
{
	int	status;

	status = 0;
	if (node->ac > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (2);
	}
	if (node->av[1] && is_num_long_long(node->av[1]))
	{
		ft_putstr_fd("minishell: exit:", 2);
		ft_putstr_fd(node->av[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		status = 2;
	}
	else if (node->av[1])
		status = ft_atoll(node->av[1]);
	ft_putendl_fd("exit", STDOUT_FILENO);
	destroy_arglist();
	destroy_envplist();
	destroy_cleanlist();
	free(data()->envp);
	free(data()->input);
	rl_clear_history();
	exit(status);
}
