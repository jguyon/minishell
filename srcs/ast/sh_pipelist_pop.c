/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pipelist_pop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 16:40:25 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/13 16:41:58 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_ast.h"
#include "ft_debug.h"

t_sh_cmd	*sh_pipelist_pop(t_sh_pipelist *pipe)
{
	t_dlist_node	*node;

	FT_ASSERT(pipe != NULL);
	if (!(node = ft_dlst_popl(&(pipe->cmds))))
		return (NULL);
	return (FT_DLST_ENTRY(&(pipe->cmds), node));
}
