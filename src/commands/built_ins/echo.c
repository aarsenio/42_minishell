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

void	cmd_echo(void)
{
	int			i;
	t_arglist	*x;

	i = 1;
	x = arglist()->next;
	if (x->ac > 2 && is_n_flag(x->av[1]))
		i++;
	while (x->av[i])
	{
		printf("%s", x->av[i]);
		if (x->av[i + 1])
			printf(" ");
		i++;
	}
	if (x->ac >= 2 && !is_n_flag(x->av[1]))
		printf("\n");
}
