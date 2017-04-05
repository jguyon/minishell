/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 11:23:32 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/05 13:52:51 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_lexer.h"
#include "ft_darrays.h"
#include "ft_debug.h"

static void		next_char(t_sh_lexer *lex)
{
	lex->curr_char = ft_fgetc(lex->stm);
	if (lex->curr_char == FT_EOF || lex->curr_char == '\n')
		lex->curr_type = SH_CHAR_END;
	else if (lex->curr_char == ' ' || lex->curr_char == '\t')
		lex->curr_type = SH_CHAR_WHITESPACE;
	else
		lex->curr_type = SH_CHAR_TOKEN;
}

static t_err	make_word(t_sh_lexer *lex, t_sh_token *token)
{
	t_darray	dstr;
	size_t		i;
	char		c;

	if (ft_darr_init(&dstr, sizeof(char), 16))
		return (SH_ERR_NOMEM);
	i = 0;
	while (lex->curr_type == SH_CHAR_TOKEN)
	{
		c = lex->curr_char;
		if (ft_darr_set(&dstr, i + 1, NULL) || ft_darr_set(&dstr, i, &c))
		{
			ft_darr_clear(&dstr);
			return (SH_ERR_NOMEM);
		}
		next_char(lex);
		++i;
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
		next_char(lex);
	while (lex->curr_type == SH_CHAR_WHITESPACE)
		next_char(lex);
	if (lex->curr_type == SH_CHAR_END)
	{
		token->type = SH_TOKEN_EOI;
		FT_DEBUG("lexer: lexed end of input");
		return (SH_ERR_OK);
	}
	return (make_word(lex, token));
}
