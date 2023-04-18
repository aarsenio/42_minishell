#include <minishell.h>

static void	change_path(void)
{
	char	*t;

	if (fetch_node("OLDPWD"))
	{
		free(fetch_node("OLDPWD")->full);
		free(fetch_node("OLDPWD")->var_value);
		fetch_node("OLDPWD")->var_value = malloc(1);
		fetch_node("OLDPWD")->var_value[0] = '\0';
		fetch_node("OLDPWD")->full = ft_strjoin(fetch_node("OLDPWD")->var_name, "=");
	}
	if (fetch_node("OLDPWD") && fetch_node("PWD"))
	{
		fetch_node("OLDPWD")->var_value = fetch_node("PWD")->var_value;
		free(fetch_node("OLDPWD")->full);
		t = ft_strjoin(fetch_node("OLDPWD")->var_name, "=");
		fetch_node("OLDPWD")->full = ft_strjoin(t, fetch_node("OLDPWD")->var_value);
		free(t);
	}
	if (fetch_node("PWD"))
	{
		fetch_node("PWD")->var_value = getcwd(NULL, 0);
		t = ft_strjoin(fetch_node("PWD")->var_name, "=");
		fetch_node("PWD")->full = ft_strjoin(t, fetch_node("PWD")->var_value);
		free(t);
	}
}

int	cmd_cd(t_cleanlist *node)
{
	char	*s;
	char	*err_msg;

	if (node->ac > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (2);
	}
	s = node->av[1];
	if (node->ac == 1 || !ft_strcmp(node->av[1], "-"))
	{
		if (!fetch_node("OLDPWD"))
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
			return (1);
		}
		s = fetch_node("OLDPWD")->var_value;
	}
	if (node->ac == 1 || !ft_strcmp(node->av[1], "~"))
		s = getenv("HOME");
	if (chdir(s) == -1)
	{
		err_msg = ft_strjoin("minishell: cd: ", node->av[1]);
		perror(err_msg);
		free(err_msg);
		return (2);
	}
	change_path();
	update_envp();
	return (0);
}
