#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

typedef enum e_operator
{
	NONE,
	RDR_OUT_REPLACE,
	RDR_OUT_APPEND,
	RDR_INPUT,
	RDR_INPUT_UNTIL,
	PIPE,
}t_operator;

typedef struct s_toklist
{
	t_operator			operator;
	char				*token;
	struct s_toklist	*next;
}t_toklist;

typedef struct s_arglist
{
	int					ac;
	char				**av;
	t_operator			operator;
	struct s_arglist	*next;
}t_arglist;

// parse
t_toklist	*toklist(void);
t_toklist	*new_toknode(char *token, t_operator operator);
void		add_toknode(t_toklist *new, t_toklist *x);
void		destroy_toklist(void);
void		tokenizer(char *input);
void		print_toklist(void);
t_arglist 	*arglist(void);
void		add_argnode(t_arglist *new, t_arglist *x);
t_arglist	*new_argnode(int ac, char **av, t_operator operator);

//lib
int			ft_strlen(const char *s);
char		*parse_strjoin(char const *s1, char const *s2);
int			is_space(char x);
int			is_pipe_rdr(char x);
int			is_quote(char x);
t_operator	get_operator(char *op);
int			ft_strcmp(char *s1, char *s2);

#endif