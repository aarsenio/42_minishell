#include <minishell.h>

t_envplist	*envplist(void)
{
	static t_envplist	envplist;

	return (&envplist);
}

t_arglist	*arglist(void)
{
	static t_arglist	arglist;

	return (&arglist);
}

t_toklist	*toklist(void)
{
	static t_toklist	toklist;

	return (&toklist);
}

t_data		*data(void)
{
	static t_data		data;

	return (&data);
}
