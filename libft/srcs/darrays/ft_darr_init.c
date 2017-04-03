/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darr_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 00:03:43 by jguyon            #+#    #+#             */
/*   Updated: 2017/03/29 17:39:58 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_darrays.h"
#include "ft_memory.h"
#include "ft_debug.h"

int		ft_darr_init(t_darray *arr, size_t item_size, size_t size)
{
	FT_ASSERT(arr != NULL);
	FT_ASSERT(item_size != 0);
	if (item_size == 0)
		return (-1);
	arr->item_size = item_size;
	arr->size = 0;
	arr->array = NULL;
	if (size > 0)
		return (ft_darr_set(arr, size - 1, NULL));
	return (0);
}
