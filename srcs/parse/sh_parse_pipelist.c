/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parse_pipelist.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 16:53:23 by jguyon            #+#    #+#             */
/*   Updated: 2017/05/04 17:53:44 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_parse.h"
#include "ft_debug.h"

t_sh_err	sh_parse_pipelist(t_sh_lexer *lex, t_sh_pipelist **pipe,
			t_sh_token *delim)
{
	t_sh_cmd	*cmd;
	t_sh_err	err;

	FT_ASSERT(lex != NULL);
	FT_ASSERT(pipe != NULL);
	FT_ASSERT(delim != NULL);
	FT_DEBUG("parse: parsing next pipelist");
	if (!(*pipe = sh_pipelist_new()))
		return (SH_ERR_NOMEM);
	while ((err = sh_parse_cmd(lex, &cmd, delim)) == SH_ERR_OK)
	{
		if (cmd)
			sh_pipelist_push(*pipe, cmd);
		if (delim->type != SH_TOKEN_OPERATOR
				|| delim->data.operator != SH_OP_PIPE)
			break ;
	}
	if (err != SH_ERR_OK || ft_dlst_empty(&((*pipe)->cmds)))
	{
		sh_pipelist_del(pipe);
		return (err);
	}
	FT_DEBUG("parse: parsed pipelist");
	return (SH_ERR_OK);
}
