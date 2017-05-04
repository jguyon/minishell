/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 14:26:32 by jguyon            #+#    #+#             */
/*   Updated: 2017/05/04 14:03:55 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_lexer.h"
#include "ft_darrays.h"
#include "ft_memory.h"
#include "ft_debug.h"

static int	is_word_char(t_sh_lexer *lex)
{
	size_t	i;

	if (lex->type == SH_TYPE_LITERAL && lex->quoting == SH_QUOTING_NONE)
	{
		i = 0;
		while (i < SH_OP_COUNT)
		{
			if (g_sh_operators[i].symbol[0] == lex->chr)
				return (0);
			++i;
		}
		return (1);
	}
	return (lex->type != SH_TYPE_WHITESPACE
			&& lex->type != SH_TYPE_EOI
			&& lex->type != SH_TYPE_LINESEP);
}

static int	push_char(t_darray *word, size_t *i,
					enum e_sh_char_type type, char c)
{
	char	slash;

	if (type == SH_TYPE_SLASHED)
	{
		slash = '\\';
		if (ft_darr_set(word, *i + 2, NULL)
				|| ft_darr_set(word, *i + 1, &c)
				|| ft_darr_set(word, *i, &slash))
			return (-1);
		*i += 2;
	}
	else if (type == SH_TYPE_LITERAL || type == SH_TYPE_ESCLITERAL)
	{
		if (ft_darr_set(word, *i + 1, NULL)
				|| ft_darr_set(word, *i, &c))
			return (-1);
		*i += 1;
	}
	return (0);
}

t_err		sh_lexer_word(t_sh_lexer *lex, t_sh_token *tok)
{
	t_darray	word;
	size_t		i;
	char		*str;

	FT_DEBUG("lexer: lexing word");
	tok->type = SH_TOKEN_NONE;
	if (ft_darr_init(&word, sizeof(char), 0))
		return (SH_ERR_NOMEM);
	i = 0;
	while (is_word_char(lex))
	{
		if (push_char(&word, &i, lex->type, lex->chr))
		{
			str = ft_darr_extract(&word);
			ft_memdel((void **)&str);
			return (SH_ERR_NOMEM);
		}
		sh_lexer_translate(lex);
	}
	tok->type = SH_TOKEN_WORD;
	tok->data.word = ft_darr_extract(&word);
	FT_DEBUG("lexer: lexed word '%s'", tok->data.word);
	return (SH_ERR_OK);
}
