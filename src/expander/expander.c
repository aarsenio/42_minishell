#include <minishell.h>

char	*replace_search(char *str)
{
	t_envplist	*tmp;

	tmp = envplist()->next;
	while (tmp)
	{
		if (!ft_strcmp(str, tmp->var_name))
			return (tmp->var_value);
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
	int		i;
	int		j;
	int		k;
	
	result = malloc(sizeof(char) * (ft_strlen(t) - ft_strlen(var) + ft_strlen(replace) + 2));
	i = -1;
	j = 0;
	while (t[++i])
	{
		if (t[i] == '$' && t[i + 1] && is_varname(t, var, i + 1))
			break ;
		result[j++] = t[i];
	}
	i += ft_strlen(var);
	k = -1;
	while (replace && replace[++k])
		result[j++] = replace[k];
	while (t[++i])
		result[j++] = t[i];
	result[j] = '\0';
	return (result);
}

char	*expander(char *token)
{
	int		i;
	int		j;
	int		k;
	char	*ex_tmp;
	char	*t;

	i = 0;
	while (token[i])
	{
		if (token[i + 1] && token[i] == '$' && !is_space(token[i + 1]))
		{
			t = token;
			ex_tmp = malloc(sizeof(char) * (expendable_len(t, i) + 1));
			if (!ex_tmp)
				return (NULL);
			j = 0;
			k = i + 1;
			while (token[k] && !is_space(token[k]) && token[k] != '$')
				ex_tmp[j++] = token[k++];
			ex_tmp[j] = '\0';
			i += ft_strlen(replace_search(ex_tmp));
			token = replace(t, ex_tmp, replace_search(ex_tmp));
			free(ex_tmp);
			free(t);
		}
		else
			i++;
	}
	return (token);
}
