/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_seqlist_del.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 18:15:16 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/13 16:49:01 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_ast.h"
#include "ft_memory.h"
#include "ft_debug.h"

void	sh_seqlist_del(t_sh_seqlist **lst)
{
	t_dlist_node	*node;
	t_sh_pipelist	*pipe;

	FT_ASSERT(lst != NULL);
	if (*lst)
	{
		while ((node = ft_dlst_popl(&((*lst)->pipes))))
		{
			pipe = FT_DLST_ENTRY(&((*lst)->pipes), node);
			sh_pipelist_del(&pipe);
		}
		ft_memdel((void **)lst);
	}
}
