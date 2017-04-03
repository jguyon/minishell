/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_next.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 13:03:52 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 18:39:01 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlists.h"
#include "ft_debug.h"

t_dlist_node	*ft_dlst_next(t_dlist *list, t_dlist_node *node)
{
	FT_ASSERT(list != NULL);
	FT_ASSERT(list->head.prev && list->head.next);
	FT_ASSERT(node != NULL);
	FT_ASSERT(node->prev && node->next);
	if (node->next == &(list->head))
		return (NULL);
	return (node->next);
}
