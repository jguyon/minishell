/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darr_copy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 02:11:47 by jguyon            #+#    #+#             */
/*   Updated: 2017/02/20 02:24:39 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_darrays.h"
#include "ft_memory.h"

int		ft_darr_copy(t_darray *arr, const void *carr, size_t i, size_t size)
{
	while (size)
	{
		--size;
		if (ft_darr_set(arr, i + size, carr + (size * arr->item_size)))
			return (-1);
	}
	return (0);
}
