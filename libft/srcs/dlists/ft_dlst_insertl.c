/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_insertl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 11:20:04 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 18:14:25 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlists.h"
#include "ft_debug.h"

void	ft_dlst_insertl(t_dlist_node *node, t_dlist_node *new)
{
	FT_ASSERT(node != NULL);
	FT_ASSERT(node->prev && node->next);
	FT_ASSERT(new != NULL);
	new->prev = node->prev;
	new->next = node;
	new->prev->next = new;
	new->next->prev = new;
}
