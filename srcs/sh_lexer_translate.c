/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_translate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 10:41:49 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/06 12:59:05 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_lexer.h"

static int		do_normal(t_sh_lexer *lex)
{
	if (lex->escape)
	{
		lex->escape = SH_ESCAPING_FALSE;
		lex->type = SH_CHAR_ISLINESEP(lex->chr)
			? SH_TYPE_LINECONT : SH_TYPE_LITERAL;
	}
	else if (SH_CHAR_ISESCAPE(lex->chr))
	{
		lex->type = SH_TYPE_ESCAPE;
		lex->escape = SH_ESCAPING_TRUE;
	}
	else if (SH_CHAR_ISLINESEP(lex->chr))
		lex->type = SH_TYPE_LINESEP;
	else if (SH_CHAR_ISBLANK(lex->chr))
		lex->type = SH_TYPE_WHITESPACE;
	else if (SH_CHAR_ISSQUOTE(lex->chr) || SH_CHAR_ISDQUOTE(lex->chr))
	{
		lex->type = SH_TYPE_QUOTE;
		lex->quoting = SH_CHAR_ISSQUOTE(lex->chr)
			? SH_QUOTING_SINGLE : SH_QUOTING_DOUBLE;
	}
	else
		lex->type = SH_TYPE_LITERAL;
	return (0);
}

static int		do_squote(t_sh_lexer *lex)
{
	if (SH_CHAR_ISSQUOTE(lex->chr))
	{
		lex->type = SH_TYPE_QUOTE;
		lex->quoting = SH_QUOTING_NONE;
	}
	else
		lex->type = SH_TYPE_LITERAL;
	return (0);
}

static int		do_dquote(t_sh_lexer *lex)
{
	if (lex->escape)
	{
		lex->escape = SH_ESCAPING_FALSE;
		if (SH_CHAR_ISLINESEP(lex->chr))
			lex->type = SH_TYPE_LINECONT;
		else if (SH_CHAR_ISDQUOTE(lex->chr) || SH_CHAR_ISESCAPE(lex->chr))
			lex->type = SH_TYPE_LITERAL;
		else
			lex->type = SH_TYPE_SLASHED;
	}
	else if (SH_CHAR_ISESCAPE(lex->chr))
	{
		lex->type = SH_TYPE_ESCAPE;
		lex->escape = SH_ESCAPING_TRUE;
	}
	else if (SH_CHAR_ISDQUOTE(lex->chr))
	{
		lex->type = SH_TYPE_QUOTE;
		lex->quoting = SH_QUOTING_NONE;
	}
	else
		lex->type = SH_TYPE_LITERAL;
	return (0);
}

int				sh_lexer_translate(t_sh_lexer *lex)
{
	lex->chr = ft_fgetc(lex->stm);
	if (SH_CHAR_ISEOF(lex->chr))
	{
		if (lex->quoting != SH_QUOTING_NONE)
			return (-1);
		lex->type = SH_TYPE_EOI;
		return (0);
	}
	else if (lex->quoting == SH_QUOTING_SINGLE)
		return (do_squote(lex));
	else if (lex->quoting == SH_QUOTING_DOUBLE)
		return (do_dquote(lex));
	else
		return (do_normal(lex));
}
