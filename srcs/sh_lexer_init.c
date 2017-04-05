/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 11:22:35 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/05 13:25:11 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_lexer.h"
#include "ft_debug.h"

t_err	sh_lexer_init(t_sh_lexer *lex, t_stream *stm)
{
	FT_ASSERT(lex != NULL);
	FT_ASSERT(stm != NULL);
	if (ft_ferror(stm))
		return (SH_ERR_IO);
	lex->stm = stm;
	lex->curr_char = -1;
	lex->curr_type = SH_CHAR_START;
	return (SH_ERR_OK);
}
