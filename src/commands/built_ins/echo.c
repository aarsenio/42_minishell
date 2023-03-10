#include <minishell.h>

void	cmd_echo(void)
{
	int	i;

	i = 1;
	if (arglist()->ac > 2 && ft_strcmp(arglist()->av[1], "-n"))
		i++;
	while (arglist()->av[i])
	{
		printf("%s", arglist()->av[i]);
		if (arglist()->av[i + 1])
			printf(" ");
		i++;
	}
	if (arglist()->ac > 2 && !ft_strcmp(arglist()->av[1], "-n"))
		printf("\n");
	return ;
}
