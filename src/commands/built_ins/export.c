#include <minishell.h>

static int	is_valid(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

static int	is_value(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			return (1);
	return (0);
}

t_envplist	*fetch_node(char *str)
{
	t_envplist	*t;
	char		*name;

	t = envplist()->next;
	name = copy_name(str);
	while (t)
	{
		if (!ft_strcmp(name, t->var_name))
		{
			free(name);
			return (t);
		}
		t = t->next;
	}
	free(name);
	return (NULL);
}

void	cmd_export(t_arglist *node)
{
	int		i;
	char	*err_msg;
	char	*t;

	i = 0;
	g_exit_status = 0;
	while (node->av[++i])
	{
		if (!is_valid(node->av[i][0]))
		{
			g_exit_status = 2;
			t = ft_strjoin("minishell: export: `", node->av[i]);
			err_msg = ft_strjoin(t, "': not a valid identifier");
			free(t);
			ft_putendl_fd(err_msg, 2);
			free(err_msg);
		}
		else
		{
			if (is_value(node->av[i]))
			{
				if (fetch_node(node->av[i]))
				{
					free(fetch_node(node->av[i])->var_value);
					free(fetch_node(node->av[i])->full);
					fetch_node(node->av[i])->var_value = copy_value(node->av[i]);
					fetch_node(node->av[i])->full = ft_strcpy(node->av[i]);
				}
				else
					add_envpnode(new_envpnode(copy_name(node->av[i]), copy_value(node->av[i]), ft_strcpy(node->av[i])), envplist());
			}
			else
			{
				if (fetch_node(node->av[i]))
					return ;
				add_envpnode(new_envpnode(copy_name(node->av[i]), NULL, ft_strcpy(node->av[i])), envplist());
			}
		}
	}
	update_envp();
}
