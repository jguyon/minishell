/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_joinl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 09:56:14 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 18:37:03 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlists.h"
#include "ft_debug.h"

void	ft_dlst_joinl(t_dlist *dst, t_dlist *src)
{
	FT_ASSERT(dst != NULL);
	FT_ASSERT(dst->head.prev && dst->head.next);
	FT_ASSERT(src != NULL);
	FT_ASSERT(src->head.prev && src->head.next);
	src->head.next->prev = &(dst->head);
	src->head.prev->next = dst->head.next;
	dst->head.next->prev = src->head.prev;
	dst->head.next = src->head.next;
}
