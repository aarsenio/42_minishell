#include <minishell.h>

/*prints error msg to std_err if absolute path is not acesseble*/
void	no_such_file_or_dir(char *path)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
}

/*prints error msg to std_err if command isn't found*/
void	cmd_not_found(char *cmd_name)
{
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
}

/*Initiate file descriptors to cleanlist()->fdin = -1 for
	each existing node of the cleanleast*/
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
