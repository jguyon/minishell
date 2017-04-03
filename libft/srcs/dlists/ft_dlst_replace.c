/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 00:54:32 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 18:30:53 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlists.h"
#include "ft_debug.h"

void	ft_dlst_replace(t_dlist_node *node, t_dlist_node *new)
{
	FT_ASSERT(node != NULL);
	FT_ASSERT(node->prev && node->next);
	FT_ASSERT(new != NULL);
	new->prev = node->prev;
	new->next = node->next;
	new->prev->next = new;
	new->next->prev = new;
	FT_DLST_NULLIFY(node);
}
