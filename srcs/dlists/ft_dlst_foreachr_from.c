/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_foreachr_from.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 12:07:14 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 18:42:24 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlists.h"
#include "ft_debug.h"

void	ft_dlst_foreachr_from(t_dlist *list, t_dlist_node *first, void *acc,
								t_dlist_iterator itr)
{
	FT_ASSERT(list != NULL);
	FT_ASSERT(list->head.prev && list->head.next);
	FT_ASSERT(first != NULL);
	FT_ASSERT(first->prev && first->next);
	FT_ASSERT(itr != NULL);
	first = first->prev;
	while (first->next != &(list->head)
			&& itr(FT_DLST_ENTRY(list, first->next), acc))
		first = first->prev;
}
