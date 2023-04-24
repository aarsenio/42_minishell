/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:59:52 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/04/24 19:59:53 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
