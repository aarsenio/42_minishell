/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarsenio <aarsenio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:00:14 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/04/27 17:33:43 by aarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*replace_search(char *str)
{
	t_envplist	*tmp;

	tmp = envplist()->next;
	if (!ft_strcmp(str, "?"))
		return (ft_itoa(g_exit_status));
	while (tmp)
	{
		if (!ft_strcmp(str, tmp->var_name))
			return (ft_strcpy(tmp->var_value));
		tmp = tmp->next;
	}
	return (NULL);
}

int	is_varname(char *str, char *var, int i)
{
	int	j;

	j = 0;
	while (var[j] && str[i] && str[i++] == var[j++])
		;
	if (!var[j])
		return (1);
	return (0);
}

char	*replace(char *t, char *var, char *replace)
{
	char	*result;
	int		i[3];

	result = malloc(sizeof(char) * (ft_strlen(t) \
		- ft_strlen(var) + ft_strlen(replace) + 2));
	i[0] = -1;
	i[1] = 0;
	while (t[++i[0]])
	{
		if (t[i[0]] == '$' && t[i[0] + 1] && is_varname(t, var, i[0] + 1))
			break ;
		result[i[1]++] = t[i[0]];
	}
	i[0] += ft_strlen(var);
	i[2] = -1;
	while (replace && replace[++i[2]])
		result[i[1]++] = replace[i[2]];
	while (t[++i[0]])
		result[i[1]++] = t[i[0]];
	result[i[1]] = '\0';
	free(replace);
	free(t);
	return (result);
}

static int	validate(char *token, int i)
{
	if (!is_space(token[i + 1]) && !is_quote(token[i + 1]))
		return (1);
	return (0);
}

char	*expander(char *token, char *ex_tmp, int i[3], char *tmp)
{
	i[0] = 0;
	while (token[i[0]])
	{
		if (token[i[0] + 1] && token[i[0]] == '$' && validate(token, i[0]))
		{
			ex_tmp = malloc(sizeof(char) * (expendable_len(token, i[0]) + 1));
			if (!ex_tmp)
				return (NULL);
			i[1] = 0;
			i[2] = i[0] + 1;
			while (token[i[2]] && !is_space(token[i[2]]) && \
			!is_quote(token[i[2]]) && token[i[2]] != '$')
				ex_tmp[i[1]++] = token[i[2]++];
			ex_tmp[i[1]] = '\0';
			tmp = replace_search(ex_tmp);
			i[0] += ft_strlen(tmp);
			free(tmp);
			token = replace(token, ex_tmp, replace_search(ex_tmp));
			free(ex_tmp);
		}
		else
			i[0]++;
	}
	return (token);
}
