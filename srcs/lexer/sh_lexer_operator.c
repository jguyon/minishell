/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 15:00:13 by jguyon            #+#    #+#             */
/*   Updated: 2017/05/04 17:51:59 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_lexer.h"
#include "ft_debug.h"

t_sh_operator	g_sh_operators[SH_OP_COUNT] = {
	{";", SH_OP_SEMI},
	{"|", SH_OP_PIPE},
};

static void		init_operators(t_sh_operator *ops[SH_OP_COUNT])
{
	size_t	i;

	i = 0;
	while (i < SH_OP_COUNT)
	{
		ops[i] = &(g_sh_operators[i]);
		++i;
	}
}

static size_t	remove_operators(t_sh_operator *ops[SH_OP_COUNT],
					char c, size_t curr)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (i < SH_OP_COUNT)
	{
		if (ops[i] && ops[i]->symbol[curr] && ops[i]->symbol[curr] == c)
			++count;
		else
			ops[i] = NULL;
		++i;
	}
	return (count);
}

static int		find_operator(t_sh_operator *ops[SH_OP_COUNT], size_t curr,
					t_sh_token *tok)
{
	size_t	i;

	i = 0;
	while (i < SH_OP_COUNT)
	{
		if (ops[i] && ops[i]->symbol[curr] == '\0')
		{
			FT_DEBUG("lexer: lexed operator '%s'", ops[i]->symbol);
			tok->type = SH_TOKEN_OPERATOR;
			tok->data.operator = ops[i]->type;
			return (1);
		}
		++i;
	}
	return (0);
}

t_sh_err		sh_lexer_operator(t_sh_lexer *lex, t_sh_token *tok)
{
	t_sh_operator	*ops[SH_OP_COUNT];
	size_t			curr;

	FT_DEBUG("lexer: lexing operator");
	tok->type = SH_TOKEN_NONE;
	if (lex->type != SH_TYPE_LITERAL || lex->quoting != SH_QUOTING_NONE)
		return (SH_ERR_OK);
	init_operators(ops);
	curr = 0;
	while (curr < SH_OP_MAXLEN && lex->type == SH_TYPE_LITERAL
			&& remove_operators(ops, lex->chr, curr) > 1)
	{
		sh_lexer_translate(lex);
		++curr;
	}
	if (lex->type == SH_TYPE_LITERAL && find_operator(ops, curr + 1, tok))
		sh_lexer_translate(lex);
	return (SH_ERR_OK);
}
