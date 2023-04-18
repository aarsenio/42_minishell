#include <minishell.h>

static int	counter(t_toklist *t)
{
	int	counter;

	counter = 0;
	while (t && t->operator != PIPE)
	{
		if (t && t->operator == NONE)
		{
			counter++;
			t = t->next;
		}
		else
			t = t->next->next;
	}
	return (counter);
}

void	create_cleanlist(void)
{
	t_toklist	*t;
	t_operator	rdr;
	char		**av;
	int			i[2];
	int			ac;

	t = toklist()->next;
	i[1] = 0;
	while (t)
	{
		rdr = NONE;
		av = malloc(sizeof(char *) * (counter(t) + 1));
		if (!av)
			return ;
		ac = 0;
		i[0] = 0;
		while (t && t->operator != PIPE)
		{
			if (t && t->operator == NONE)
			{
				av[i[0]++] = ft_strcpy(t->token);
				ac++;
				t = t->next;
			}
			else
			{
				rdr = t->operator;
				t = t->next->next;
			}
		}
		av[i[0]] = NULL;
		add_cleannode(new_cleannode(ac, av, i[1], rdr), cleanlist());
		i[1]++;
		if (t && t->operator == PIPE)
			t = t->next;
	}
	destroy_toklist();
}
