/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_slice.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 19:26:29 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 17:54:49 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlists.h"
#include "ft_debug.h"

void	ft_dlst_slice(t_dlist *list, t_dlist_node *start, t_dlist_node *end)
{
	FT_ASSERT(list != NULL);
	FT_ASSERT(start != NULL);
	FT_ASSERT(end != NULL);
	start->prev->next = end->next;
	end->next->prev = start->prev;
	start->prev = &(list->head);
	end->next = &(list->head);
	list->head.next = start;
	list->head.prev = end;
}
