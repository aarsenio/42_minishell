#include <minishell.h>

int	varname_length(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i + 1);
}

int	varvalue_length(char *str)
{
	int	i;
	int	result;

	i = varname_length(str);
	result = 0;
	while (str[i++])
		result++;
	return (result + 1);
}

char	*copy_name(char *str)
{
	char	*name;
	int		i;

	name = malloc(sizeof(char) * varname_length(str));
	if (!name)
		return (NULL);
	i = -1;
	while (str[++i] != '=')
		name[i] = str[i];
	name[i] = '\0';
	return (name);
}

char	*copy_value(char *str)
{
	char	*value;
	int		i;
	int		j;

	j = 0;
	i = varname_length(str);
	value = malloc(sizeof(char) * varvalue_length(str));
	if (!value)
		return (NULL);
	while (str[i])
		value[j++] = str[i++];
	value[j] = '\0';
	return (value);
}

void	init_envplist(char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
		add_envpnode(new_envpnode(copy_name \
		(envp[i]), copy_value(envp[i])), envplist());
}
