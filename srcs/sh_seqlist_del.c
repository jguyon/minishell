/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_seqlist_del.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 18:15:16 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/06 18:19:35 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_ast.h"
#include "ft_memory.h"
#include "ft_debug.h"

void	sh_seqlist_del(t_sh_seqlist **lst)
{
	t_dlist_node	*node;
	t_sh_cmd		*cmd;

	FT_ASSERT(lst != NULL);
	if (*lst)
	{
		while ((node = ft_dlst_popl(&((*lst)->cmds))))
		{
			cmd = FT_DLST_ENTRY(&((*lst)->cmds), node);
			sh_cmd_del(&cmd);
		}
		ft_memdel((void **)lst);
	}
}
