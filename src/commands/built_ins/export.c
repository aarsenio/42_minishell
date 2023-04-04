#include <minishell.h>

static int	is_valid(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	cmd_export(void)
{
	return(0);
}
