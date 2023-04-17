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
	int			index;
	int			i;
	int			ac;

	t = toklist()->next;
	index = 0;
	while (t)
	{
		rdr = NONE;
		av = malloc(sizeof(char *) * (counter(t) + 1));
		if (!av)
			return ;
		ac = 0;
		i = 0;
		while (t && t->operator != PIPE)
		{
			if (t && t->operator == NONE)
			{
				av[i++] = ft_strcpy(t->token);
				ac++;
				t = t->next;
			}
			else
			{
				rdr = t->operator;
				t = t->next->next;
			}
		}
		av[i] = NULL;
		add_cleannode(new_cleannode(ac, av, index, rdr), cleanlist());
		index++;
		if (t && t->operator == PIPE)
			t = t->next;
	}
	destroy_toklist();
}
