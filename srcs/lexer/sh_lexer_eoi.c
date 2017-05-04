/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_eoi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 16:46:14 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/06 16:49:45 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_lexer.h"
#include "ft_debug.h"

t_err	sh_lexer_eoi(t_sh_lexer *lex, t_sh_token *tok)
{
	FT_DEBUG("lexer: lexing end of input");
	tok->type = SH_TOKEN_NONE;
	if (lex->type == SH_TYPE_EOI || lex->type == SH_TYPE_LINESEP)
	{
		FT_DEBUG("lexer: lexed end of input");
		tok->type = SH_TOKEN_EOI;
	}
	return (SH_ERR_OK);
}
