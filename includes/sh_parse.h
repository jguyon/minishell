/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parse.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 15:59:10 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/06 20:08:56 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_PARSE_H
# define SH_PARSE_H

/*
** Functions used to parse the input of the program
*/

# include "sh_lexer.h"
# include "sh_ast.h"
# include "sh_errors.h"

/*
** Parse a command with arguments from the input
**
** @cmd will be assigned NULL if the input has ended before a word
** could be read.
*/
t_err	sh_parse_cmd(t_sh_lexer *lex, t_sh_cmd **cmd, t_sh_token *delim);

/*
** Parse a list of commands to execute sequentially
**
** @lst will be empty if no commands were parsed.
*/
t_err	sh_parse_seqlist(t_sh_lexer *lex, t_sh_seqlist **lst,
			t_sh_token *delim);

#endif
