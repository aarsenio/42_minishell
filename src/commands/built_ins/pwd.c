#include <minishell.h>

void	cmd_pwd(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	g_exit_status = 0;
	if (!pwd)
	{
		g_exit_status = 2;
		perror("pwd");
		return ;
	}
	printf("%s\n", pwd);
	free(pwd);
}
