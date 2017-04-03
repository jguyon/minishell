/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_foreachr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 11:57:31 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 18:41:33 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlists.h"
#include "ft_debug.h"

void	ft_dlst_foreachr(t_dlist *list, void *acc, t_dlist_iterator itr)
{
	FT_ASSERT(list != NULL);
	FT_ASSERT(list->head.prev && list->head.next);
	FT_ASSERT(itr != NULL);
	ft_dlst_foreachr_from(list, list->head.prev, acc, itr);
}
