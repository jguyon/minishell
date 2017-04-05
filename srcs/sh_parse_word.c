/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parse_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:37:19 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/05 15:37:03 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_parse.h"
#include "ft_strings.h"
#include "ft_debug.h"

t_err	sh_parse_word(t_sh_lexer *lex, t_sh_word **word)
{
	t_sh_token	tok;
	t_err		err;

	FT_ASSERT(lex != NULL);
	FT_ASSERT(word != NULL);
	FT_DEBUG("parse: parsing next word");
	*word = NULL;
	if ((err = sh_lexer_token(lex, &tok)) != SH_ERR_OK)
		return (err);
	if (tok.type == SH_TOKEN_WORD)
	{
		if (!(*word = sh_word_new(tok.data.word)))
		{
			ft_strdel(&(tok.data.word));
			return (SH_ERR_NOMEM);
		}
		FT_DEBUG("parse: parsed word '%s'", (*word)->str);
	}
	return (SH_ERR_OK);
}
