/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darr_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 01:08:28 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/20 02:01:42 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_darrays.h"
#include <ft_memory.h>

void	ft_darr_get(t_darray *arr, size_t i, void *val)
{
	if (i < arr->size)
		ft_memcpy(val, arr->array + (arr->item_size * i), arr->item_size);
	else
		ft_memcpy(val, arr->deflt, arr->item_size);
}
