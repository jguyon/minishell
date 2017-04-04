/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parse.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 15:59:10 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/04 13:08:36 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_PARSE_H
# define SH_PARSE_H

/*
** Functions used to parse the input of the program
*/

# include "sh_ast.h"
# include "sh_errors.h"
# include "ft_streams.h"

# define SH_NEWLINE		'\n'
# define SH_WHITESPACE	" \t"

/*
** Type representing the program input
*/
typedef struct	s_sh_input {
	int			next_c;
	t_stream	*stm;
}				t_sh_input;

/*
** Init the input from a stream
*/
t_err			sh_init_input(t_sh_input *in, t_stream *stm);

/*
** Parse a word from the input
**
** @word will be assigned NULL if the input has ended before a
** word could be read.
*/
t_err			sh_parse_word(t_sh_input *in, t_sh_word **word);

/*
** Parse a command with arguments from the input
**
** @cmd will be assigned NULL if the input has ended before a word
** could be read.
*/
t_err			sh_parse_cmd(t_sh_input *in, t_sh_cmd **cmd);

#endif
