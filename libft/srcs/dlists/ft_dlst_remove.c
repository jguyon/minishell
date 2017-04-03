/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 12:23:41 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 18:29:18 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlists.h"
#include "ft_debug.h"

void	ft_dlst_remove(t_dlist_node *node)
{
	FT_ASSERT(node != NULL);
	FT_ASSERT(node->prev && node->next);
	node->prev->next = node->next;
	node->next->prev = node->prev;
	FT_DLST_NULLIFY(node);
}
