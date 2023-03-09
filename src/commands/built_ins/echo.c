#include <minishell.h>

void	cmd_echo(t_arglist	*arg)
{
	int i;

	i = 1;
	if (arg->ac >= 2 && ft_strcmp(arg->av[1], "-n"))
		i++;
	while (arg->av[i])
	{
		printf("%s", arg->av[i]);
			if (arg->av[i + 1])
				printf(" ");
		i++;
	}
	if (arg->ac >= 2 && !ft_strcmp(arg->av[1], "-n"))
		printf("\n");
	return ;
}
