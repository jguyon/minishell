/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ast.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:22:27 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/13 16:46:00 by jguyon           ###   ########.fr       */
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
	t_sh_word		*name;
	t_dlist			args;
	t_dlist_node	node;
}				t_sh_cmd;

/*
** Type representing a list of piped command
*/
typedef struct	s_sh_pipelist {
	t_dlist			cmds;
	t_dlist_node	node;
}				t_sh_pipelist;

/*
** Type representing a list of commands to execute sequentially
*/
typedef struct	s_sh_seqlist {
	t_dlist		pipes;
}				t_sh_seqlist;

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
t_sh_pipelist	*sh_pipelist_new(void);
void			sh_pipelist_push(t_sh_pipelist *pipe, t_sh_cmd *cmd);
t_sh_cmd		*sh_pipelist_pop(t_sh_pipelist *pipe);
void			sh_pipelist_del(t_sh_pipelist **pipe);
t_sh_seqlist	*sh_seqlist_new(void);
void			sh_seqlist_push(t_sh_seqlist *lst, t_sh_pipelist *pipe);
t_sh_pipelist	*sh_seqlist_pop(t_sh_seqlist *lst);
void			sh_seqlist_del(t_sh_seqlist **lst);

#endif
