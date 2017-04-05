/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_nextc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 17:54:54 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/05 18:19:01 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_lexer.h"

static void	nextc_normal(t_sh_lexer *lex)
{
	if (lex->curr_char == '\n')
		lex->curr_type = SH_CHAR_END;
	else if (lex->curr_char == ' ' || lex->curr_char == '\t')
		lex->curr_type = SH_CHAR_WHITESPACE;
	else if (lex->curr_char == '\'')
	{
		lex->curr_ctx = SH_CTX_SQUOTE;
		sh_lexer_nextc(lex);
	}
	else if (lex->curr_char == '\\')
	{
		lex->curr_char = ft_fgetc(lex->stm);
		if (lex->curr_char == FT_EOF)
			lex->curr_type = SH_CHAR_END;
		else if (lex->curr_char == '\n')
			sh_lexer_nextc(lex);
		else
			lex->curr_type = SH_CHAR_TOKEN;
	}
	else
		lex->curr_type = SH_CHAR_TOKEN;
}

static void	nextc_squote(t_sh_lexer *lex)
{
	if (lex->curr_char == '\'')
	{
		lex->curr_ctx = SH_CTX_NORMAL;
		sh_lexer_nextc(lex);
	}
	else
		lex->curr_type = SH_CHAR_TOKEN;
}

void		sh_lexer_nextc(t_sh_lexer *lex)
{
	lex->curr_char = ft_fgetc(lex->stm);
	if (lex->curr_char == FT_EOF)
		lex->curr_type = SH_CHAR_END;
	else if (lex->curr_ctx == SH_CTX_SQUOTE)
		nextc_squote(lex);
	else
		nextc_normal(lex);
}
