/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parse_seqlist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 20:09:34 by jguyon            #+#    #+#             */
/*   Updated: 2017/05/04 17:53:57 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_parse.h"
#include "ft_debug.h"

t_sh_err	sh_parse_seqlist(t_sh_lexer *lex, t_sh_seqlist **lst,
			t_sh_token *delim)
{
	t_sh_pipelist	*pipe;
	t_sh_err		err;

	FT_ASSERT(lex != NULL);
	FT_ASSERT(lst != NULL);
	FT_ASSERT(delim != NULL);
	FT_DEBUG("parse: parsing next seqlist");
	if (!(*lst = sh_seqlist_new()))
		return (SH_ERR_NOMEM);
	while ((err = sh_parse_pipelist(lex, &pipe, delim)) == SH_ERR_OK)
	{
		if (pipe)
			sh_seqlist_push(*lst, pipe);
		if (delim->type != SH_TOKEN_OPERATOR
				|| delim->data.operator != SH_OP_SEMI)
			break ;
	}
	if (err != SH_ERR_OK)
	{
		sh_seqlist_del(lst);
		return (err);
	}
	FT_DEBUG("parse: parsed seqlist");
	return (SH_ERR_OK);
}
