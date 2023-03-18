#include <minishell.h>

char	**get_paths(t_envplist *head)
{
	t_envplist	*temp;

	temp = head;
	while (temp)
	{
		if (!ft_strcmp("PATH", temp->var_name))
			return (ft_split(temp->var_value, ':'));
		temp = temp->next;
	}
	return (NULL);
}

char	*find_working_path(char *cmd, char **paths)
{
	size_t	i;
	char	*temp;
	char	*bin_path;

	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		bin_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(bin_path, F_OK) == 0)
			return (bin_path);
		free(bin_path);
		bin_path = NULL;
		i++;
	}
	return (NULL);
}
