#include <minishell.h>

void	cmd_pwd(void)
{
	char *pwd;
	
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("pwd");
		return ;
	}
	printf("%s\n", pwd);
	free(pwd);
}
