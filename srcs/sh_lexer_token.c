/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 11:23:32 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/05 19:02:49 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_lexer.h"
#include "ft_darrays.h"
#include "ft_debug.h"

static int		set_char(t_darray *dstr, size_t i, char c)
{
	if (ft_darr_set(dstr, i + 1, NULL) || ft_darr_set(dstr, i, &c))
		return (-1);
	return (0);
}

static t_err	make_word(t_sh_lexer *lex, t_sh_token *token)
{
	t_darray	dstr;
	size_t		i;

	if (ft_darr_init(&dstr, sizeof(char), 16))
		return (SH_ERR_NOMEM);
	i = 0;
	while (lex->curr_type == SH_CHAR_TOKEN
			|| lex->curr_type == SH_CHAR_BACKSLASH_TOKEN)
	{
		if ((lex->curr_type == SH_CHAR_BACKSLASH_TOKEN
					&& set_char(&dstr, i++, '\\'))
				|| set_char(&dstr, i++, lex->curr_char))
		{
			ft_darr_clear(&dstr);
			return (SH_ERR_NOMEM);
		}
		sh_lexer_nextc(lex);
	}
	token->type = SH_TOKEN_WORD;
	token->data.word = (char *)dstr.array;
	FT_DEBUG("lexer: lexed word '%s'", token->data.word);
	return (SH_ERR_OK);
}

t_err			sh_lexer_token(t_sh_lexer *lex, t_sh_token *token)
{
	FT_ASSERT(lex != NULL);
	FT_ASSERT(token != NULL);
	FT_DEBUG("lexer: lexing next token");
	if (lex->curr_type == SH_CHAR_START)
		sh_lexer_nextc(lex);
	while (lex->curr_type == SH_CHAR_WHITESPACE)
		sh_lexer_nextc(lex);
	if (lex->curr_type == SH_CHAR_END)
	{
		token->type = SH_TOKEN_EOI;
		FT_DEBUG("lexer: lexed end of input");
		return (SH_ERR_OK);
	}
	return (make_word(lex, token));
}
