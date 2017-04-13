/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_seqlist_pop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 18:11:55 by jguyon            #+#    #+#             */
/*   Updated: 2017/04/13 16:47:55 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_ast.h"
#include "ft_debug.h"

t_sh_pipelist	*sh_seqlist_pop(t_sh_seqlist *lst)
{
	t_dlist_node	*node;

	FT_ASSERT(lst != NULL);
	if (!(node = ft_dlst_popl(&(lst->pipes))))
		return (NULL);
	return (FT_DLST_ENTRY(&(lst->pipes), node));
}
