/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarsenio <aarsenio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:48:31 by aarsenio          #+#    #+#             */
/*   Updated: 2023/03/07 14:58:46 by aarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_quote(char x)
{
	if (x == '"' || x == '\'')
		return (1);
	return (0);
}

int	is_pipe_redirect(char x)
{
	if (x == '|' || x == '>' || x == '<')
		return (1);
	return (0);
}

int	is_space(char x)
{
	if (x == ' ' || x == '\n' || x == '\t')
		return (1);
	return (0);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*parse_strjoin(char const *s1, char const *s2)
{
	char		*newstr;
	int			i;
	int			j;
	t_toklist	*x;

	j = -1;
	i = -1;
	if (!s1 || !s2)
		return (NULL);
	newstr = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	while (s1[++i])
		newstr[i] = s1[i];
	while (s2[++j])
		newstr[i++] = s2[j];
	newstr[i] = '\0';
	x = toklist()->next;
	while (x->next)
		x = x->next;
	free(x->token);
	return (newstr);
}
