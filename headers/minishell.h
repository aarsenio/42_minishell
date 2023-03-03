/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarsenio <aarsenio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:33:42 by aarsenio          #+#    #+#             */
/*   Updated: 2023/03/03 11:13:51 by aarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

typedef struct s_list
{
	struct s_list	*next;
	char			token[999];
}t_list;

// parse
t_list	*list(void);
t_list	*new_node(char *token);
void	add_node(t_list *new, t_list *x);
void	destroy_list(t_list *x);
void	tokenizer(char *input);
void	print_list(void);

#endif