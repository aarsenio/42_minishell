/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:33:42 by aarsenio          #+#    #+#             */
/*   Updated: 2023/03/06 11:43:48 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

typedef struct	s_toklist
{
	char				*token;
	struct s_toklist	*next;
}t_toklist;

typedef struct	s_arglist
{
	int					argc;		/*numero de comandos*/
	char				**argv;		/*array de comandos, ex:"ls -la -b"*/
	struct s_arglist	*next;
}t_arglist;

typedef struct s_envplist
{
	char				*var_name;	/*nome das variaveis envirnonment*/
	char				*var_value;	/*valor das variaveis envirnonment*/
	struct s_envplist	*next;
}t_envplist;

typedef struct	s_data
{
	char				**envp;
	t_envplist			*envp_list;
	t_arglist			*arg_list;
	t_toklist			*tok_list;
}t_data;

/*parse*/
t_data			*data(void);
t_toklist		*new_node(char *token);
void			add_node(t_toklist *new, t_toklist *x);
void			destroy_list(t_toklist *x);
void			tokenizer(char *input);
void			print_toklist(void);

/*execute*/
void	execute(int argc, char **argv, char**envp);
void	here_doc(int argc, char *limiter);
void	free_matrix(char **matrix);
int		open_file(char *argv, int option);
int		end_and_error_message(char *msg);
/*commands*/
	/*builtins*/
void	cmd_env();
void	cmd_echo(t_arglist	*arg);

#endif
