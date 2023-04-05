#include <minishell.h>

static void	change_path()
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

void	cmd_cd(t_arglist *node)
{
	char	*s;
	char	*err_msg;

	g_exit_status = 0;
	if (node->ac > 2)
	{
		g_exit_status = 2;
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return ;
	}
	s = node->av[1];
	if (node->ac == 1 || !ft_strcmp(node->av[1], "~"))
		s = fetch_node("HOME")->var_value;
	if (chdir(s) == -1)
	{
		g_exit_status = 2;
		err_msg = ft_strjoin("minishell: cd: ", node->av[1]);
		perror(err_msg);
		free(err_msg);
		return ;
	}
	change_path();
	update_envp();
}
