#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

extern int	g_exit_status;

typedef enum e_operator
{
	NONE,
	RDR_OUT_REPLACE,
	RDR_OUT_APPEND,
	RDR_INPUT,
	RDR_INPUT_UNTIL,
	PIPE,
}t_operator;

typedef struct s_envplist
{
	char				*full;
	char				*var_name;
	char				*var_value;
	struct s_envplist	*next;
}t_envplist;

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
	t_operator			rdr;
	t_operator			pipe;
	struct s_arglist	*next;
}t_arglist;

typedef struct s_data
{
	char				**envp;
	char				*input;
	int					stin_fd;
}t_data;

// parse
t_toklist	*new_toknode(char *token, t_operator operator);
void		add_toknode(t_toklist *new, t_toklist *x);
void		destroy_toklist(void);
int			tokenizer(char *input);
void		print_toklist(void);
void		add_argnode(t_arglist *new, t_arglist *x);
t_arglist	*new_argnode(int ac, char **av, \
			t_operator	rdr, t_operator	pipe);
void		token_handler(void);
void		destroy_arglist(void);
void		print_arglist(void);
void		add_envpnode(t_envplist *new, t_envplist *x);
t_envplist	*new_envpnode(char *name, char *value, char *full);
void		destroy_envplist(void);
void		init_envplist(char **envp);
void		print_envplist(void);

// parse lib
char		*parse_strjoin(char const *s1, char const *s2);
int			is_space(char x);
int			is_operator(char x);
int			is_quote(char x);
t_operator	get_operator(char *op);

// expander
char		*expander(char *str);
int			expander_checker(char *str);
int			expendable_len(char *token, int i);

//commands
	//built_ins
int			builtins(t_arglist *node);
int			cmd_cd(void);
int			cmd_echo(t_arglist *node);
int 		cmd_env(void);
void		cmd_export(t_arglist *node);
int			cmd_pwd(void);
int			cmd_unset(void);
void 		cmd_exit(void);

	//executes
void		execute(void);
void		exec_commands(t_arglist *node);
void		exec_executables(t_arglist *node);
void		exec_redirects(t_arglist *node);
void		exec_redirects(t_arglist *node);
void		exec_pipe(t_arglist *node);
char 		**get_paths(t_envplist *head);
char		*find_working_path(char *cmd, char **paths);

//libft
size_t		ft_lstsize(t_arglist *lst);
void		ft_putendl_fd(char *str, int fd);
void		ft_putstr_fd(char *str, int fd);
char		**ft_split(char const *s, char c);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strcpy(char *str);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);

//utils
int			varname_length(char *str);
int			varvalue_length(char *str);
char		*copy_value(char *str);
char		*copy_name(char *str);
t_envplist	*envplist(void);
t_toklist	*toklist(void);
t_arglist	*arglist(void);
t_data		*data(void);
void		update_envp(void);
void		init_shell(char **envp);
void		cmd_not_found(char *cmd_name);
void		exit_free_matrix(char **matrix,char *str);
void		free_matrix(char **matrix);
void		free_perror_exit(char *msg);
#endif
