#include <minishell.h>

void	no_such_file_or_dir(char *path)
{
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(":no_such_file_or_dir", STDERR_FILENO);
}

void	cmd_not_found(char *cmd_name)
{
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
}

void	initiate_fd(void)
{
	t_cleanlist	*t;

	t = cleanlist()->next;
	while (t)
	{
		t->fdin = -1;
		t->fdout = -1;
		t = t->next;
	}
}
