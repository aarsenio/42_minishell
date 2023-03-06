/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarsenio <aarsenio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:33:42 by aarsenio          #+#    #+#             */
/*   Updated: 2023/03/06 17:07:06 by aarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

typedef struct s_toklist
{
	struct s_toklist	*next;
	char				*token;
}t_toklist;

// parse
t_toklist	*toklist(void);
t_toklist	*new_node(char *token);
void		add_node(t_toklist *new, t_toklist *x);
void		destroy_toklist(void);
void		tokenizer(char *input);
void		print_toklist(void);

//lib
char		*ft_strjoin(char const *s1, char const *s2);

#endif