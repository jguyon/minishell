/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 10:47:34 by jguyon            #+#    #+#             */
/*   Updated: 2017/05/04 17:49:03 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_LEXER_H
# define SH_LEXER_H

# include "sh_errors.h"
# include "ft_streams.h"

/*
** Check the type of a character
*/
# define SH_CHAR_ISBLANK(c) (c == ' ' || c == '\t')
# define SH_CHAR_ISSQUOTE(c) (c == '\'')
# define SH_CHAR_ISDQUOTE(c) (c == '"')
# define SH_CHAR_ISESCAPE(c) (c == '\\')
# define SH_CHAR_ISLINESEP(c) (c == '\n')
# define SH_CHAR_ISEOF(c) (c == FT_EOF)

/*
** Type of parsed character
**
** @SH_TYPE_NONE: placeholder value at initialization
** @SH_TYPE_LITERAL: literal value of the character
** @SH_TYPE_ESCLITERAL: literal character that has been escaped
** @SH_TYPE_SLASHED: literal character preceded by a literal backslash
** @SH_TYPE_WHITESPACE: blank character separating tokens
** @SH_TYPE_QUOTE: start or end character of a quoted string
** @SH_TYPE_ESCAPE: escape character
** @SH_TYPE_LINESEP: line separator
** @SH_TYPE_LINECONT: line continuation
** @SH_TYPE_EOI: end of input
*/
enum			e_sh_char_type {
	SH_TYPE_NONE,
	SH_TYPE_LITERAL,
	SH_TYPE_ESCLITERAL,
	SH_TYPE_SLASHED,
	SH_TYPE_WHITESPACE,
	SH_TYPE_QUOTE,
	SH_TYPE_ESCAPE,
	SH_TYPE_LINESEP,
	SH_TYPE_LINECONT,
	SH_TYPE_EOI,
};

/*
** Quoting context
*/
enum			e_sh_quoting {
	SH_QUOTING_NONE,
	SH_QUOTING_SINGLE,
	SH_QUOTING_DOUBLE,
};

/*
** Escaping context
*/
enum			e_sh_escaping {
	SH_ESCAPING_FALSE = 0,
	SH_ESCAPING_TRUE = 1,
};

/*
** Hold the current state of the lexer and its input stream
*/
typedef struct	s_sh_lexer {
	enum e_sh_quoting		quoting;
	enum e_sh_escaping		escape;
	enum e_sh_char_type		type;
	int						chr;
	t_stream				*stm;
}				t_sh_lexer;

/*
** Type of token
**
** SH_TOKEN_NONE: no token found
** SH_TOKEN_WORD: word (command name, argument, ...)
** SH_TOKEN_OPERATOR: operator
** SH_TOKEN_EOI: end of input
*/
enum			e_sh_token_type {
	SH_TOKEN_NONE,
	SH_TOKEN_WORD,
	SH_TOKEN_OPERATOR,
	SH_TOKEN_EOI,
};

/*
** Operator type
**
** @SH_OP_SEMI: semicolon seperator
** @SH_OP_PIPE: pipe operator
*/
enum			e_sh_operator {
	SH_OP_SEMI,
	SH_OP_PIPE,
};

/*
** Data associated with a token type
**
** @word: allocated string constituting the word
** @operator: operator type
*/
union			u_sh_token_data {
	char				*word;
	enum e_sh_operator	operator;
};

/*
** Hold token data and type
*/
typedef struct	s_sh_token {
	enum e_sh_token_type	type;
	union u_sh_token_data	data;
}				t_sh_token;

/*
** Maximum length of operators
*/
# define SH_OP_MAXLEN 1

/*
** Number of operators
*/
# define SH_OP_COUNT 2

/*
** Operator type and its corresponding symbol
*/
typedef struct	s_sh_operator {
	char				symbol[SH_OP_MAXLEN + 1];
	enum e_sh_operator	type;
}				t_sh_operator;

/*
** Supported operators
*/
t_sh_operator	g_sh_operators[SH_OP_COUNT];

/*
** Init @lex with @stm
*/
t_sh_err		sh_lexer_init(t_sh_lexer *lex, t_stream *stm);

/*
** Parse a token from @lex into @tok
*/
t_sh_err		sh_lexer_token(t_sh_lexer *lex, t_sh_token *tok);

/*
** Parsing of token types
*/
t_sh_err		sh_lexer_word(t_sh_lexer *lex, t_sh_token *tok);
t_sh_err		sh_lexer_operator(t_sh_lexer *lex, t_sh_token *tok);
t_sh_err		sh_lexer_eoi(t_sh_lexer *lex, t_sh_token *tok);

/*
** Advance the lexer position to the next character
**
** Used by `sh_lexer_token`.
** Returns -1 if a syntax error occurred, 0 otherwise.
*/
int				sh_lexer_translate(t_sh_lexer *lex);

#endif
