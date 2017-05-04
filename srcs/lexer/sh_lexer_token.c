/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 11:23:32 by jguyon            #+#    #+#             */
/*   Updated: 2017/05/04 17:49:41 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_lexer.h"
#include "ft_debug.h"

static void		skip_whitespace(t_sh_lexer *lex)
{
	while (lex->type == SH_TYPE_WHITESPACE
			|| lex->type == SH_TYPE_LINECONT
			|| lex->type == SH_TYPE_ESCAPE)
		sh_lexer_translate(lex);
}

t_sh_err		sh_lexer_token(t_sh_lexer *lex, t_sh_token *token)
{
	t_sh_err	err;

	FT_ASSERT(lex != NULL);
	FT_ASSERT(token != NULL);
	FT_DEBUG("lexer: lexing next token");
	if (lex->type == SH_TYPE_NONE)
		sh_lexer_translate(lex);
	skip_whitespace(lex);
	if ((err = sh_lexer_eoi(lex, token))
			|| token->type == SH_TOKEN_EOI)
		return (err);
	if ((err = sh_lexer_operator(lex, token))
			|| token->type == SH_TOKEN_OPERATOR)
		return (err);
	return (sh_lexer_word(lex, token));
}
