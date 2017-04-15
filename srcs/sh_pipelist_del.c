/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pipelist_del.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 16:42:23 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/13 16:44:39 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_ast.h"
#include "ft_memory.h"
#include "ft_debug.h"

void	sh_pipelist_del(t_sh_pipelist **pipe)
{
	t_dlist_node	*node;
	t_sh_cmd		*cmd;

	FT_ASSERT(pipe != NULL);
	if (*pipe)
	{
		while ((node = ft_dlst_popl(&((*pipe)->cmds))))
		{
			cmd = FT_DLST_ENTRY(&((*pipe)->cmds), node);
			sh_cmd_del(&cmd);
		}
		ft_memdel((void **)pipe);
	}
}
