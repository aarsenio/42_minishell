#include <minishell.h>

void	cmd_echo(void)
{
	int			i;
	t_arglist	*x;

	i = 1;
	x = arglist()->next;
	if (x->ac > 2 && !ft_strcmp(x->av[1], "-n"))
		i++;
	while (x->av[i])
	{
		printf("%s", x->av[i]);
		if (x->av[i + 1])
			printf(" ");
		i++;
	}
	if (x->ac >= 2 && ft_strcmp(x->av[1], "-n"))
		printf("\n");
	return ;
}
