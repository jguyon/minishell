/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ast.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:22:27 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/24 23:49:45 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_AST_H
# define SH_AST_H

/*
** Utilities to create and manipulate an AST of the shell language
*/

# include "ft_dlists.h"

/*
** Type representing a word (can be a command name, an arg...)
*/
typedef struct	s_sh_word {
	char			*str;
	t_dlist_node	node;
}				t_sh_word;

/*
** Type representing a simple command
*/
typedef struct	s_sh_cmd {
	t_sh_word	*name;
	t_dlist		args;
}				t_sh_cmd;

/*
** Functions to manipulate the AST
**
** The sh_word_tostr and sh_cmd_toargv extract their return value
** from the argument before freeing it.
** The other functions are somewhat self-explanatory, I think.
*/
t_sh_word		*sh_word_new(char *str);
char			*sh_word_tostr(t_sh_word **word);
void			sh_word_del(t_sh_word **word);
t_sh_cmd		*sh_cmd_new(t_sh_word *name);
void			sh_cmd_push(t_sh_cmd *cmd, t_sh_word *arg);
char			**sh_cmd_toargv(t_sh_cmd **cmd);
void			sh_cmd_del(t_sh_cmd **cmd);

#endif
