/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parse_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 19:39:08 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/05 15:50:19 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_parse.h"
#include "ft_debug.h"

t_err	sh_parse_cmd(t_sh_lexer *lex, t_sh_cmd **cmd)
{
	t_sh_word	*name;
	t_err		err;

	FT_ASSERT(lex != NULL);
	FT_ASSERT(cmd != NULL);
	FT_DEBUG("parse: parsing next command");
	*cmd = NULL;
	if ((err = sh_parse_word(lex, &name)) != SH_ERR_OK || name == NULL)
		return (err);
	if (!(*cmd = sh_cmd_new(name)))
	{
		sh_word_del(&name);
		return (SH_ERR_NOMEM);
	}
	while ((err = sh_parse_word(lex, &name)) == SH_ERR_OK && name)
		sh_cmd_push(*cmd, name);
	if (err != SH_ERR_OK)
	{
		sh_cmd_del(cmd);
		return (err);
	}
	FT_DEBUG("parse: parsed command '%s'", (*cmd)->name->str);
	return (SH_ERR_OK);
}
