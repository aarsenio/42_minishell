#include <minishell.h>

void	token_expander(void)
{
	t_toklist	*t;
	t_envplist	*e;
	char		*var;
	int			i;
	int			j;

	t = toklist()->next;
	
	while (t)
	{
		i = 0;
		j = 0;
		if (t->token[i] == '$')
		{
			var = malloc(sizeof(char) * ft_strlen(t->token));
			while (t->token[++i])
				var[j++] = t->token[i];
			var[j] = '\0';
			e = envplist()->next;
			while (e)
			{
				if (!ft_strcmp(var, e->var_name))
				{
					free(t->token);
					t->token = ft_strcpy(e->var_value);
				}
				e = e->next;
			}
			free(var);
		}
		t = t->next;
	}
}