#include <minishell.h>

static int		is_n_flag(char *str)
{
	if (*str == '-')
		str++;
	else
		return (0);
	while (*str == 'n')
		str++;
	if (!*str)
		return (1);
	else
		return (0);
}

int	cmd_echo(t_arglist *node)
{
	int			i;

	i = 1;
	if (node->ac > 2 && is_n_flag(node->av[1]))
		i++;
	while (node->av[i])
	{
		printf("%s", node->av[i]);
		if (node->av[i + 1])
			printf(" ");
		i++;
	}
	if (node->ac >= 2 && !is_n_flag(node->av[1]))
		printf("\n");
	return(0);
}
