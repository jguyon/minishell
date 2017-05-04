/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parse_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 19:39:08 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/06 20:03:39 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_parse.h"
#include "ft_debug.h"

static t_err	parse_name(t_sh_lexer *lex, t_sh_cmd **cmd, t_sh_token *delim)
{
	t_sh_word	*name;
	t_err		err;

	*cmd = NULL;
	if ((err = sh_lexer_token(lex, delim))
			|| delim->type != SH_TOKEN_WORD)
		return (err);
	if (!(name = sh_word_new(delim->data.word))
			|| !(*cmd = sh_cmd_new(name)))
	{
		sh_word_del(&name);
		return (SH_ERR_NOMEM);
	}
	return (SH_ERR_OK);
}

t_err			sh_parse_args(t_sh_lexer *lex, t_sh_cmd **cmd,
					t_sh_token *delim)
{
	t_err		err;
	t_sh_word	*arg;

	while ((err = sh_lexer_token(lex, delim)) == SH_ERR_OK
			&& delim->type == SH_TOKEN_WORD)
	{
		if (!(arg = sh_word_new(delim->data.word)))
		{
			err = SH_ERR_NOMEM;
			break ;
		}
		sh_cmd_push(*cmd, arg);
	}
	if (err != SH_ERR_OK)
	{
		sh_cmd_del(cmd);
		return (err);
	}
	FT_DEBUG("parse: parsed command '%s'", (*cmd)->name->str);
	return (SH_ERR_OK);
}

t_err			sh_parse_cmd(t_sh_lexer *lex, t_sh_cmd **cmd,
					t_sh_token *delim)
{
	t_err	err;

	FT_ASSERT(lex != NULL);
	FT_ASSERT(cmd != NULL);
	FT_ASSERT(delim != NULL);
	FT_DEBUG("parse: parsing next command");
	if ((err = parse_name(lex, cmd, delim)) || *cmd == NULL)
		return (err);
	return (sh_parse_args(lex, cmd, delim));
}
