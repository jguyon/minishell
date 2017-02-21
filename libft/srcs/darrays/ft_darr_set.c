/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darr_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 00:37:11 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/20 02:00:17 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_darrays.h"
#include "ft_memory.h"
#include <stdlib.h>

#define MIN_ARRAY_SIZE(old) (old == 0 ? 8 : old)
#define GROW_SIZE(size) (size * 2)

static void	memset_array(void *arr, const void *val,
				size_t item_size, size_t size)
{
	while (size)
	{
		ft_memcpy(arr, val, item_size);
		arr += item_size;
		--size;
	}
}

static int	grow_array(t_darray *arr, size_t wanted_size)
{
	size_t	new_size;
	void	*new_arr;

	new_size = MIN_ARRAY_SIZE(arr->size);
	while (new_size <= wanted_size)
		new_size = GROW_SIZE(new_size);
	if (!(new_arr = malloc(arr->item_size * new_size)))
		return (-1);
	ft_memcpy(new_arr, arr->array, arr->item_size * arr->size);
	memset_array(new_arr + (arr->size * arr->item_size), arr->deflt,
		arr->item_size, new_size - arr->size);
	free(arr->array);
	arr->array = new_arr;
	arr->size = new_size;
	return (0);
}

int			ft_darr_set(t_darray *arr, size_t i, const void *val)
{
	if (i >= arr->size && grow_array(arr, i + 1))
		return (-1);
	if (!val)
		val = arr->deflt;
	memset_array(arr->array + (i * arr->item_size), val, arr->item_size, 1);
	return (0);
}
