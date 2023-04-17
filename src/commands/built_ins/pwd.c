#include <minishell.h>

int	cmd_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("pwd");
		return (2);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
