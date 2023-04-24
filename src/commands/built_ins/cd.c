/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:59:37 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/04/24 19:59:38 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	change_old(void)
{
	free(fetch_node("OLDPWD")->full);
	free(fetch_node("OLDPWD")->var_value);
	fetch_node("OLDPWD")->var_value = malloc(1);
	fetch_node("OLDPWD")->var_value[0] = '\0';
	(fetch_node)("OLDPWD")->full = \
	ft_strjoin(fetch_node("OLDPWD")->var_name, "=");
}

static void	change_old_pwd(void)
{
	char	*t;
	char	*t2;

	free(fetch_node("OLDPWD")->var_value);
	free(fetch_node("OLDPWD")->full);
	fetch_node("OLDPWD")->var_value = fetch_node("PWD")->var_value;
	t = ft_strjoin(fetch_node("OLDPWD")->var_name, "=");
	t2 = ft_strjoin(t, fetch_node("OLDPWD")->var_value);
	fetch_node("OLDPWD")->full = t2;
	free(t);
}

static void	change_pwd(void)
{
	char	*t;
	char	*t2;

	free(fetch_node("PWD")->full);
	(fetch_node)("PWD")->var_value = getcwd(NULL, 0);
	t = ft_strjoin(fetch_node("PWD")->var_name, "=");
	t2 = ft_strjoin(t, fetch_node("PWD")->var_value);
	fetch_node("PWD")->full = t2;
	free(t);
}

static void	change_path(void)
{
	if (fetch_node("OLDPWD"))
		change_old();
	if (fetch_node("OLDPWD") && fetch_node("PWD"))
		change_old_pwd();
	if (fetch_node("PWD"))
		change_pwd();
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
	if (node->ac == 1)
		s = getenv("HOME");
	if (chdir(s) == -1)
	{
		err_msg = ft_strjoin("minishell: cd: ", s);
		perror(err_msg);
		free(err_msg);
		return (2);
	}
	change_path();
	update_envp();
	return (0);
}
