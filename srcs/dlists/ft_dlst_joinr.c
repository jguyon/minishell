/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_joinr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 10:11:22 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 18:37:32 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlists.h"
#include "ft_debug.h"

void	ft_dlst_joinr(t_dlist *dst, t_dlist *src)
{
	FT_ASSERT(dst != NULL);
	FT_ASSERT(dst->head.prev && dst->head.next);
	FT_ASSERT(src != NULL);
	FT_ASSERT(src->head.prev && src->head.next);
	src->head.next->prev = dst->head.prev;
	src->head.prev->next = &(dst->head);
	dst->head.prev->next = src->head.next;
	dst->head.prev = src->head.prev;
}
