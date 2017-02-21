/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darr_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 00:03:43 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/20 01:59:27 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_darrays.h"
#include "ft_memory.h"

int		ft_darr_init(t_darray *arr, const void *deflt,
			size_t item_size, size_t size)
{
	if (item_size == 0)
		return (-1);
	arr->item_size = item_size;
	arr->size = 0;
	arr->array = NULL;
	ft_bzero(arr->deflt, sizeof(arr->deflt));
	if (deflt)
		ft_memcpy(arr->deflt, deflt, item_size);
	if (size > 0)
		return (ft_darr_set(arr, size - 1, deflt));
	return (0);
}
