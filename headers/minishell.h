/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:59:13 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/04/24 19:59:15 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline.h>
# include <history.h>
# include <stdlib.h>
# include <signal.h>

extern int	g_exit_status;

typedef enum e_operator
{
	NONE,
	R_OUT_REP,
	R_OUT_APP,
	R_IN,
	R_IN_UNT,
	PIPE,
}t_operator;

typedef struct s_envplist
{
	int					pos;
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
	int					index;
	int					ac;
	char				**av;
	t_operator			rdr;
	t_operator			pipe;
	struct s_arglist	*next;
}t_arglist;

typedef struct s_cleanlist
{
	t_operator			rdr;
	int					index;
	int					fdin;
	int					fdout;
	int					ac;
	char				**av;
	struct s_cleanlist	*next;
}t_cleanlist;

typedef struct s_data
{
	char				**envp;
	char				*input;
	int					ac;
	int					i;
	int					old_i;
	t_operator			op[2];
}t_data;

// parse
t_toklist	*new_toknode(char *token, t_operator operator);
void		add_toknode(t_toklist *new, t_toklist *x);
void		destroy_toklist(void);
t_toklist	*lst_node(void);
int			tokenizer(char *input);
void		add_argnode(t_arglist *new, t_arglist *x);
t_arglist	*new_argnode(int ac, char **av, t_operator *op, int index);
void		create_arglist(int i, t_toklist	*x);
void		destroy_arglist(void);
void		add_envpnode(t_envplist *new, t_envplist *x);
t_envplist	*new_envpnode(char *name, char *value, char *full);
void		destroy_envplist(void);
void		init_envplist(char **envp);
t_cleanlist	*new_cleannode(int ac, char **av, int index, t_operator rdr);
void		add_cleannode(t_cleanlist *new, t_cleanlist *x);
void		destroy_cleanlist(void);
void		create_cleanlist(void);
int			alphanumeric(char *input, int i);
int			pipe_redirections(char *input, int i);
int			quotes(char *input, int i);

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
int			builtins(t_cleanlist *node);
int			cmd_cd(t_cleanlist *node);
int			cmd_echo(t_cleanlist *node);
int			cmd_env(void);
void		cmd_export(t_cleanlist *node);
int			cmd_pwd(void);
void		cmd_unset(t_cleanlist *node);
int			cmd_exit(t_cleanlist *node);

	//executes
void		execute(void);
void		exec_executables(t_cleanlist *node);
void		exec_input(t_arglist *arg_node);
void		heredoc(t_arglist *arg_node);
void		exec_outputs(t_arglist *arg_node);
void		exec_pipe(t_cleanlist *node);
char		**get_paths(t_envplist *head);
char		*find_working_path(char *cmd, char **paths);
void		initiate_fd(void);

//libft
size_t		ft_lstsize(t_arglist *lst);
void		ft_putendl_fd(char *str, int fd);
void		ft_putstr_fd(char *str, int fd);
char		**ft_split(char const *s, char c);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strcpy(char *str);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
char		*ft_itoa(int n);
long long	ft_atoll(const char *str);
int			ft_strchr(char *s, char c);
int			is_alpha(int c);

//utils
void		sig_handler(int signal);
int			varname_length(char *str);
int			varvalue_length(char *str);
char		*copy_value(char *str);
char		*copy_name(char *str);
t_envplist	*envplist(void);
t_toklist	*toklist(void);
t_arglist	*arglist(void);
t_cleanlist	*cleanlist(void);
t_data		*data(void);
t_envplist	*fetch_node(char *str);
int			ft_envplstsize(void);
void		order_envplist(void);
void		update_envp(void);
void		init_shell(char **envp);
void		cmd_not_found(char *cmd_name);
void		no_such_file_or_dir(char *path);
void		exit_destroy_free(void);
void		exit_free_matrix(t_cleanlist *node, char **matrix, char *str);
void		free_matrix(char **matrix);
void		perror_exit(char *msg);
#endif
