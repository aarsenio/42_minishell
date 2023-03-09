#include <minishell.h>

t_envplist	*envplist(void)
{
	static t_envplist envplist;

	return (&envplist);
}
