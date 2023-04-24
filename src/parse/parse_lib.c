/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:00:54 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/04/24 20:00:55 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_quote(char x)
{
	if (x == '"' || x == '\'')
		return (1);
	return (0);
}

int	is_operator(char x)
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
	x->token = NULL;
	return (newstr);
}

t_operator	get_operator(char *op)
{
	if (ft_strcmp(op, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(op, "<") == 0)
		return (R_IN);
	else if (ft_strcmp(op, "<<") == 0)
		return (R_IN_UNT);
	else if (ft_strcmp(op, ">") == 0)
		return (R_OUT_REP);
	else if (ft_strcmp(op, ">>") == 0)
		return (R_OUT_APP);
	return (NONE);
}
