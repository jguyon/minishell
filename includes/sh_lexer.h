/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 10:47:34 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/05 14:46:13 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_LEXER_H
# define SH_LEXER_H

# include "sh_errors.h"
# include "ft_streams.h"

/*
** Type of parsed character
**
** @SH_CHAR_START: start of input (nothing read yet)
** @SH_CHAR_END: end of input chars
** @SH_CHAR_WHITESPACE: whitespace chars
** @SH_CHAR_TOKEN: character inside token
*/
enum			e_sh_char_type {
	SH_CHAR_START,
	SH_CHAR_END,
	SH_CHAR_WHITESPACE,
	SH_CHAR_TOKEN,
};

/*
** Hold the current state of the lexer and its input stream
*/
typedef struct	s_sh_lexer {
	enum e_sh_char_type	curr_type;
	int					curr_char;
	t_stream			*stm;
}				t_sh_lexer;

/*
** Type of token
**
** SH_TOKEN_WORD: word (command name, argument, ...)
** SH_TOKEN_EOI: end of input
*/
enum			e_sh_token_type {
	SH_TOKEN_WORD,
	SH_TOKEN_EOI,
};

/*
** Data associated with a token type
**
** @word: allocated string constituting the word
*/
union			u_sh_token_data {
	char		*word;
};

/*
** Hold token data and type
*/
typedef struct	s_sh_token {
	enum e_sh_token_type	type;
	union u_sh_token_data	data;
}				t_sh_token;

/*
** Init @lex with @stm
*/
t_err			sh_lexer_init(t_sh_lexer *lex, t_stream *stm);

/*
** Parse a token from @lex into @tok
*/
t_err			sh_lexer_token(t_sh_lexer *lex, t_sh_token *tok);

#endif
