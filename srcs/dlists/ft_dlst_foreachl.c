/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_foreachl.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 11:38:06 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 18:41:24 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlists.h"
#include "ft_debug.h"

void	ft_dlst_foreachl(t_dlist *list, void *acc, t_dlist_iterator itr)
{
	FT_ASSERT(list != NULL);
	FT_ASSERT(list->head.prev && list->head.next);
	FT_ASSERT(itr != NULL);
	ft_dlst_foreachl_from(list, list->head.next, acc, itr);
}
